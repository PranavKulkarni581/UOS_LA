#!/bin/bash
read -p "Enter expression (e.g. 2+3 or 4 * 5): " expr
result=$(echo "$expr" | bc -l 2>/dev/null)
if [ $? -ne 0 ]; then
  echo "Invalid expression"
else
  echo "Result: $result"
fi
