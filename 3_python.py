import time

st = time.clock()
num = 600851475143
primes = []
p = 2
while True:
	for i in range(2, p):
		if p % i == 0:
			break
	else:
		primes.append(p)
		if num % p == 0:
			num /= p
			
			if num == 1:
				break

	p += 1

print p, time.clock() - st