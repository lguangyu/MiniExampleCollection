#!/usr/bin/env python3

import foo

print(dir(foo.Foo))
print(foo.Foo.__doc__)

f = foo.Foo(None, 2)

print(f.get_bar())
print(f.get_hundred())
print(f.get_a())
f.set_a(30)
print(f.get_a())
print(f.a)
f.a = 1
print(f.a)
f.set_bar("as")
print(f.bar)
print(f.get_bar())
