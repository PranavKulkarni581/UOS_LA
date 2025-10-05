#!/bin/bash
if [ $# -lt 3 ]; then echo "Usage: $0 <host> <user> <remote-file>"; exit 1; fi
host="$1"; user="$2"; remote="$3"
lftp -c "open -u $user $host; get $remote"
