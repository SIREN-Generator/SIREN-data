# NuMI beamline GDML

## numi_g4export_2026-05-19.gdml

Geant4 GDML export of the NuMI beamline geometry, produced from the
[TAMU-Neutrino/g4numi](https://github.com/TAMU-Neutrino/g4numi) fork.

This version includes the shielding block geometry update described in
MICROBOONE-NOTE-1132-PUB, "Search for a Sterile Neutrino in a 3+1
Framework using Wire-Cell Inclusive Charged-Current nu_e Selection with
the BNB and NuMI beamlines in MicroBooNE" (The MicroBooNE collaboration,
June 7, 2024):

  https://microboone.fnal.gov/wp-content/uploads/MICROBOONE-NOTE-1132-PUB.pdf

The shielding block fix is one of three updates to the NuMI flux prediction
listed in Section 3.1 of that note:

  - Shielding block geometry update
  - Geant4 version update from v4.9.2 to v4.10.4
  - Updated PPFX implementation accounting for underlying changes in the
    simulation

The upstream g4numi repository (https://github.com/keplerman417/G4BNB_BSM_rostein,
originally from Fermilab) does not contain this fix. The TAMU-Neutrino fork
incorporates the corrected shielding block geometry.

### Export date

2026-05-19

### Export procedure

The GDML was exported from the TAMU-Neutrino/g4numi build by running the
simulation with `/run/beamOn 0` and the GDML writer enabled, producing a
full geometry dump of the NuMI beamline including the target hall, decay
pipe, hadron absorber, and surrounding rock.
