from re import sub

def ReadTextData(file):
    '''
	TEXT
	Pattern
	'''
    with open(file, 'r') as f:
        text = f.readline().strip()
        pattern = f.readline().strip()

    return text, pattern

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


def kmp(P, T):
    S = P + '$' + T
    s = PrefixFunction(S)
    result = list()
    for i in xrange(len(P) + 1, len(S)):
        if s[i] == len(P):
            result.append(i - 2 * len(P) )
    return result


text, pattern = ReadTextData('input.txt')

new_text = sub("[a-z]", '.', text)
new_pattern = sub("[a-z]", '.', pattern)

matches = kmp(new_pattern,new_text)


if (not matches):
    ans = "Looks like something new."
else:
    for i in matches:
        subs = dict()
        for j in xrange(0, len(pattern)):
            if pattern[j] not in subs.keys():
                subs[pattern[j]] = text[i + j]
            t = text[i + j]
            p = subs[pattern[j]]
            if t != p:
                ans = "Looks like something new."
                break
            elif (j == len(pattern) - 1):
                ans = "Plagiarism was detected at position " + str(i + 1) + "."
                break
        if ans[0] == "P":
            break
with open('output.txt','w+') as f:
    f.write(str(ans))
