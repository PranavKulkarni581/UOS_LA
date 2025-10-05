#!/bin/bash
if [ $# -ne 1 ]; then echo "Usage: $0 <filename>"; exit 1; fi
file="$1"
if [ -x "$file" ]; then echo "File is executable. Removing execute permission."; chmod -x "$file"; else echo "File is not executable."; fi
