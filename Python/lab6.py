from math import sqrt


def prime_factorization(n):
    d = 2
    primes = dict()  # number:power
    while d <= sqrt(n):
        if n % d == 0:
            primes[d] = primes.get(d, 0) + 1
            n //= d
        else:
            d += 1
    if n != 1:
        primes[n] = primes.get(n, 0) + 1
    return [[x, y] for x, y in primes.items()]


for i in range(1, 10000):
    print(i, ':', prime_factorization(i))
