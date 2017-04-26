def ReadTextData(file):
	'''
	N
	Pattern1
	.
	.
	.
	PatternN
	'''
	with open(file, 'r') as f:
		N = int(f.readline().strip())
		patterns = []
		for i in xrange(0, N):
			patterns.append(f.readline().strip())

	return N, patterns

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
	String = P + '$' + T
	s = PrefixFunction(String)
	result = list()
	for i in xrange(len(P) + 1, len(String)):
		if s[i] == len(P):
			result.append(i - 2 * len(P))
			break
	return result


N, patterns = ReadTextData('littera.in')
#patterns = ['abcd', 'abc','bce', 'bcd'] # ['abc','bcd','bce', 'abcd']
ans = 'NO'
patterns.sort(key=lambda x: (len(x), x.lower()))
#print(patterns)
for i in range(0, len(patterns)):
	pattern = patterns[0]
	patterns.pop(0)
	text = '$'.join(patterns)
	if kmp(pattern, text):
		ans = 'YES'
		break

with open('littera.out','w+') as f:
	f.write(str(ans))