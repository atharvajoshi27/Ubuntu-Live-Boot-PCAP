#!/bin/bash
if [ $# -ne 1 ]
then
	echo "Syntax : ./runmpi.sh no.of.processes"
	exit 1
fi

echo "Running hello-world-blocking.c ...."
mpicc hello-world-blocking.c
sudo perf stat mpirun --allow-run-as-root -np $1 a.out


echo -e
echo "Running hello-world-non-blocking.c ...."
mpicc hello-world-non-blocking.c
sudo perf stat mpirun --allow-run-as-root -np $1 a.out

echo -e
echo "Running trapezoid-blocking.c ...."
mpicc trapezoid-blocking.c
sudo perf stat mpirun --allow-run-as-root -np $1 a.out

echo -e
echo "Running trapezoid-non-blocking.c ...."
mpicc trapezoid-non-blocking.c
sudo perf stat mpirun --allow-run-as-root -np $1 a.out
