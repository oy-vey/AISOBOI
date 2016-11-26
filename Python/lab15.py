import time
import httplib


class Timer:
    def __enter__(self):
        self.start = time.clock()
        return self

    def __exit__(self, *args):
        self.end = time.clock()
        self.interval = self.end - self.start
        print 'Execution time: %.03f sec.' % self.interval


try:
    with Timer() as t:
        conn = httplib.HTTPConnection('google.com')
        conn.request('GET', '/')
except:
    print "Connection failed"



