def cumsum(x: list):
    """Returns cumulative sums of a list"""
    s = [0]
    for i, v in enumerate(x):
        a = v + s[i]
        s.append(a)
    return s


x = [1, 2, 3, 4]

print(cumsum(x))
