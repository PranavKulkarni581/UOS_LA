#!/bin/bash
echo "Partitions and sizes:"
lsblk -o NAME,SIZE,TYPE,MOUNTPOINT
echo
echo "Disk usage (df -h):"
df -h
