limit = 10000000
patterns_num = 100000 #adjust
patterns_num_len = len(str(patterns_num))
patterns = list()
for i in xrange(0,patterns_num ):
    patterns.append('{0:b}'.format(i))

with open('littera.in','w+') as f:
    f.write(str(patterns_num) + '\n')

    for i in xrange(0, patterns_num):
        patterns.append('{0:b}'.format(i))
