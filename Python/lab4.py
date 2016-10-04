import re


def reverse(text):
    underscores = [u for u in re.split('[^_]', text) if u != '']
    words = [w for w in re.split('[_]', text) if w != '']
    words.reverse()
    if len(underscores) > len(words):
        start, end = len(words), -1
    elif text[-1] == '_':
        start, end = len(words), 0
    elif text[0] == '_':
        start, end = len(words) - 1, -1
    else:
        start, end = len(words) - 1, 0
    a = 1
    for i in range(start, end, -1):
        words.insert(i, underscores[min(i, len(underscores) - a)])
        a += 1
    return ''.join(words)

print(reverse('_ab__c___d____'))
print(reverse('ab__c___d'))
print(reverse('_ab__c___d'))
print(reverse('ab__c___d____'))
