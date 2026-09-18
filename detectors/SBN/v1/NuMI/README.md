# NuMI beamline GDML

## Medium-energy configuration (ME / NOvA)

`numi_ME_g4export_2026-09-17.gdml` is the nominal ME mechanical geometry,
exported with the complete settings in [export_ME.mac](export_ME.mac).
SHA256: `730466f287196d65a7fee074203014471faee6be0fbfa3da4769046d92355ed7`.

| Setting | Value |
| --- | --- |
| BeamConfig / RunPeriod | `me000z200i` / `0` |
| Target position | `(0, 0, -143.3)` cm |
| Horn 1 position | `(0, 0, 3)` cm |
| Horn 2 position | `(0, 0, 1918)` cm |
| Baffle position / bore radius | `(0, 0, -380)` cm / `6.5` mm |
| Horn 1 model | alternate, unrefined |
| Horn water / outer-thickness adjustment | `1` mm / `0.9525` cm |
| Duratek and target-hall block shifts | `4.5` m each |
| Water in target | disabled |

Positions are g4numi command parameters in its native MCZERO frame, not
necessarily GDML mother-volume centres. This asset describes geometry, not a
flux sample, polarity selection, magnetic-field map or run-dependent survey.
Only ME is provided as a supported configuration. The older May file below
is an invalid mixture of ME target geometry and legacy positions, **not LE**.

### Reproduction and provenance

Source: [TAMU-Neutrino/g4numi at 4658ab16](https://github.com/TAMU-Neutrino/g4numi/tree/4658ab16a5aabe54d3ace87826b31baf03720ddd),
using `macros/template_ME.mac` with the explicit nominal ME settings above.
The export used an existing macOS ARM64 build with Geant4 10.4.p02 and
`FTFP_BERT`. No events were generated. In a configured g4numi environment, run
from an empty output directory:

```sh
g4numi /absolute/path/to/export_ME.mac FTFP_BERT
```

The GDML is the writer's unmodified output. Geant4 pointer suffixes are retained;
a fresh export can therefore have different names and bytes. The SHA256 pins
this exact published artifact. [validation_ME.json](validation_ME.json) records
source, binary and library hashes separately: the existing build was not rebuilt
for this export. The checkout had tracking-only changes to backward-track killing;
no geometry code was changed for the export.

### Validation and known limitations

- `python3 validate_ME.py` checks the published bytes and ME placements, including
  all 48 target-fin centres and separation of the target and horn-1 envelopes.
- Independent Geant4 11.3.2 checks of the target/horn mothers pass at 0.01 mm
  tolerance with 20,000 surface samples. A targeted solid-interior scan finds
  zero target/horn material overlap pairs; the same scan found 88 in the May file.
- All 282 logical-volume meshes build at 48 angular slices with finite vertices
  and nonempty faces. SIREN's strict GDML reader imports 969 sectors.
- Of 20,000 seeded material points, 19,981 agree between Geant4 and SIREN.
  The same 19 downstream points disagree with identical densities using the old
  file; no new mismatches appear. These points lie near daughter volumes that
  protrude outside the tunnel mother. All 15,000 target/horn-focused points agree.

**This is not an overlap-free audit of the entire beamline.** A broader Geant4
11.3.2 scan of 563 physical-volume definitions (2,000 surface samples each,
0.01 mm tolerance) flags 16 definitions: eight horn-1 conductor pieces outside
their enclosing volume, two Duratek blocks, three decay-pipe/tracker volumes
against concrete shielding, and three downstream mother-volume protrusions.
The horn-1 protrusions are approximately 0.36–1.62 mm; their origin remains
unresolved because the native Geant4 10.4.p02 pre-export overlap check reports
these horn pieces as OK. The native check does report shielding/decay-pipe and
downstream containment issues. Different versions and random surface samples
need not report identical volumes. These residual findings are retained in
[validation_ME.json](validation_ME.json); this export fixes the ME configuration
and does not modify those source solids or claim production-wide validation.

## Historical export: numi_g4export_2026-05-19.gdml

Retained unchanged for reproducing previous results. SHA256:
`39670d52a6181352a8ae7c798387a9c58de950462c634e57da7d39fb23abe30a`.
The recovered export macro selected `me000z200i` without explicitly setting
ME positions: target -0.350 m, horn 2 +10 m, baffle -2.53 m. This produces
real target/horn overlaps before serialization (35 of 48 fins intersect the
inner conductor). It must not be relabeled as a valid low-energy geometry.

The original provenance follows for historical context.


Geant4 GDML export of the NuMI beamline geometry, produced from the
[TAMU-Neutrino/g4numi](https://github.com/TAMU-Neutrino/g4numi) fork
at commit `4658ab1` (2026-03-29).

The upstream repository is [NuSoftHEP/g4numi](https://github.com/NuSoftHEP/g4numi).
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

## Repeating the independent solid checks

The checked-in [validation sources](validation/) require Geant4 with GDML.
From this directory (configure `Geant4_DIR` for the intended runtime):

```sh
cmake -S validation -B /tmp/numi-check-build -DGeant4_DIR=/path/to/lib/cmake/Geant4
cmake --build /tmp/numi-check-build
/tmp/numi-check-build/probe_overlap numi_ME_g4export_2026-09-17.gdml /tmp/ME
/tmp/numi-check-build/audit_geometry numi_ME_g4export_2026-09-17.gdml /tmp/ME-full.tsv
```

The first writes placement inventory and target/horn material-overlap witnesses;
the second writes a per-volume flag table and prints full Geant4 warnings.
The target scan samples solid interiors; a zero count is not a mathematical
proof of disjoint solids. The independent axial-envelope check in
`validate_ME.py` provides the stronger separation check for this ME placement.
