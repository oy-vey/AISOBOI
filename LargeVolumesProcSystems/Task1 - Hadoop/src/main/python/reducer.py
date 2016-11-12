#!/usr/bin/env python

from operator import itemgetter
import sys

current_vertex = None
current_sum = 0
vertex = None

# input comes from STDIN
for line in sys.stdin:
    # remove leading and trailing whitespace
    line = line.strip()

    # parse the input we got from mapper.py
    vertex, sum = line.split('\t', 1)

    # convert sum (currently a string) to int
    try:
        sum = int(sum)
    except ValueError:
        # sum was not a number, so silently
        # ignore/discard this line
        continue

    # this IF-switch only works because Hadoop sorts map output
    # by key (here: vertex) before it is passed to the reducer
    if current_vertex == vertex:
        current_sum += sum
    else:
        if current_vertex:
            # write result to STDOUT
            print '%s\t%s' % (current_vertex, current_sum)
        current_sum = sum
        current_vertex = vertex

# do not forget to output the last vertex if needed!
if current_vertex == vertex:
    print '%s\t%s' % (current_vertex, current_sum)