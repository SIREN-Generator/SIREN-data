# SIREN-data

Data files for [SIREN](https://github.com/Harvard-Neutrino/SIREN): detector
geometries, flux tables, and cross-section splines.

Small files from upstream public repositories (e.g. SBNSoftware GDML files)
are downloaded directly from source. This repository hosts files that are not
available in a public upstream repo, or that require preprocessing.

## Directory structure

```
detectors/<program>/<version>/   -- detector geometry files
fluxes/<beam>/<version>/         -- flux tables
xsec/<model>/<version>/          -- cross-section splines
```

## Current contents

### detectors/SBN/v1/

| File | Description | Origin |
|------|-------------|--------|
| `numi_g4export.gdml` | NuMI beamline geometry (g4numi Geant4 export) | Exported from g4numi; not in a public repo |
