import re
import subprocess

with open("version.txt", "r") as f:
    version = f.read().strip()

match = re.match(r"(\d+)\.(\d+)\.(\d+)+", version)
if not match:
    raise Exception("Invalid Semver")

major, minor, patch = match.groups()
# patch = str(int(patch) + 1)

build = subprocess.check_output(
    ["git", "rev-list", "--count", "HEAD"],
    encoding="utf-8"
).strip()

version = f"{major}.{minor}.{patch}"
with open("version.txt", "w") as f:
    f.write(f"{version}+build-{build}")
