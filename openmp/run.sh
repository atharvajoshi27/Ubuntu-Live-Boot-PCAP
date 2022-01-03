#!/bin/bash
if [ $# -ne 1 ]
then
	echo "Enter program name to execute"
	exit 1
fi

gcc $1 -lpthread -fopenmp
sudo perf stat -e cycles,instructions,cache-references,cache-misses,bus-cycles,instructions,branches,branch-misses,page-faults,context-switches,cpu-migrations ./a.out
rm a.out
