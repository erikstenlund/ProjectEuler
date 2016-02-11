fibo = [1, 1]
i = 0

nextFibo = fibo[i] + fibo[i + 1]
while nextFibo <= 4000000 :
	fibo.append(nextFibo)
	i += 1
	nextFibo = fibo[i] + fibo[i + 1]

print sum([x for x in fibo if x % 2 == 0])
