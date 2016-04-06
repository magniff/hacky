from distutils.core import setup, Extension


hacky_module = Extension('hacky', sources=['hacky.c'])


setup(
    name='hacky',
    author='magniff',
    version='0.0.2',
    url='https://github.com/magniff/hacky',
    description='Low level tinkering utils.',
    ext_modules=[hacky_module]
)
