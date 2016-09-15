import sys

def collatz(x):
    r = [str(x)]
    while x != 1:
        if x % 2 == 0:
            x = x // 2
        else:
            x = 3 * x + 1
        r.append(str(x))
    return '->'.join(r)

x = int(sys.stdin.read())
print(collatz(x))
