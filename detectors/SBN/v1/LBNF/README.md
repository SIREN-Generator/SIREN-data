# DUNE LBNF beamline GDML

## g4lbnf.gdml

Geant4 GDML export of the DUNE/LBNF primary beamline geometry, produced from
**g4lbne** (the Fermilab `lbne-beamsim` simulation) at commit `0f2b8dc`
(master), using the **July 2020 Optimized Engineered Design**
(`OptEngDesignJul2020`): the RAL-designed helium-cooled ~1.8 m cantilevered
graphite target with the three-horn focusing system (horn A conic inner
conductor; horns B and C standardized, with striplines), 1.2 MW operation,
293 kA horn current, 120 GeV protons.

The geometry contains the full primary beam train -- baffle/collimator,
target, three focusing horns, decay pipe (194 m), and hadron absorber --
inside the enclosing `Tunnel` world (911 volumes / 1311 placements, 28 inline
materials). It is built in the beam frame: MCZero at the target, +z along the
(horizontally-built) beam axis, +y up. The 101 mrad beam declination is NOT
baked into the geometry; it is applied externally by the placement transform.
Volume/solid names carry Geant4 `0x...` pointer suffixes, which the SIREN GDML
parser strips automatically.

### Source

- Repository: g4lbne (FNAL `lbne-beamsim`),
  `ssh://p-lbne-beamsim@cdcvs.fnal.gov/cvs/projects/lbne-beamsim/g4lbne.git`
  (project wiki: https://cdcvs.fnal.gov/redmine/projects/lbne-beamsim)
- Commit: `0f2b8dc` (master)
- Geometry config: `macros/OptEngDesignJul2020.mac`
  (key command `/LBNE/det/UseStandardEngHornDesign True`)

Note: the anonymous HTTP mirror of g4lbne is stale (master frozen 2024-04);
the live source is the FNAL cdcvs SSH origin above.

### Export date

2026-06-09

### Export procedure

g4lbne builds the beamline in C++ and serializes it on demand. It was built
against the g4bnb software stack (Geant4 10.4.3 / ROOT 6.36 / dk2nu /
xerces-c) with a small set of local build-system patches (the crux being the
libc++ `_LIBCPP_ENABLE_CXX17_REMOVED_FEATURES` define, needed because Geant4
10.4 headers use `std::binary_function`, removed in C++17). The export runs
the OptEngDesignJul2020 design with the GDML writer enabled and no beam:

```
/LBNE/det/UseStandardEngHornDesign True
/LBNE/det/WriteGDMLFile true
/LBNE/det/construct
/run/initialize
```

The `WriteGDMLFile` flag triggers `G4GDMLParser::Write("g4lbnf.gdml", tunnel)`
in `LBNEDetectorConstruction.cc`, serializing the entire constructed beamline
(the C++-built target/horns/decay-pipe plus the imported absorber/MARS/TOP
sub-geometries) into one file.

### Placement in SIREN

Placed in the BNB world via the `LBNF -> BNB` edge in
`resources/detectors/SBN/SBN-v1/sbn_geometry.py`:

- Rotation: beam azimuth 287.79 deg (Fermilab -> SURF), 101 mrad downward.
- Horizontal translation: from the Fermilab MI-10 / MI-60 straight-section
  FSCS survey centers, bridged into the BNB frame through NuMI (good to
  ~10-15 m; validated against the authoritative NuMI flux matrix to ~1 deg).
- Vertical: MCZero taken at site grade, y_up = 8.369 m in the BNB frame
  (the Fermilab grade is modeled as the MiniBooNE computer-room floor).

Enabled at load time with `load_detector("SBN", detector=..., lbnf=True)`
(off by default).

### License

g4lbne is Fermilab `lbne-beamsim` code; this GDML is a geometry export (data).
The generating simulation is the property of Fermilab / the DUNE collaboration.

### sha256

`f0e0f32cc3cf45fb1a783d84d470a5d2caa06b7ba667648482f8e4137d507cdc`
