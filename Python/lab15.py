import time
import httplib


class Timer:
    def __enter__(self):
        self.start = time.time()
        return self

    def __exit__(self, *args):
        self.end = time.time()
        self.interval = self.end - self.start
        print 'Execution time: %.03f sec.' % self.interval
        return self


try:
    with Timer() as t:
        #time.sleep(1.5)
        conn = httplib.HTTPConnection('google.com')
        conn.request('GET', '/')
except:
    print 'Connection failed'