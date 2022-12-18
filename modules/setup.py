from distutils.core import setup, Extension

module1 = Extension('ASCIImodule',
                    define_macros = [('MAJOR_VERSION', '1'),
                                     ('MINOR_VERSION', '0')],
                    include_dirs = ['/usr/local/include'],
                    libraries = ['pthread'],
                    library_dirs = ['/usr/local/lib'],
                    sources = ['modules/interface.c', 'modules/module.c'])

setup (name = 'ASCIImodule',
       version = '1.0',
       description = 'This is a package for generating ASCII art',
       author = 'Patryk Korycki',
       author_email = '01169041@pw.edu.pl',
       url = 'https://gitlab-stud.elka.pw.edu.pl/pkorycki/ascii-player',
       long_description = '''
This is a package for generating ASCII art
''',
       ext_modules = [module1])