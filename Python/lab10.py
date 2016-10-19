def format_print(x, level=0):
    argtype = type(x)
    brackets = {list: '[]', tuple: '()', set: '{}', dict: '{}'}
    if argtype in [dict]:
        return ('\t' * (level - (1 * level))) + brackets[argtype][0] + '\n' + \
                    ''.join(['\t' * (level + 1) + str(i) + ':' + format_print(x[i], level + 1) + ',\n' for i in x]) + \
               ('\t' * level) + brackets[argtype][1]
    elif argtype in brackets.keys():
        return ('\t' * (level - (1 * level))) + brackets[argtype][0] + '\n' + \
                    ''.join(['\t' * (level+1) + format_print(i, level + 1) + ',\n' for i in x]) + \
               ('\t' * level) + brackets[argtype][1]
    else:
        return str(x)

print(format_print([1, {'a': [1, 2], 'b': 'hi'}]))

