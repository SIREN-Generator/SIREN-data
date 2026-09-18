// Direct Geant4 solid tests, independent of SIREN and all rendering meshes.
#include "G4GDMLParser.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VSolid.hh"
#include "G4Version.hh"
#include "Randomize.hh"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

struct Row {
    G4VPhysicalVolume* pv;
    G4RotationMatrix rotation;
    G4ThreeVector position;
    std::string path;
};
std::vector<Row> rows;
void visit(G4VPhysicalVolume* pv, G4RotationMatrix r, G4ThreeVector t, std::string path) {
    t += r * pv->GetObjectTranslation();
    r = r * pv->GetObjectRotationValue();
    path += "/" + std::string(pv->GetName()) + "[" + std::to_string(pv->GetCopyNo()) + "]";
    rows.push_back({pv, r, t, path});
    auto* lv = pv->GetLogicalVolume();
    for (int i = 0; i < lv->GetNoDaughters(); ++i) visit(lv->GetDaughter(i), r, t, path);
}
int main(int argc, char** argv) {
    if (argc != 3) return 2;
    G4GDMLParser parser;
    parser.SetStripFlag(false);
    parser.Read(argv[1], false);
    std::cout << "Geant4 version: " << G4Version << '\n';
    visit(parser.GetWorldVolume(), G4RotationMatrix(), G4ThreeVector(), "");
    std::ofstream inventory(std::string(argv[2]) + "-inventory.tsv");
    std::ofstream overlaps(std::string(argv[2]) + "-overlaps.tsv");
    inventory << std::setprecision(17) << "name\tcopy\tmaterial\tx_mm\ty_mm\tz_mm\tsolid\tpath\n";
    overlaps << std::setprecision(17) << "target\tcopy\thorn\tx_mm\ty_mm\tz_mm\ttarget_safety_mm\thorn_safety_mm\n";
    std::vector<Row*> targets, horns;
    for (auto& row : rows) {
        auto* lv = row.pv->GetLogicalVolume();
        const auto& name = row.pv->GetName();
        if (row.path.find("TargetMotherVol") != std::string::npos || row.path.find("pvMHorn") != std::string::npos) {
            inventory << name << '\t' << row.pv->GetCopyNo() << '\t' << lv->GetMaterial()->GetName()
                      << '\t' << row.position.x()/mm << '\t' << row.position.y()/mm << '\t' << row.position.z()/mm
                      << '\t' << lv->GetSolid()->GetName() << '\t' << row.path << '\n';
        }
        if (name.find("TargetMotherVol") == 0 || name.find("pvMHorn1Mother") == 0) {
            CLHEP::HepRandom::setTheSeed(812347);
            row.pv->CheckOverlaps(20000, .01*mm, true, 4);
        }
        if (lv->GetMaterial()->GetDensity()/(g/cm3) <= .05) continue;
        if (row.path.find("TargetMotherVol") != std::string::npos) targets.push_back(&row);
        if (row.path.find("pvMHorn1Mother") != std::string::npos) horns.push_back(&row);
    }
    int pairs = 0;
    for (auto* target : targets) {
        auto* a = target->pv->GetLogicalVolume()->GetSolid();
        G4ThreeVector lo, hi;
        a->BoundingLimits(lo, hi);
        for (auto* horn : horns) {
            auto* b = horn->pv->GetLogicalVolume()->GetSolid();
            bool found = false;
            // Fins are narrow in x/z but tall in y: scan their interior finely.
            bool fin = target->pv->GetName().find("TGT1") == 0;
            const int nx = fin ? 3 : 13, ny = fin ? 1001 : 81, nz = fin ? 3 : 81;
            for (int iz = 0; iz < nz && !found; ++iz)
            for (int iy = 0; iy < ny && !found; ++iy)
            for (int ix = 0; ix < nx && !found; ++ix) {
                G4ThreeVector p(lo.x()+(hi.x()-lo.x())*(ix+.5)/nx,
                                lo.y()+(hi.y()-lo.y())*(iy+.5)/ny,
                                lo.z()+(hi.z()-lo.z())*(iz+.5)/nz);
                if (a->Inside(p) != kInside) continue;
                const auto world = target->position + target->rotation*p;
                const auto q = horn->rotation.inverse()*(world-horn->position);
                if (b->Inside(q) != kInside) continue;
                double sa=a->DistanceToOut(p), sb=b->DistanceToOut(q);
                if (std::min(sa,sb) <= .01*mm) continue;
                overlaps << target->pv->GetName() << '\t' << target->pv->GetCopyNo() << '\t' << horn->pv->GetName()
                         << '\t' << world.x()/mm << '\t' << world.y()/mm << '\t' << world.z()/mm
                         << '\t' << sa/mm << '\t' << sb/mm << '\n';
                found=true; ++pairs;
            }
        }
    }
    std::cout << "Confirmed target/horn material overlap pairs: " << pairs << '\n';
}
