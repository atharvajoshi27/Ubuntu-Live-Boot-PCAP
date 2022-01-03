#!/bin/bash
if [ $# -ne 1 ]
then
	echo "Enter no. of processes to execute."
	exit 1
fi
gcc serial_mul.c
sudo perf stat -e cycles,instructions,cache-references,cache-misses,bus-cycles,instructions,branches,branch-misses,page-faults,context-switches,cpu-migrations ./a.out

gcc parallel_mul.c -lpthread
sudo perf stat -e cycles,instructions,cache-references,cache-misses,bus-cycles,instructions,branches,branch-misses,page-faults,context-switches,cpu-migrations ./a.out

gcc matrix_omp.c -fopenmp
sudo perf stat -e cycles,instructions,cache-references,cache-misses,bus-cycles,instructions,branches,branch-misses,page-faults,context-switches,cpu-migrations ./a.out

mpicc matrix-blocking.c
sudo perf stat -e cycles,instructions,cache-references,cache-misses,bus-cycles,instructions,branches,branch-misses,page-faults,context-switches,cpu-migrations mpirun --allow-run-as-root ./a.out

mpicc matrix-non-blocking.c
sudo perf stat -e cycles,instructions,cache-references,cache-misses,bus-cycles,instructions,branches,branch-misses,page-faults,context-switches,cpu-migrations mpirun --allow-run-as-root ./a.out

rm a.out
