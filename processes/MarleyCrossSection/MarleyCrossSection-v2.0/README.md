# MARLEY v2.0.0 data bundle

This directory contains the MARLEY 2.0.0 data used by SIREN's
`MarleyCrossSection-v1.0` and `MarleyCrossSection-v2.0` process loaders. The
v1 loader evaluates the legacy reaction models with the MARLEY 2.0.0 engine
in its backwards-compatible mode.

## Contents

`MarleyCrossSection-v2.0.tar.xz` contains 129 runtime data files with their
original MARLEY directory layout:

- `mass_table.js`, `gs_spin_parity_table.txt`, and
  `nuclear_charge_radii.js`
- the default logger configuration under `config/`
- four current reaction definitions under `react/`
- three legacy reaction definitions under `react/v1/`
- six HF-CRPA nuclear response tables under `react/crpa/`
- the nuclide index and 111 per-element nuclear structure tables under
  `structure/`
- the upstream GPLv3 license as `COPYING`

Archive SHA-256:

```text
10c05087774b409fc1908a0482fa65af0e030baddca41a296446558374d0b5bc  MarleyCrossSection-v2.0.tar.xz
```

## Provenance

Every runtime data file is byte-identical to the corresponding file under
`data/` in the official [MARLEY v2.0.0
release](https://github.com/MARLEY-MC/marley/releases/tag/v2.0.0), commit
`435f083b60411b8a747c6a73d8c9b3a52ee25c0b`. The archive was assembled on
2026-08-14 from the files selected for the SIREN MARLEY interfaces. The
selection excludes unrelated MARLEY example configurations, tests, optical
model data, and reaction inputs that SIREN does not load.

MARLEY is distributed under the GNU General Public License version 3. The
upstream license text is preserved both beside and inside the archive as
`COPYING`.
