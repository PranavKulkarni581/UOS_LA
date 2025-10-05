#!/bin/bash
if [ $# -lt 2 ]; then echo "Error: Provide two or more filenames"; exit 1; fi
for f in "$@"; do if [ ! -f "$f" ]; then echo "File $f does not exist"; exit 1; fi; done
cat "$@" > concatenated.out
echo "Files concatenated into concatenated.out"
