# DUNE Far Detector (DUNEFD) geometry, v2

GDMLs of the two DUNE Far Detector modules, taken from the official
[DUNE/dunecore](https://github.com/DUNE/dunecore) geometry repository
(Apache-2.0) and used by the SIREN loader
`resources/detectors/DUNEFD/DUNEFD-v2/`.

| Module | Directory | GDML | dunecore commit |
|--------|-----------|------|-----------------|
| FD1-HD (horizontal drift) | `HD/` | `dune10kt_v6_refactored_1x2x6_nowires.gdml` | `b8fb0006` (2024-03-11) |
| FD2-VD (vertical drift)   | `VD/` | `dunevd10kt_3view_30deg_v7_refactored_1x8x14_nowires.gdml` | `697040d7` (2025-02-04) |

Both are "nowires" partial-module "workspace" geometries (sense wires omitted,
sensitive `volTPCActive` volumes retained) -- lightweight inputs for SIREN's
macroscopic-material sector model. Each module directory has a `README.md` with
the full upstream provenance (path, commit, retrieval date, version-token
meaning, license, sha256). All files were retrieved from dunecore `develop` on
2026-06-24 and verified byte-identical to the blob at their last-modifying
commit.

## Site frame

The SIREN loader places both modules in a common site frame:

- `+y` = local up (vertical at SURF),
- `+z` = LBNF neutrino-beam direction downstream (geographic azimuth 277.15 deg,
  tilted +5.71 deg upward at the far detector),
- `+x` = right-handed (horizontal transverse).

The HD GDML is already in this frame (y up, z beam) and is placed with identity
rotation. The VD GDML is built x = up (vertical drift along its local x) and is
rotated GDML z = -90 deg so its drift axis points along +y.

## License

The GDMLs are Apache-2.0, (c) Fermi National Accelerator Laboratory / DUNE
Collaboration. They are generated geometry data; see each module README.
