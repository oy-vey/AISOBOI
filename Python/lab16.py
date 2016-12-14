def myxrange(begin, end=None, step=1):
    (start, stop) = (0, begin) if end is None else (begin, end)
    if (start < stop and step < 0) or (start > stop and step > 0):
        raise StopIteration
    elif start < stop:
        while start < stop:
            yield start
            start += step
    elif start > stop:
        while start > stop:
            yield start
            start += step


print list(myxrange(10))
print list(range(10))

print list(myxrange(1, 10, 2))
print list(range(1, 10, 2))

print list(myxrange(10, 0, -2))
print list(range(10, 0, -2))

print list(myxrange(0, 10, -2))
print list(range(0, 10, -2))


