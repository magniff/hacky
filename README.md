# HACKY
Python hacking suit.

## INSTALLATION
```bash
python setup.py install
```

## EXAMPLE
Only one function available for now `set_class`, checkout:
```python
>>> import hacky
>>> hacky.set_class(100, type('MyInt', (int,), {'__repr__': lambda self: "hello from hacky"})
hello from hacky
>>> 100
hello from hacky
>>> 
```
