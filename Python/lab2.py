def cut(x , a, b):
    """Updates list x to meet a >= x[i] >= b"""
    for i, v in enumerate(x):
        x[i] = min(max(v, a), b)
    return x


x = [-1, 1, 2, 3, 4]
a = 0
b = 3

print(cut(x, a, b))