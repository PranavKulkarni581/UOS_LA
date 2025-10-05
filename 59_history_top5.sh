#!/bin/bash
history | awk '{$1=""; print substr($0,2)}' | awk '{print $1}' | sort | uniq -c | sort -nr | head -n 5
