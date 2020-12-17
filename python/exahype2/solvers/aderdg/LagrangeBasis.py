import mpmath as mp
import numpy as np
from sympy.integrals.quadrature import gauss_legendre, gauss_lobatto # quadrature_nodes by default in [-1,1]

from abc import abstractmethod

PREC_DIGITS   = 256
RENDER_DIGITS = 64

mp.dps    = PREC_DIGITS
mp.pretty = False

class LagrangeBasis():
  def __init__(self,num_points):
    self._num_points = num_points
    self._max_poly_order = num_points - 1
    # quadrature_nodes, quadrature_weights
    self._quadrature_nodes, self._quadrature_weights = self._compute_quadrature_nodes_and_quadrature_weights(num_points)
    # operators
    self._mass_matrix                = self._compute_mass_matrix()
    self._stiffness_matrix           = self._compute_stiffness_matrix()
    self._K1                         = self._compute_K1()
    self._F0                         = self._compute_F0()
    self._dudx                       = self._compute_discrete_derivative_operator()
    self._equidistant_grid_projector = self._compute_equidistant_grid_projector()
    self._fine_grid_projector        = [None]*3
    for j in range(0,3):
      self._fine_grid_projector[j] = self._compute_fine_grid_projector(j)
  def __str__(self):
    return "<{}.{} object>: {}".format(self.__class__.__module__,self.__class__.__name__,self.__dict__)
  __repr__ = __str__
  @abstractmethod
  def _compute_quadrature_nodes_and_quadrature_weights(self,num_points):
    """
    To be implemented by subclass.
    """
    assert False, "To be implemented by subclass."
  def _evaluate(self,xi):
    """
    Evaluates a lagrange polynomial and its first derivative at a given point.
    
    Args:
       xi:
        The reference element point the basis functions are evaluated at.
        Here, xi refers to the greek letter that is often used as a reference element coordinate.
    Returns:
       phi:
        Basis function values.
       phi_xi:
        First derivatives of the basis functions.
    """
    phi  = [mp.mpf(1.)]*(self._num_points) 
    phi_xi = [mp.mpf(0.)]*(self._num_points)
    xin = self._quadrature_nodes
    for m in range(0,self._num_points):
      for j in range(0,self._num_points):
        if j == m:
          continue 
        phi[m] = phi[m]*(xi-xin[j])/(xin[m]-xin[j])
      for i in range(0,self._num_points):
        if i == m:
          continue
        tmp = 1.;
        for j in range(0,self._num_points):
          if j == i:
            continue
          if j == m:
            continue
          tmp = tmp*(xi-xin[j])/(xin[m]-xin[j])
        phi_xi[m] += tmp/(xin[m]-xin[i])
    return phi, phi_xi  
  def _compute_mass_matrix(self):
    """
    Computes the (reference) element mass matrix for an approximation of
    order self._max_poly_order.
  
    Returns:
       M_xi:
        The (reference) element mass matrix.
    """
    # init matrix with zeros
    MM = [[mp.mpf(0) for _ in range(self._num_points)] for _ in range(self._num_points)]
    
    for i in range(0,self._num_points):
      phi, _ = self._evaluate(self._quadrature_nodes[i])
      for k in range(0,self._num_points):
        for l in range(0,self._num_points):
          MM[k][l] += self._quadrature_weights[i]*phi[k]*phi[l]
    return MM
  def _compute_stiffness_matrix(self):
    """
    Computes the (reference) element stiffness matrix for an approximation of order self._max_poly_order.
    Returns:
       K_xi:
        The (reference) element stiffness matrix.
    """
    # init matrix with zero
    Kxi = [[mp.mpf(0) for _ in range(self._num_points)] for _ in range(self._num_points)]
       
    for i in range(0,self._num_points):
      phi, phi_xi = self._evaluate(self._quadrature_nodes[i])
      for k in range(0,self._num_points):
        Kxi[k][i] = self._quadrature_weights[i]*phi_xi[k]*phi[i] 
    return Kxi
  def _compute_K1(self):
    """
    Computes the difference between the reference element mass operator 
    evaluated at point xi=1.0 and the element stiffness matrix.
    
    Returns:
       K1:
        delta between the reference element mass operator and the element stiffness matrix
    """
    phi1, _ = self._evaluate(1.0)
    FRm = [[mp.mpf(0) for _ in range(self._num_points)] for _ in range(self._num_points)]
    
    for k in range(0, self._num_points):
      for l in range(0, self._num_points):
        FRm[k][l] = phi1[k]*phi1[l] 
    
    K1 = np.subtract(FRm,self._stiffness_matrix)
    return K1    
      
  def _compute_F0(self):
    """
    Evaluates the reference basis functions at point xi=0.0.
  
    Returns:
       phi:
        The reference basis functions evaluated at point xi=0.0.
    """
    phi, _ = self._evaluate(mp.mpf(0.0))
    return phi     
      
  def _compute_discrete_derivative_operator(self):
    """
    Computes some derivative values for debugging purposes.
  
    Returns:
       dudx:
        Derivative values for debugging purposes.
    """
    dudx = np.dot(mp.inverse(self._mass_matrix).tolist(),np.transpose(self._stiffness_matrix))
    return dudx
  def _compute_fine_grid_projector(self, j):
    """
    Transforms the degrees of freedom located on a coarse grid edge
    quadrature_nodes to degrees of freedoms located on quadrature_nodes of a fine grid edge.
    The difference in levels is 1.
    
    Let us denote by P the  fine grid projector (= equidistantGridProjector). The fine grid DoF 
    are computed according to:
    
    u^{fine;j}_i =  sum_{m} P^{j}_im u^{coarse}_m
     
    Args:
      j:
      subinterval index
    
    Returns:
       fineGridProjector:
        Operator to express polynomial function associated with original interval with basis functions associated with subinterval j
    """
    fineGridProjector = [[mp.mpf(0) for _ in range(self._num_points)] for _ in range(self._num_points)] # 4 x 4 for self._max_poly_order=3
    
    for i in range(0, self._num_points): # Eq. basis
      phi_i, _ = self._evaluate((self._quadrature_nodes[i]+j)/mp.mpf(3.0)) # comma after phi_i is important
      for m in range(0, self._num_points): # DG basis
        fineGridProjector[m][i] = phi_i[m]
    return fineGridProjector
  def _compute_equidistant_grid_projector(self):
    """
    Transforms the degrees of freedom located at non-equidistant Lagrange support points
    quadrature_nodes to degrees of freedoms located at quadrature_nodes of an equidistant grid over (0,1).
    
    Let us denote by P the  projection operator (= equidistantGridProjector). The equidistant DoF 
    are computed according to:
    
    u^eq_i =  sum_{m} P_im u^DG_m
    
    Returns:
       equidistantGridProjector:
        The corresponding degrees of freedom located at quadrature_nodes of an equidistant grid over (0,1).
    """
    equidistantGridProjector = [[mp.mpf(0) for _ in range(self._num_points)] for _ in range(self._num_points)] # 4 x 4 for self._max_poly_order=3
    subxi = mp.linspace(mp.mpf(0.0), mp.mpf(1.0), self._num_points)
    
    for i in range(0, self._num_points): # Eq. basis
      phi_i, _ = self._evaluate(subxi[i]) # comma after phi_i is important
      for m in range(0, self._num_points): # DG basis
        equidistantGridProjector[m][i] = phi_i[m]
    return equidistantGridProjector

  def _render_tensor_1(self,tensor):
    """
    :param tensor: list or numpy vector storing  mpmath numbers
    """
    result = []
    for elem in tensor:
      result.append(mp.nstr(elem,n=RENDER_DIGITS))
    return result
  
  def _render_tensor_2(self,tensor):
    """
    :param tensor: nested list or numpy matrix storing  mpmath numbers
    """
    result = []
    for row in tensor:
       resultRow = []
       for elem in row:
          resultRow.append(mp.nstr(elem,n=RENDER_DIGITS))
       result.append(resultRow)
    return result 

  def _render_tensor_3(self,tensor):
      """
      :param tensor: nested list or numpy matrix storing  mpmath numbers
      """
      result = []
      for r1 in tensor:
         tmp1 = []
         for r2 in r1:
            tmp2 = []
            for elem in r2:
              tmp2.append(mp.nstr(elem,n=RENDER_DIGITS))
            tmp1.append(tmp2)
         result.append(tmp1)
      return result 
  
  def _init_dictionary_with_default_parameters(self,d):
    d["order".upper()]                      = self._max_poly_order
    d["quadrature_nodes".upper()]           = self._render_tensor_1(self._quadrature_nodes)                
    d["quadrature_weights".upper()]         = self._render_tensor_1(self._quadrature_weights)                
    d["F0".upper()]                         = self._render_tensor_1(self._F0)                         
    d["dudx".upper()]                       = self._render_tensor_2(self._dudx)                       
    d["mass_matrix".upper()]                = self._render_tensor_2(self._mass_matrix)                
    d["stiffness_matrix".upper()]           = self._render_tensor_2(self._stiffness_matrix)           
    d["K1".upper()]                         = self._render_tensor_2(self._K1)                         
    d["equidistant_grid_projector".upper()] = self._render_tensor_2(self._equidistant_grid_projector) 
    d["fine_grid_projector".upper()]        = self._render_tensor_3(self._fine_grid_projector)        

