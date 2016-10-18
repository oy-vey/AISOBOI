from math import sqrt
from itertools import chain

N = 100000

primes = [i for i in chain([2], range(3, N, 2)) if all([i % d for d in range(2, int(sqrt(i) + 1))])]
print(primes)


primes = [x for x in range(2, N) if x not in [j for i in range(2, 8) for j in range(i*2, N, i)]]
print(primes)
