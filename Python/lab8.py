from itertools import chain

N = 1000

primes = [i for i in chain([2], range(3, N, 2)) if all([i % d for d in range(2, int(i**0.5 + 1))])]
print(primes)
