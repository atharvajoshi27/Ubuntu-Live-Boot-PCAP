#include <stdio.h>
#include <mpi.h>

double f(double x){
	return x * x;
}

double actual_area_under_f(double a, double b){
	return (b*b*b - a*a*a) / 3.0;
}

double trapezoid_area(double l, double r, int n, double del_x) {
	int i;
	double area_approx, x;
	
	area_approx = (f(l) + f(r)) / 2.0;
	for (i = 1; i < n; i++) {
		x = l + i * del_x;
		area_approx += f(x);
	}
	area_approx = area_approx * del_x;
	return area_approx;
}

int main(int argc, char *argv[]) {
	int id, nprocs, N = 1024, n, process_id; // area divided into n trapezoids
	double A = 0.0, B = 3.0, h, a, b; // A, B actual
	double my_area, total_area, actual_area;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	h = (B-A) / N; // width of a trapezoid
	n = N / nprocs; // no. of trapezoids per process
	a = A + id * n * h; // a for current process
	b = a + n * h; // b for current process
	my_area = trapezoid_area(a, b, n, h); // calculate integral for current process
	if (id != 0) { // slave processes
		MPI_Send(&my_area, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	} 
	else { // cosider process 0 as root process
		total_area = my_area; // add areas from all other processes
		for (process_id = 1; process_id < nprocs; process_id++) {
			MPI_Recv(&my_area, 1, MPI_DOUBLE, process_id, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			total_area += my_area;
		}    
	}
	if (id == 0){
		actual_area = actual_area_under_f(A, B);
		printf("No. of trapezoids : %d\n", N);
		printf("No. of processes : %d\n", nprocs);
		printf("Trapezoids per process : %d\n", n);
		
		printf("Using Trapezoidal rule integral of f from %f to %f = %.4f\n", A, B, total_area);
		printf("Actual area : %.4f\n", actual_area);
	}
	
	MPI_Finalize();
	return 0;
}



