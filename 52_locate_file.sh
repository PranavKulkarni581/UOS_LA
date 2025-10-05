#!/bin/bash
if [ $# -lt 1 ]; then echo "Usage: $0 <filename>"; exit 1; fi
name="$1"
if command -v locate >/dev/null 2>&1; then
  locate "$name" | head -n 50
else
  find / -name "$name" 2>/dev/null | head -n 50
fi
