"""distutils.command.clean

Implements the Distutils 'clean' command."""

# contributed by Bastian Kleineidam <calvin@cs.uni-sb.de>, added 2000-03-18

__revision__ = "$Id$"

import os
from distutils.core import Command
from distutils.dir_util import remove_tree
from distutils import log

class clean(Command):

    description = "clean up temporary files from 'build' command"
    user_options = [
        ('build-base=', 'b',
         "base build directory (default: 'build.build-base')"),
        ('build-lib=', None,
         "build directory for all modules (default: 'build.build-lib')"),
        ('build-temp=', 't',
         "temporary build directory (default: 'build.build-temp')"),
        ('build-scripts=', None,
         "build directory for scripts (default: 'build.build-scripts')"),
        ('bdist-base=', None,
         "temporary directory for built distributions"),
        ('all', 'a',
         "remove all build output, not just temporary by-products")
    ]

    boolean_options = ['all']

    

# class clean
