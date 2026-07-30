#!/usr/bin/env python3

from pathlib import Path
import argparse
import numpy as np


def extract_npz(npz_path: Path):
  with np.load(npz_path) as archive:
    for key in archive.files:
      arr = archive[key]
      out_path = npz_path.with_suffix("")
      if len(archive.files) > 1:
        out_path = out_path.with_name(f"{out_path.name}_{key}")
      out_path = out_path.with_suffix(".bin")

      arr.tofile(out_path)
      print(
        f"{npz_path} -> {out_path} "
        f"(shape={arr.shape}, dtype={arr.dtype})"
      )


def process_directory(directory: Path):
  if not directory.exists():
    print(f"Skipping missing directory: {directory}")
    return

  for npz_file in sorted(directory.glob("*.npz")):
    extract_npz(npz_file)


def main():
  parser = argparse.ArgumentParser()
  parser.add_argument(
    "parent_folder",
    help="Folder containing inputs/ and results/ subdirectories",
  )
  args = parser.parse_args()

  parent = Path(args.parent_folder)

  process_directory(parent / "inputs")
  process_directory(parent / "results")


if __name__ == "__main__":
  main()