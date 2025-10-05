#!/bin/bash
echo "Enter 10 numbers separated by spaces:"
read -a arr
if [ ${#arr[@]} -ne 10 ]; then echo "Please enter exactly 10 numbers"; exit 1; fi
sorted=($(for i in "${arr[@]}"; do echo $i; done | sort -n))
echo "Sorted numbers: ${sorted[@]}"
