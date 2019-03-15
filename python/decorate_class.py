class Decorator(object):
	def __init__(self, arg, *ka, **kw):
		super(Decorator, self).__init__(*ka, **kw)
		self.arg = arg

	def __call__(self, cls):
		class wrapper(cls):
			arg = self.arg
			def __init__(_self, *ka, **kw):
				super(wrapper, _self).__init__(*ka, **kw)
				# so something here

			def method(_self):
				pass
		return wrapper


@Decorator("arg")
class Foo(object):
	def __init__(self, arg1, arg2):
		super(Foo, self).__init__()
		self.arg1 = arg1
		self.arg2 = arg2


if __name__ == "__main__":
	foo = Foo("arg1", "arg2")
