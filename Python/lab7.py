
N = 20
result = [(x, y, z) for x in range(1, N) for y in range(x + 1, N) for z in range(y + 1, N) if x * x + y * y == z * z]
print(result)