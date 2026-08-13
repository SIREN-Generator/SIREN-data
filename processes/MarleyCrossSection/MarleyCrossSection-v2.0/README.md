# MARLEY v2.0.0 data bundle

This directory contains the MARLEY v2 data used by SIREN's
`MarleyCrossSection-v2.0` process loader.

## Contents

`MarleyCrossSection-v2.0.zip` contains 126 runtime data files with their
original MARLEY directory layout:

- `mass_table.js`, `gs_spin_parity_table.txt`, and
  `nuclear_charge_radii.js`
- the default logger configuration under `config/`
- four reaction definitions under `react/`
- six HF-CRPA nuclear response tables under `react/crpa/`
- the nuclide index and 111 per-element nuclear structure tables under
  `structure/`
- the upstream GPLv3 license as `COPYING`

Archive SHA-256:

```text
7965f0ea89dda01dfa8a5d4eb5af36e9ff6f440ed7945afb3ea64236b2931cf7  MarleyCrossSection-v2.0.zip
```

## Provenance

Every runtime data file is byte-identical to the corresponding file under
`data/` in the official [MARLEY v2.0.0
release](https://github.com/MARLEY-MC/marley/releases/tag/v2.0.0), commit
`435f083b60411b8a747c6a73d8c9b3a52ee25c0b`. The archive was assembled on
2026-08-13 from the files selected for the SIREN MARLEY v2 interface. The
selection excludes unrelated MARLEY example configurations, tests, optical
model data, and reaction inputs that SIREN does not load.

MARLEY is distributed under the GNU General Public License version 3. The
upstream license text is preserved both beside and inside the archive as
`COPYING`.
