"""Check this immutable ME export; this is not a general overlap checker."""
import hashlib
import json
from pathlib import Path
import xml.etree.ElementTree as ET

ASSET = Path(__file__).with_name("numi_ME_g4export_2026-09-17.gdml")
SHA256 = "730466f287196d65a7fee074203014471faee6be0fbfa3da4769046d92355ed7"


def validate(path=ASSET):
    path = Path(path)
    assert hashlib.sha256(path.read_bytes()).hexdigest() == SHA256, "Asset hash differs"
    root = ET.parse(path).getroot()
    solids = {e.get("name"): e for e in root.find("solids")}
    volumes = {e.get("name"): e for e in root.find("structure")}
    definitions = {e.get("name"): e for e in root.find("define")}

    def vector(element, tag):
        node = element.find(tag)
        ref = element.find(tag + "ref")
        if ref is not None:
            node = definitions[ref.get("ref")]
        if node is None:
            return (0., 0., 0.)
        if tag == "position":
            assert node.get("unit", "mm") == "mm"
        return tuple(float(node.get(axis, "0")) for axis in "xyz")

    rows = []

    def walk(volume, offset=(0., 0., 0.), rotated=False):
        for pv in volume.findall("physvol"):
            local = vector(pv, "position")
            position = tuple(a+b for a, b in zip(offset, local))
            has_rotation = rotated or any(vector(pv, "rotation"))
            child = volumes[pv.find("volumeref").get("ref")]
            rows.append((pv, child, position, has_rotation))
            walk(child, position, has_rotation)

    walk(volumes[root.find("setup/world").get("ref")])

    def selected(prefix):
        result = [r for r in rows if r[0].get("name", "").startswith(prefix)]
        assert result and not any(r[3] for r in result), "Expected unrotated ME placements"
        return result

    fins = selected("TGT10x")
    assert len(fins) == 48
    assert sorted(int(r[0].get("copynumber", "0")) for r in fins) == list(range(48))
    fin_z = sorted(r[2][2] for r in fins)
    assert all(abs(z-(-1363.5+24.5*i)) < 1e-7 for i, z in enumerate(fin_z))
    horn2, = selected("pvMHorn2Mother")
    assert abs(horn2[2][2]-19180.) < 1e-7

    def z_limits(solid):
        # Only the unrotated target envelope union and horn polycone are needed.
        if solid.tag in ("box", "tube"):
            assert solid.get("lunit", "mm") == "mm"
            half = float(solid.get("z"))/2
            return -half, half
        if solid.tag == "polycone":
            assert solid.get("lunit", "mm") == "mm"
            zs = [float(p.get("z")) for p in solid.findall("zplane")]
            return min(zs), max(zs)
        assert solid.tag == "union", solid.tag
        assert not any(vector(solid, "rotation"))
        a = z_limits(solids[solid.find("first").get("ref")])
        b = z_limits(solids[solid.find("second").get("ref")])
        dz = vector(solid, "position")[2]
        return min(a[0], b[0]+dz), max(a[1], b[1]+dz)

    def bounds(row):
        local = z_limits(solids[row[1].find("solidref").get("ref")])
        return [v+row[2][2] for v in local]

    target, = selected("TargetMotherVol")
    horn1, = selected("pvMHorn1Mother")
    target_z, horn1_z = bounds(target), bounds(horn1)
    gap = horn1_z[0]-target_z[1]
    assert gap > 0, "Target and horn-1 axial envelopes overlap"
    assert any(r[0].get("name", "").startswith("Horn1UpstrSubSect0_P") for r in rows)
    return dict(sha256=SHA256, target_fins=len(fins), fin_centres_z_mm=[min(fin_z), max(fin_z)],
                horn2_origin_z_mm=horn2[2][2], target_envelope_z_mm=target_z,
                horn1_envelope_z_mm=horn1_z, envelope_gap_mm=gap)


if __name__ == "__main__":
    print(json.dumps(validate(), indent=2))
