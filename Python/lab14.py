class Singleton(object):
    obj = None
    def __new__(cls,*dt,**mp):
       if cls.obj is None:
          cls.obj = object.__new__(cls,*dt,**mp)
       return cls.obj


class Foo(Singleton):
    def __init__(self, arg):
        self.arg = arg
        print arg, 'inited!'
    def test(self):
        print self.arg
Foo(1).test() #=> 1 inited!\n1
Foo().test() #=> 1