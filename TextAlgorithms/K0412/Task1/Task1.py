def ReadTextData(file):
    '''
    N
    abc...N
    abc...N
    '''
    with open(file, 'r') as f:
        N = int(f.readline().strip())
        text = f.readline(N).strip()
        trash = f.readline()
        pattern = f.readline(N).strip()
    return N, text, pattern


N, text, pattern = ReadTextData('littera.in')


def zfun(s):
     out = []
     if not s: return out
     i, slen = 1, len(s)
     out.append(slen)
     while i < slen:
         left, right = 0, i
         while right < slen and s[left] == s[right]:
             left += 1
             right += 1
         out.append(left)
         i += 1
     return out

z = zfun(text + '$' + pattern + pattern)
ans = -1
for i in range(N + 1, 2 * N + 2):
    if (z[i] >= N):
        ans = 2 * N + 1 - i


with open('littera.out','w+') as f:
    f.write(str(ans))