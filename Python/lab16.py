def myxrange(begin, end=None, step=1):
    (start, stop) = (0, begin) if end is None else (begin, end)
    if begin > end:
        (start, stop) = (stop, start)
    while start < stop:
        yield start
        start += step


print list(myxrange(10, 0, -2))
print list(xrange(10, 0, -2))
