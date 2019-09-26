#!/bin/bash
 find . -name "*$1"  -printf '%s %p\n' |
 sort -nr |
 head -$2 |
 awk '{ x += $1 ; print $0 } END { print "total bytes: " x }'
