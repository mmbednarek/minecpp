#!/usr/bin/python3
import sys
name = sys.argv[1]

out_str = ''
upper = True
for ch in name:
    if ch == '_':
        upper = True
        continue

    if upper:
        out_str += ch.upper()
        upper = False
    else:
        out_str += ch

print(out_str)