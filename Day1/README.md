## [AoC Day 1](https://adventofcode.com/2020/day/1)

This solution contains a very basic doubly-linked list implementation that 
iterates through the input data and adds each entry to the list as an int.

It then does three nested loops, iterating through the list n^3 times to find 
the matching entires. This is not efficient, but as the sample data was very small,
this is more than sufficient. If the sample data were bigger, I would probably 
use some kind of sorting to lower the time complexity.
