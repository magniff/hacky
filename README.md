# HACKY
Python hacking suite.

## INSTALLATION
Tested on CPython 3.4
```bash
python setup.py install
```
or
```bash
pip install hacky
```

## EXAMPLES
* Class transplantation:
```python
>>> import hacky
>>> hacky.set_class(100, type('MyInt', (int,), {'__repr__': lambda self: "hello from hacky"}))
hello from hacky
>>> 100
hello from hacky
>>> 
```

* Messing around with tp_flags:
```python
>>> from types import FunctionType
>>> import hacky
>>> hacky.set_flags(
        FunctionType,
        hacky.get_flags(FunctionType) | (1 << 10)
    )
<class 'function'>
# you can now subclass function type
>>> class T(FunctionType): pass
>>>
```

* Make your class final:
```python
>>> hacky.set_flags(int, hacky.get_flags(int) ^ (1 << 10))
<class 'int'>
>>> class T(int): pass
TypeError: type 'int' is not an acceptable base type
```

* Read process's memory. Lets examine memory around `int` object `100`.
```python
>>> [hacky.read_memory_in(id(100)+shift) for shift in range(20)]
[7, 0, 0, 0, 0, 0, 0, 0, 192, 228, 158, 0, 0, 0, 0, 0, 1, 0, 0, 0]
>>> import struct
>>> [int(item) for item in struct.pack('<I', id(int))]
[192, 228, 158, 0]
```
There are 7 links on this instance and also we get correct address of type `int` located in memory.

* Modify process's memory:
```python
>>> hacky.write_memory_in(id(100)+24, 200)
>>> 100
200
```

* Inject attr at type`s dictionary
```python
>>> object_dict = hacky.fetch_dict(object)
>>> object_dict["foo"] = "hello world"
>>> (100).foo
'hello world'
>>> "hello world".foo
'hello world'
>>> (lambda x: x).foo
'hello world'
```

* More stuff soon. 
