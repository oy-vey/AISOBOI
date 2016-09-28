def collatz(x):
    r = [str(x)]
    while x != 1:
        x = x // 2 if x % 2 == 0 else 3 * x + 1
        r.append(str(x))
    return '->'.join(r)

x = int(input('Please, enter number: '))
print(collatz(x))
