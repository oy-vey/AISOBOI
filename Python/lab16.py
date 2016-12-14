def myxrange(begin, end=None, step=1):
    (start, stop) = (0, begin) if end is None else (begin, end)
    while start != stop:
        yield start
        start += step


print(list(myxrange(-1, -8, -1)))
print(list(range(-1, -8, -1)))
