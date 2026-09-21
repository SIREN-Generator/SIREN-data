# NuMI beamline GDML

Geant4 GDML exports of the NuMI beamline, produced from the
[TAMU-Neutrino/g4numi](https://github.com/TAMU-Neutrino/g4numi) fork of
[NuSoftHEP/g4numi](https://github.com/NuSoftHEP/g4numi) at commit
`4658ab16a5aabe54d3ace87826b31baf03720ddd` (2026-03-29).

| File | Configuration | Status |
|------|---------------|--------|
| `numi_ME_g4export_2026-09-17.gdml` | Medium-energy (ME / NOvA) mechanical geometry, explicitly configured | Supported; loaded by SIREN's SBN detector |
| `numi_g4export_2026-05-19.gdml` | ME target at legacy target, horn-2 and baffle positions | Historical only; contains target/horn overlaps and is **not** an LE geometry |

The TAMU-Neutrino fork includes additional fixes, notably the shielding
block geometry update described in MICROBOONE-NOTE-1132-PUB, "Search for
a Sterile Neutrino in a 3+1 Framework using Wire-Cell Inclusive
Charged-Current nu_e Selection with the BNB and NuMI beamlines in
MicroBooNE" (The MicroBooNE collaboration, June 7, 2024):

  https://microboone.fnal.gov/wp-content/uploads/MICROBOONE-NOTE-1132-PUB.pdf

The shielding block fix is one of three updates to the NuMI flux prediction
listed in Section 3.1 of that note:

  - Shielding block geometry update
  - Geant4 version update from v4.9.2 to v4.10.4
  - Updated PPFX implementation accounting for underlying changes in the
    simulation

Relevant commits in the TAMU-Neutrino fork:

  - `a255804` (2026-02-17) Re-enable missing concrete blocks.
  - `109a125` (2026-03-06) Apply geometry fixes from ZP.

Both files are the unmodified output of the Geant4 GDML writer: a full dump of
the beamline including the target hall, decay pipe, hadron absorber, and
surrounding rock. Geant4 `0x...` pointer suffixes are retained in volume and
solid names, so a fresh export can differ in names and bytes; the sha256 values
below pin the published files.

## numi_ME_g4export_2026-09-17.gdml

The nominal ME mechanical geometry, exported with the macro given under the
export procedure below. Selecting `BeamConfig me000z200i` alone keeps the
legacy target, horn-2 and baffle positions: the fork's `macros/template_ME.mac`
notes that `BeamConfig` is deprecated for ME and sets only the horn current.
The macro therefore sets every ME placement explicitly. Values follow that
template and the ME production defaults that fill its placeholders in
`ProcessG4NuMI.py` at the same commit:

| Setting | Value | Origin |
| --- | --- | --- |
| `DebugLevel` / `useNuBeam` / `RunPeriod` | `0` / `true` / `0` | template |
| `BeamConfig` | `me000z200i` | production default |
| `targetPosition` | `(0, 0, -143.3)` cm | production default (template comment: "10/2016 default") |
| `horn1Position` | `(0, 0, 3)` cm | production default |
| `horn2Position` | `(0, 0, 1918)` cm | z fixed in template; x, y production default |
| `bafflePosition` / `baffleInnerRadius` | `(0, 0, -380)` cm / `6.5` mm | template |
| `Horn1IsAlternate` / `Horn1IsRefined` | `true` / `false` | production default (new horn-1 geometry, no fine segmentation) |
| `HornWaterLayerThickness` | `1` mm | production default |
| `deltaOuterThickness` (horn-1 outer conductor) | `0.9525` cm | template |
| `duratekShift` / `thblockShift` | `4.5` m each | template |
| `useWaterInTgt` / `LengthOfWaterInTgt` | `false` / `3` cm | production default; the length is unused while water is disabled |
| `UseCorrHornCurrent` | `true` | differs from the template (`false`); see below |

Differences from the template. `UseCorrHornCurrent` is `true` here and `false`
in the template; in `NumiDataInput.cc` at this commit the flag only alters the
horn current for an LE horn configuration, so it has no effect on this ME
export, and the GDML carries no field in any case. `LengthOfWaterInTgt` is
kept from the template, but `NumiTarget.cc` builds the water volumes only when
`useWaterInTgt` is true. The template's beam-spot, importance-weighting,
ntuple, seed and `/run/beamOn` commands are omitted because the export only
constructs the geometry and writes GDML.

Positions are g4numi command parameters in its native MCZERO frame, not
necessarily GDML mother-volume centres. This asset describes geometry only: it
does not select a flux sample, horn polarity, magnetic-field map or
run-dependent survey. ME is the only supported configuration.

### Source

- Repository: https://github.com/TAMU-Neutrino/g4numi
- Upstream: https://github.com/NuSoftHEP/g4numi
- Commit: `4658ab16a5aabe54d3ace87826b31baf03720ddd` (2026-03-29)
- Configuration: `macros/template_ME.mac` filled with the ME production
  defaults of `ProcessG4NuMI.py`, as tabulated above (macro below)

### Export date

2026-09-17

### Export procedure

An existing macOS ARM64 build of g4numi with Geant4 10.4.p02 and the
`FTFP_BERT` physics list was used. It was not rebuilt for this export, and no
events were generated. The checkout carried tracking-only changes to
backward-track killing and no geometry changes. The export macro, saved as
`export_ME.mac` and run from an empty output directory in a configured g4numi
environment with `g4numi export_ME.mac FTFP_BERT`, was:

```
/NuMI/run/DebugLevel 0
/NuMI/run/useNuBeam true
/NuMI/det/RunPeriod 0
/NuMI/det/BeamConfig me000z200i

# BeamConfig alone retains legacy positions. Set the complete ME geometry.
/NuMI/run/useWaterInTgt false
/NuMI/det/LengthOfWaterInTgt 3 cm
/NuMI/det/set/targetPosition 0 0 -143.3 cm
/NuMI/det/Horn1IsAlternate true
/NuMI/det/Horn1IsRefined false
/NuMI/det/HornWaterLayerThickness 1 mm
/NuMI/det/UseCorrHornCurrent true
/NuMI/det/set/horn1Position 0 0 3 cm
/NuMI/det/set/horn2Position 0 0 1918 cm
/NuMI/det/set/deltaOuterThickness 0.9525 cm
/NuMI/det/set/duratekShift 4.5 m
/NuMI/det/set/thblockShift 4.5 m
/NuMI/det/set/bafflePosition 0 0 -380 cm
/NuMI/det/set/baffleInnerRadius 6.5 mm

/NuMI/det/update
/NuMI/output/GDMLref true
/NuMI/output/writeGDML numi_ME_g4export_2026-09-17.gdml
```

### Validation and known limitations

The following checks were run on the published file with tooling kept outside
this data repository.

- All 48 target-fin centres are at the ME axial positions (z from -1363.5 mm
  to -212.0 mm in 24.5 mm steps) and horn 2 is at z = 19180 mm. The target and
  horn-1 axial envelopes are separated by 87.61 mm.
- Independent Geant4 11.3.2 overlap checks of the target and horn-1 mother
  volumes pass at 0.01 mm tolerance with 20,000 surface samples. A targeted
  solid-interior scan finds zero target/horn material overlap pairs; the same
  scan found 88 in the May file.
- All 282 logical-volume meshes build at 48 angular slices with finite vertices
  and nonempty faces. SIREN's strict GDML reader imports 969 sectors.
- Of 20,000 seeded material points, 19,981 agree between Geant4 and SIREN.
  The same 19 downstream points disagree, with identical densities, in the
  May file; no new mismatches appear. These points lie near daughter volumes
  that protrude outside the tunnel mother. All 15,000 target/horn-focused
  points agree.

**This is not an overlap-free audit of the entire beamline.** A broader Geant4
11.3.2 scan of 563 physical-volume definitions (2,000 surface samples each,
0.01 mm tolerance) flags 16 definitions: eight horn-1 conductor pieces outside
their enclosing volume, two Duratek blocks, three decay-pipe/tracker volumes
against concrete shielding, and three downstream mother-volume protrusions.
The horn-1 protrusions are approximately 0.36–1.62 mm; their origin remains
unresolved because the native Geant4 10.4.p02 pre-export overlap check reports
these horn pieces as OK. The native check does report shielding/decay-pipe and
downstream containment issues. Different Geant4 versions and random surface
samples need not report identical volumes. This export fixes the ME
configuration and does not modify those source solids or claim
production-wide validation.

### sha256

`730466f287196d65a7fee074203014471faee6be0fbfa3da4769046d92355ed7`

## numi_g4export_2026-05-19.gdml (historical)

Retained unchanged for reproducing previous results. The recovered export
macro selected `me000z200i` without explicitly setting the ME positions:
target -0.350 m, horn 2 +10 m, baffle -2.53 m. The tall ME target therefore
extends into horn 1 and produces real target/horn overlaps before
serialization (35 of 48 fins intersect the inner conductor). It must not be
relabeled as a valid low-energy geometry.

### Source

- Repository: https://github.com/TAMU-Neutrino/g4numi
- Upstream: https://github.com/NuSoftHEP/g4numi
- Commit: `4658ab16a5aabe54d3ace87826b31baf03720ddd` (2026-03-29)

### Export date

2026-05-19

### Export procedure

The GDML was exported from the TAMU-Neutrino/g4numi build by running the
simulation with `/run/beamOn 0` and the GDML writer enabled, producing a
full geometry dump of the NuMI beamline including the target hall, decay
pipe, hadron absorber, and surrounding rock.

### sha256

`39670d52a6181352a8ae7c798387a9c58de950462c634e57da7d39fb23abe30a`
