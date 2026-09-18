#include "G4GDMLParser.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4Navigator.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4SystemOfUnits.hh"
#include "G4Version.hh"
#include "Randomize.hh"
#include <fstream>
#include <iomanip>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3 && argc != 5) return 2;
    G4GDMLParser parser;
    parser.SetStripFlag(false);
    parser.Read(argv[1], false);
    std::cout << "Runtime: " << G4Version << '\n';
    std::ofstream report(argv[2]);
    report << "physical_volume\tcopy\toverlap_reported\n";
    for (auto* pv : *G4PhysicalVolumeStore::GetInstance()) {
        if (!pv->GetMotherLogical()) continue;
        CLHEP::HepRandom::setTheSeed(721919);
        bool overlap = pv->CheckOverlaps(2000, .01*mm, true, 1);
        report << pv->GetName() << '\t' << pv->GetCopyNo() << '\t' << overlap << '\n';
    }
    if (argc == 5) {
        G4GeometryManager::GetInstance()->CloseGeometry();
        G4Navigator nav;
        nav.SetWorldVolume(parser.GetWorldVolume());
        std::ifstream input(argv[3]);
        std::ofstream output(argv[4]);
        output << std::setprecision(17) << "x_m\ty_m\tz_m\tdensity_g_cm3\tmaterial\tvolume\n";
        double x, y, z;
        while (input >> x >> y >> z) {
            auto* pv = nav.LocateGlobalPointAndSetup(G4ThreeVector(x*m,y*m,z*m), nullptr, false);
            if (!pv) return 3;
            auto* mat = pv->GetLogicalVolume()->GetMaterial();
            output << x << '\t' << y << '\t' << z << '\t' << mat->GetDensity()/(g/cm3)
                   << '\t' << mat->GetName() << '\t' << pv->GetName() << '\n';
        }
        G4GeometryManager::GetInstance()->OpenGeometry();
    }
}
