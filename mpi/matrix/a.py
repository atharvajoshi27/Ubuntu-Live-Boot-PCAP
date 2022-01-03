N = 1024
n = N * N
print(f"n = {n}")
l1 = []
l2 = []
import random
random.seed(42)
for i in range(n):
	l1.append(random.randint(0,64))
	l2.append(random.randint(0,64))

with open("matrix.h", "a+") as f:
	f.write(f"#define N {N}\n\n")
	f.write(f"#define N_THREADS 8\n\n")
	
	f.write(f"int A[N][N] =  ")
	f.write("{")
	for i in range(len(l1)):
		f.write(f"{l1[i]}")
		if i != len(l1)-1:
			f.write(", ")
		if (i+1) % 32 == 0:
			f.write("\n")
	f.write("};\n\n")
	f.write(f"int B[N][N] = ")
	f.write("{")
	for i in range(len(l2)):
		f.write(f"{l2[i]}")
		if i != len(l2)-1:
			f.write(", ")
		if (i+1) % 32 == 0:
			f.write("\n")
	f.write("};\n")
