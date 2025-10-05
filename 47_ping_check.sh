#!/bin/bash
host=${1:-8.8.8.8}
if ping -c 1 -W 2 "$host" >/dev/null 2>&1; then
  echo "Network reachable (ping to $host successful)"
  exit 0
else
  echo "Network unreachable (ping to $host failed)"
  exit 1
fi
