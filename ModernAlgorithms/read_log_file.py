def read_log_file (path):
    '''
    Log file format:

    n = 1000
    timeSimple:  0.8932
    timeBlock:  0.5754
    timeSwapped:  0.3424

    :return
    results = {Simple: [(1000, 0.8932), ... ,( )], Block: [(1000, 0.8932), ... ,( )], Swapped: [(1000, 0.8932), ... ,( )]}
    '''

    results = dict()
    for line in open(path):
        if 'n = ' in line:
            print(line.split("="))

read_log_file("C:\\Users\\Daniil_Skokleenko\\Desktop\\1000-1100.log")