def _transform_and_sort_nodes_and_weights(quadrature_nodes,quadrature_weights):
  """
  Transform quadrature quadrature_nodes and quadrature_weights for interval [-1,1]
  to quadrature_nodes and quadrature_weights for interval [0,1].
  """
  transformed_quadrature_weights = []
  transformed_quadrature_nodes   = []
  # weight
  for i,w in enumerate(quadrature_weights):
    x = quadrature_nodes[i]
    wT = mp.mpf(w)/mp.mpf(2.0)
    xT = (mp.mpf(x)+mp.mpf(1.0))/mp.mpf(2.0)
    transformed_quadrature_weights.append(wT)
    transformed_quadrature_nodes.append(xT)
  # sort
  sorted_transformed_quadrature_nodes = sorted(transformed_quadrature_nodes)
  sorted_transformed_quadrature_weights = []
  for i,xs in enumerate(sorted_transformed_quadrature_nodes):
    n  = transformed_quadrature_nodes.index(xs) 
    ws = transformed_quadrature_weights[n]
    sorted_transformed_quadrature_weights.append(ws)
  return sorted_transformed_quadrature_nodes, sorted_transformed_quadrature_weights

class GaussLegendreBasis(LagrangeBasis):
  def _compute_quadrature_nodes_and_quadrature_weights(self,num_points):
    x, w = gauss_legendre(num_points,PREC_DIGITS)
    return _transform_and_sort_nodes_and_weights(x,w)  

class GaussLobattoBasis(LagrangeBasis):
  def _compute_quadrature_nodes_and_quadrature_weights(self,num_points):
    x, w = gauss_lobatto(num_points,PREC_DIGITS)
    return _transform_and_sort_nodes_and_weights(x,w)  
