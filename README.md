# HACKY
Python hacking suit.

## INSTALLATION
```bash
python setup install
```

## EXAMPLE
* Class transplantation:
```python
>>> import hacky
>>> hacky.set_class(100, type('MyInt', (int,), {'__repr__': lambda self: "hello from hacky"})
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
* More stuff soon. 
