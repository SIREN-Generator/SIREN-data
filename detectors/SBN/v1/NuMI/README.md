# NuMI beamline GDML

## numi_g4export_2026-05-19.gdml

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
