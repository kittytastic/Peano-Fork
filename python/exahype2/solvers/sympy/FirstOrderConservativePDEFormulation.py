# This file is part of the ExaHyPE2 project. For conditions of distribution and 
# use, please see the copyright notice at www.peano-framework.org


import sympy


class FirstOrderConservativePDEFormulation:
  """
    
    Helper class to model a hyperbolic PDE in first-order conservative 
    formulation.
    
    To model your PDE, you typically run through a couple of single steps. 
    First, include this package plus sympy. Next, create a new instance
    of this class to which you pass the number of equations in your PDE 
    system, i.e. the number of unknowns you want to develop, plus the 
    dimension.
    
    As a consequence, the solver holds an equation pde which describes the
    pde's right-hand side in the representation
    
    \partial Q(t) + div_x F(Q)
    
    Most people prefer not to work with a vector Q but with some symbolic
    names. Feel free to derive them from Q via constructs similar to
      
    rho = euler.Q[0]
    j = sympy.Array( euler.Q[1:4] )
    E = euler.Q[4]

        
  """
  def __init__(self, unknowns, dimensions ):
    self.unknowns   = unknowns
    self.dimensions = dimensions
    
    self.Q          = sympy.symarray("Q",     (unknowns))
    self.F          = sympy.symarray("F",     (unknowns,dimensions))
    self.eigenvalue = sympy.symarray("alpha", (unknowns,dimensions))
    
    for i in range(0,unknowns):
      self.F[i]          = [0 for i in range(0,dimensions)]
      self.eigenvalue[i] = [0 for i in range(0,dimensions)]
    pass


  def name_Q_entry(self,offset_in_Q,name):
    self.Q[offset_in_Q] = sympy.symbols( name )
    return self.Q[offset_in_Q]


  def name_Q_entries(self,offset_in_Q,cardinality,name):
    new_entry = sympy.symarray(name, cardinality)
    for i in range(0,cardinality):
      self.Q[offset_in_Q+i] = new_entry[i]
    return new_entry


  def __str__(self):
    result = ""
    for i in range(0,self.unknowns):
      result += "d_t " + str( self.Q[i] ) + "(x) + div_x( "
      result += str( self.F[i] )
      result += " ) = 0\n"
    for i in range(0,self.unknowns):
      result += "\lambda _{max," + str( i ) + "}(x) = "
      result += str( self.eigenvalue[i] )
      result += "\n"
    return result


  def implementation_of_mapping_onto_named_quantities(self):
    """
    
      Return the C code that maps the quantities from Q onto
      properly labelled quantities
      
    """
    result = ""
    for i in range(0,self.unknowns):
      result += "const double "
      result += sympy.printing.cxxcode( self.Q[i] )
      result += " = Q[" + str(i) + "];\n"
    return result


  def find_max_eigenvalues(self):
    """
      I use alpha as lambda is already a keyword
    """
    alpha     = sympy.symarray( "alpha", self.unknowns )
    #direction = sympy.symarray( "x",     self.dimensions )
    direction = sympy.symbols( "direction" )
    equation = sympy.diff( self.F[0,0], direction ) + sympy.diff( self.F[0,1], direction ) + sympy.diff( self.F[0,2], direction ) - alpha * sympy.diff( self.Q[0], direction )      
    print( str(equation) )


  def substitute_expression(self,expression,new_expression):
    """
    
      Usually used to set a symbolic variable (expression) to a value 
      (new_expression). We run over all internal expressions and set 
      them accordin
      
    """
    for i in range(0,self.unknowns):
      for d in range(0,self.dimensions):
        self.F[i,d]          = self.F[i,d].subs(expression,new_expression)
        self.eigenvalue[i,d] = self.eigenvalue[i,d].subs(expression,new_expression)


  def implementation_of_flux(self):
    """
      Return implementation for flux along one coordinate axis (d) as C code.
    """
    result  = self.implementation_of_mapping_onto_named_quantities()
    result += "switch( normal ) {\n"
    for d in range(0,self.dimensions):
      result += "  case " + str(d) + ":\n"
      for i in range(0,self.unknowns):
        result += sympy.printing.cxxcode( self.F[i,d].evalf(), assign_to="F[" + str(i) + "]" )
        result += "\n"
      result += "  break;\n"
    result += "}\n"
    return result


  def implementation_of_eigenvalues(self):
    """
      Return implementation for flux along one coordinate axis (d) as C code.
      
      @param d the axis along which we wanna have the eigenvalues
    """
    result  = self.implementation_of_mapping_onto_named_quantities()
    result += "switch (normal) {\n"
    for d in range(0,self.dimensions):
      result += "  case " + str(d) + ":\n"
      for i in range(0,self.unknowns):
        result += sympy.printing.cxxcode( self.eigenvalue[i,d].evalf(), assign_to="lambda[" + str(i) + "]" )
        result += "\n"
      result += "  break;\n"
    result += "}\n"
    return result
