# SIREN-data

Data files for [SIREN](https://github.com/Harvard-Neutrino/SIREN): detector
geometries, flux tables, generator inputs, and cross-section splines.

## Directory structure

```
detectors/<program>/<version>/   -- detector geometry files
fluxes/<beam>/<version>/         -- flux tables
processes/<model>/<version>/     -- interaction-generator data
xsec/<model>/<version>/          -- cross-section splines
```

## Current contents

### detectors/SBN/v1/

GDML geometry files for the Fermilab Short-Baseline Neutrino program.
Used by `load_detector("SBN", detector=...)` in SIREN.

| File | Description | Upstream source |
|------|-------------|-----------------|
| `BNB/BooNE_50m.gdml` | BNB beamline geometry | [SBNSoftware/G4BNB](https://github.com/SBNSoftware/G4BNB/blob/master/geometry/BooNE_50m.gdml) |
| `NuMI/numi_g4export.gdml` | NuMI beamline geometry (Geant4 export) | [NuSoftHEP/g4numi](https://github.com/NuSoftHEP/g4numi) (exported from Geant4) |
| `ICARUS/icarus_refactored_nounderscore_20230918_nowires.gdml` | ICARUS | [SBNSoftware/icarusalg](https://github.com/SBNSoftware/icarusalg/blob/develop/icarusalg/Geometry/gdml/icarus_refactored_nounderscore_20230918_nowires.gdml) |
| `SBND/sbnd_v02_06.gdml` | SBND detector | [SBNSoftware/sbndcode](https://github.com/SBNSoftware/sbndcode/blob/develop/sbndcode/Geometry/gdml/sbnd_v02_06.gdml) |

### processes/MarleyCrossSection/MarleyCrossSection-v2.0/

MARLEY v2.0.0 reaction, CRPA response, mass, spin-parity, charge-radius,
nuclear-structure, and logger inputs used by SIREN's
`MarleyCrossSection-v2.0` resource. The files are distributed as one
SHA-256-pinned zip so SIREN can fetch the complete, internally consistent data
bundle in a single download. See the directory README for exact provenance and
archive contents.
