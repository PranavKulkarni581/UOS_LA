#!/bin/bash
if [ $# -ne 1 ]; then echo "Usage: $0 wonderland.txt"; exit 1; fi
tr '[:upper:]' '[:lower:]' < "$1" | tr -c "[:alnum:]" "[\n*]" | grep -v '^$' | sort | uniq -c | sort -nr
