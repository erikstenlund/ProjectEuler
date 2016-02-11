n = input("Enter a number")

print sum([x for x in range(n) if x % 3 == 0 or x % 5 == 0])
