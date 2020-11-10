# This file is part of the Peano project. For conditions of distribution and
# use, please see the copyright notice at www.peano-framework.org
from .Helper import Overwrite
from .Helper import writeFile
from .CompileMode import CompileMode


import os
import re


import jinja2


class Makefile(object):
  """ Represents the created makefile of a Peano4 project """
  default_overwrite = True


  def __init__(self):
    self.clear()


  def clear(self):
    self.d = {}
    self.d["CXX"]              = ""
    self.d["CXXFLAGS"]         = ""
    self.d["FC"]               = ""
    self.d["FCFLAGS"]          = ""
    self.d["LDFLAGS"]          = ""
    self.d["LIBS"]             = ""
    self.d["DIM"]              = "2"
    self.d["CONFIGUREPATH"]    = "."
    self.d["EXECUTABLENAME"]   = "peano4"
    self.d["FORTRAN_MODULES"]  = {}
    self.set_mode( CompileMode.Debug )
    self.clear_files()


  def set_executable_name(self, fname):
      self.d["EXECUTABLENAME"] = fname


  def clear_files(self):
    self.cppfiles     = []
    self.fortranfiles = []


  def set_dimension(self,dimension):
    self.d["DIM"] = str(dimension)


  def get_configure_path(self):
    """
    Returns the directory where the ./configure script is located
    """
    return self.d["CONFIGUREPATH"]


  def get_source_path(self):
    """
    Returns the directory where the ./configure script is located
    """
    return self.get_configure_path() + "/src"


  def add_header_search_path(self, path ):
    """
     Add the header search path to both the C++ and the Fortran 
     call command.
    """
    self.d["CXXFLAGS"] += " -I" + path
    self.d["FCFLAGS"]  += " -I" + path


  def add_library(self, library_name, library_path="" ):
    """
    If you want to link against a library from Peano, feel free to use
    get_Peano4_source_directory() and hand in a concatenation of this
    path plus a subpath. Otherwise, specify the absolute path where to
    search for. By default, Peano's src directory is in the search
    path.

    A popular invocation including one of Peano's toolboxes is

    project.output.makefile.add_library( "ToolboxFiniteElements2d_trace", project.output.makefile.get_source_path() + "/toolbox/finiteelements" )

    """
    if library_path!="":
      self.d["LIBS"] = "-L" + library_path + " " + self.d["LIBS"]
    self.d["LIBS"] += " -l" + library_name + " "


  def set_mode( self, mode ):
    """
      mode should be of type CompileMode. Pass in

      peano4.output.CompileMode.Debug

      for example
    """
    if mode==CompileMode.Debug:
      self.d["CXX_MODE_FLAGS"]  = "-g -O0 -DPeanoDebug=4"
      self.d["LIBRARY_POSTFIX"] = "_debug"
    elif mode==CompileMode.Asserts:
      self.d["CXX_MODE_FLAGS"]  = "-g -O2 -DPeanoDebug=2"
      self.d["LIBRARY_POSTFIX"] = "_asserts"
    elif mode==CompileMode.Trace:
      self.d["CXX_MODE_FLAGS"]  = "-g -O2 -DPeanoDebug=1"
      self.d["LIBRARY_POSTFIX"] = "_trace"
    elif mode==CompileMode.Release:
      self.d["CXX_MODE_FLAGS"]  = "-O2 -DPeanoDebug=0"
      self.d["LIBRARY_POSTFIX"] = ""
    else:
      assert(False)


  def set_CXX_compiler(self,value):
    self.d["CXX"]           = value


  def set_CXX_flags(self,value):
    self.d["CXXFLAGS"]      = value


  def add_CXX_flag(self,value):
    self.d["CXXFLAGS"]     += " " + value


  def set_Fortran_compiler(self,value):
    self.d["FC"]           = value


  def set_Fortran_flags(self,value):
    self.d["FCFLAGS"]       = value


  def add_Fortran_flag(self,value):
    self.d["FCFLAGS"]      += " " + value


  def set_linker_flags(self,value):
    self.d["LDFLAGS"]       = value + " "


  def parse_configure_script_outcome(self,directory):
    """

    directory should point to the directory which holds the ./configure script.
    It furthermore has to be invoked after configure has passed successfully.
    This script does not accept relative paths. I then search for the subdirector
    src and parse the Makefile there.

    """
    input_file = directory + "/src/Makefile"
    try:
      input = open( input_file, "r" )
      print( "parse configure outcome " + input_file + " to extract compile settings" )
      for line in input:
        if re.match( "CXX *=", line) and line.startswith( "CXX" ):
          compiler = line.split("=")[-1].strip()
          print( "used C++ compiler is " + compiler )
          self.d["CXX"] = compiler
        if re.match( "FC *=", line) and line.startswith( "FC" ):
          compiler = line.split("=")[-1].strip()
          print( "used Fortran compiler is " + compiler )
          self.d["FC"] = compiler
        if re.search( "CXXFLAGS *=", line) and line.startswith( "CXXFLAGS" ):
          flags = line.split("=",1)[1].strip()
          self.d["CXXFLAGS"] += flags
          self.d["CXXFLAGS"] += " "
        if re.search( "FCFLAGS *=", line) and line.startswith( "FCFLAGS" ):
          flags = line.split("=",1)[1].strip()
          self.d["FCFLAGS"] += flags
          self.d["FCFLAGS"] += " "
        if re.search( "LDFLAGS *=", line) and line.startswith( "LDFLAGS" ):
          flags = line.split("=",1)[1].strip()
          self.d["LDFLAGS"] += flags
          self.d["LDFLAGS"] += " "
        if re.search( "LIBS *=", line) and line.startswith( "LIBS" ):
          flags = line.split("=",1)[1].strip()
          self.d["LIBS"] += flags
          self.d["LIBS"] += " "
      self.d["CONFIGUREPATH"] = directory
    except IOError:
      print( """
Error: if you call parse_configure_script_outcome(), please hand over directory where
./configure had been called. You passed """ + directory + """ and the script therefore
did search for a file """ + input_file )



  def add_cpp_file(self,filename):
    """

     Add a new filename. This is basically a set implementation, i.e. you can
     add files multiple times, but they are not inserted multiple times. This
     is important, as the steps add the cpp files. Multiple steps can hold the
     same action, so this action would be created multiple times.

     All the standard Peano 4 routines rely on this function to add their
     generated files to the build environment. Nothing stops you however to
     add more files yourself.

    """
    if self.cppfiles.count(filename)==0:
      self.cppfiles.append( filename )


  def add_Fortran_file(self,filename):
    """

     Add a new filename. This is basically a set implementation, i.e. you can
     add files multiple times, but they are not inserted multiple times. This
     is important, as the steps add the cpp files. Multiple steps can hold the
     same action, so this action would be created multiple times.

     All the standard Peano 4 routines rely on this function to add their
     generated files to the build environment. Nothing stops you however to
     add more files yourself.
     
     Fortran is really picky about the translation order. So you have to add
     the stuff in the right order. Otherwise, Fortran might complain. This is 
     your responsibility. Also, I don't know what happens if you use -j no 
     the generated makefile with Fortran.

    """
    if self.fortranfiles.count(filename)==0:
      self.fortranfiles.append( filename )


  def add_Fortran_files(self,filenames):
    for i in filenames:
      self.add_Fortran_file(i)


  def add_Fortran_module(self,module_name,module_files):
    self.d["FORTRAN_MODULES"][ module_name ] = []
    for i in module_files:
      self.d["FORTRAN_MODULES"][ module_name ].append( i.replace( ".f90", ".o") )
      self.fortranfiles.append(i)
    

  def generate(self,overwrite,directory):
    filename = directory + "/Makefile";
    if writeFile(overwrite,self.default_overwrite,filename):
      print( "write " + filename )

      # files
      self.d[ 'CXX_SOURCES' ]     = self.cppfiles
      
      self.d[ 'FORTRAN_SOURCES' ] = self.fortranfiles


      template_file   = os.path.realpath(__file__).replace( ".pyc", ".template" ).replace( ".py", ".template" )
      template_loader = jinja2.FileSystemLoader(searchpath=os.path.split(template_file)[0])
      templateEnv     = jinja2.Environment(loader=template_loader)
      template        = templateEnv.get_template( os.path.split(template_file)[1] )


      # We first eliminate the precompiled variant, and then we get rid of the
      # postfix in the case where it is a source file
      with open( filename, "w" ) as output:
        output.write( template.render(self.d) )

