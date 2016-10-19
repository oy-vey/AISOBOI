from math import sqrt, floor
from itertools import chain

N = 4

primes = [i for i in chain([2], range(3, N, 2)) if all([i % d for d in range(2, floor(sqrt(i) + 1))])]
print(primes)

primes = [i for i in chain([2], range(3, N, 2)) if all([i % d for d in range(2, int(sqrt(i) + 1))])]
print(primes)