# HACKY
Python hacking suite.

## INSTALLATION
```bash
python setup.py install
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
* More stuff soon. 
