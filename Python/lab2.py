def cut(x, a, b):
    """Updates list x to meet a =< x[i] =< b"""
    return [min(max(v, a), b) for v in x]


ml = [-1, 1, 2, 3, 4]
lb = 0
ub = 2

print(cut(ml, lb, ub))
