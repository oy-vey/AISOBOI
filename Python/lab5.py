def plural(subject, amount):
    if amount == 1:
        return subject
    else:
        return subject + 's'


def hanging_bottles(amount):
    numbers = {0: 'no', 1: 'one', 2: 'two', 3: 'three', 4: 'four', 5: 'five',
               6: 'six', 7: 'seven', 8: 'eight', 9: 'nine', 10: 'ten'}
    return "%s green %s" % (numbers[amount], plural('bottle', amount)) + " hanging on the wall,"


def what_if(bottles_left):
    if bottles_left != 0:
        one, two = ("And i", '')
    else:
        one, two = ('I', ' that')
    return "%sf%s one green bottle should accidentally fall," % (one, two)


def song(bottles):
    while bottles != 0:
        for _ in [0, 1]:
            print(hanging_bottles(bottles).capitalize())
        print(what_if(bottles - 1))
        print("There'll be " + hanging_bottles(bottles - 1))
        bottles -= 1
        print()

song(10)
