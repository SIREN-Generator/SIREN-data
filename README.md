# SIREN-data

Data files for [SIREN](https://github.com/Harvard-Neutrino/SIREN): detector
geometries, flux tables, and cross-section splines.

## Directory structure

```
detectors/<program>/<version>/   -- detector geometry files
fluxes/<beam>/<version>/         -- flux tables
xsec/<model>/<version>/          -- cross-section splines
```

## Current contents

### detectors/SBN/v1/

GDML geometry files for the Fermilab Short-Baseline Neutrino program.
Used by `load_detector("SBN", detector=...)` in SIREN.

| File | Description | Upstream source |
|------|-------------|-----------------|
| `BNB/BooNE_50m.gdml` | BNB beamline geometry | [SBNSoftware/G4BNB](https://github.com/SBNSoftware/G4BNB/blob/master/geometry/BooNE_50m.gdml) |
| `NuMI/numi_g4export.gdml` | NuMI beamline geometry (Geant4 export) | g4numi (no public repo) |
| `ICARUS/icarus_refactored_nounderscore_20230918_nowires.gdml` | ICARUS T600 detector | [SBNSoftware/icarusalg](https://github.com/SBNSoftware/icarusalg/blob/develop/icarusalg/Geometry/gdml/icarus_refactored_nounderscore_20230918_nowires.gdml) |
| `SBND/sbnd_v02_06.gdml` | SBND detector | [SBNSoftware/sbndcode](https://github.com/SBNSoftware/sbndcode/blob/develop/sbndcode/Geometry/gdml/sbnd_v02_06.gdml) |
