import string
from re import sub

def ReadTextData(file):
    with open(file, 'r') as f:
        data = f.read().splitlines()
        N = int(data[0])
        origin = ''.join(data[1:])[0:N]
        encryption = ''.join(data[1:])[N:2*N]


    return  N, origin, encryption


def PrefixFunction(pattern):
    border = 0
    s = [0]*(len(pattern))
    for i in xrange(1, len(pattern)):
        while (border > 0) and (pattern[i] != pattern[border]):
            border = s[border - 1]
        if pattern[i] == pattern[border]:
            border += 1
        else:
            border = 0
        s[i] = border
    return s

def AllCyclicStrings(string):
    result = []
    for i in xrange(0,len(string)):
        string = string[1:] + string[0]
        result.append(string)
    return  result

N, origin, encryption = ReadTextData('littera.in')


origin = sub("[^a-z]", '', origin.lower())
encryption = sub("[^a-z]", '', encryption.lower())

keys = ""
for i in xrange(0, len(origin)):
    if string.lowercase.index(encryption[i]) - string.lowercase.index(origin[i]) < 0:
        a = string.lowercase.index(encryption[i]) - string.lowercase.index(origin[i]) + 25
    else:
        a = string.lowercase.index(encryption[i]) - string.lowercase.index(origin[i]) - 1
    keys += string.lowercase[a]

p = PrefixFunction(keys)
#print p
res = ""


for i in xrange(len(p) - 1, -1, -1):
    if p[i]==0:
        res = keys[:i + 1]
        break

result = AllCyclicStrings(res)
result.sort()


with open('littera.out','w+') as f:
    f.write(str(result[0]))


