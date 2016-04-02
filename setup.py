from distutils.core import setup, Extension


hacky_module = Extension('hacky', sources = ['hacky.c'])


setup(
    name='hacky',
    author='magniff',
    version='0.0.1',
    description='Hacky!',
    ext_modules=[hacky_module]
)

