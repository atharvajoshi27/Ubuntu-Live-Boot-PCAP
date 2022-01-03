import random

n = int(input('Enter N : '))
with open('matrix.txt', 'w+') as f:
	for i in range(n):
		for j in range(n):
			f.write(str(random.randint(-42, 43)))
			f.write(' ')
		f.write('\n')
