import numpy

elements = numpy.fromfile("input.bin", dtype='uint64', count=1)
mm = numpy.memmap("input.bin", offset=8, dtype='uint64', mode='r+')
mm.sort()
output = numpy.append(elements, mm)
output.tofile("output.bin")

print(output)