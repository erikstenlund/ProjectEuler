from math import ceil, sqrt
import sys

def primeSum(n):
    isPrime = [True] * (n + 1)
    s = 0
    for i in range(2, ceil(sqrt(n))):
        if isPrime[i] == True:
            j = i**2
            s += i
            while j <= n:
                isPrime[j] = False
                j += i
    for i in range(ceil(sqrt(n)) + 1, n):
        if isPrime[i] == True:
            s += i
    return s
        

print (primeSum(int(sys.argv[1])))

