def format_print(x, level=0):
    xtype = type(x)
    brackets = {list: '[]', tuple: '()', set: '{}', dict: '{}'}
    if xtype in [dict]:
        return ('\t' * (level - (1 * level))) + brackets[xtype][0] + '\n' + \
                    ''.join(['\t' * (level + 1) + str(i) + ':' + format_print(x[i], level + 1) + ',\n' for i in x]) + \
               ('\t' * level) + brackets[xtype][1]
    elif xtype in brackets.keys():
        return ('\t' * (level - (1 * level))) + brackets[xtype][0] + '\n' + \
                    ''.join(['\t' * (level+1) + format_print(i, level + 1) + ',\n' for i in x]) + \
               ('\t' * level) + brackets[xtype][1]
    else:
        return str(x)



print(format_print([1, {'a': [1, 2], 'b': 'hi'}]))

