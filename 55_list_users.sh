#!/bin/bash
if command -v finger >/dev/null 2>&1; then finger
else who
fi
