def cut(x , a, b):
    """Updates list x to meet a =< x[i] =< b"""
    return [min(max(v, a), b) for v in x]


x = [-1, 1, 2, 3, 4]
a = 0
b = 3

print(cut(x, a, b))