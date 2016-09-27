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
            n = int(line.split("=")[1])
        elif 'time' in line:
            method = line.split(":")[0][4:]
            value = float(line.split(":")[1])
            results[method] = results.get(method, list())
            pair = (n, value)
            results[method].append(pair)
    return results

results2000 = read_log_file("C:\\Users\\Danon\\PycharmProjects\\AISOBOI\\ModernAlgorithms\\1000-2000.log")
results1100 = read_log_file("C:\\Users\\Danon\\PycharmProjects\\AISOBOI\\ModernAlgorithms\\1000-1100.log")



