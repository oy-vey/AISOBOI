def format_print(x, level=0):
    xtype = type(x)
    brackets = {list: '[]', tuple: '()', set: '()', dict: '{}'}
    if xtype in [dict]:
        return ('\t' * (level - (1 * level))) + brackets[xtype][0] + '\n' + ''.join(['\t' * (level + 1)+ i + ':' + format_print(x[i], level + 1) + ',\n' for i in x]) + ('\t' * level) + brackets[xtype][1]
    elif xtype in brackets.keys():
        return ('\t' * (level - (1 * level))) + brackets[xtype][0] + '\n' + ''.join(['\t' * (level+1) + format_print(i, level + 1) + ',\n' for i in x]) + ('\t' * level) + brackets[xtype][1]
    else:
        return str(x)




l = [1, 2, 3]
d = {1:'a', 2:'b', 3:'c'}
t = {1, 2, 3}
s = (1, 2, 3)


print(format_print(123))

