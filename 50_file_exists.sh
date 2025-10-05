#!/bin/bash
if [ $# -ne 2 ]; then echo "Usage: $0 <folder> <filename>"; exit 1; fi
folder="$1"; file="$2"
if [ -e "$folder/$file" ]; then echo "File exists: $folder/$file"; else echo "File not found"; fi
