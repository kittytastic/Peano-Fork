from compute_graph.DAG import *
from compute_graph.DAG.primitive_node import Constant
from compute_graph.examples.Euler.euler import flux_x, flux_y, max_eigen_x, max_eigen_y


def proper_flux_x()->Graph:
    g = Graph(4+2+2+1, 4, "proper-flux-x")
    euler = flux_x()
    for u in range(4): 
        g.add_edge(g.get_internal_input(u), euler.get_external_input(u))
        g.add_edge(euler.get_external_output(u), g.get_internal_output(u))
    return g

def proper_flux_y()->Graph:
    g = Graph(4+2+2+1, 4, "proper-flux-y")
    euler = flux_y()
    for u in range(4): 
        g.add_edge(g.get_internal_input(u), euler.get_external_input(u))
        g.add_edge(euler.get_external_output(u), g.get_internal_output(u))
    return g


def proper_max_eigen_x()->Graph:
    g = Graph(4+2+2+1, 1, "proper-max-eigen-x")
    eigen = max_eigen_x()
    for u in range(4): 
        g.add_edge(g.get_internal_input(u), eigen.get_external_input(u))
        
    g.add_edge(eigen.get_external_output(0), g.get_internal_output(0))
    return g

def proper_max_eigen_y()->Graph:
    g = Graph(4+2+2+1, 1, "proper-max-eigen-y")
    eigen = max_eigen_y()
    for u in range(4): 
        g.add_edge(g.get_internal_input(u), eigen.get_external_input(u))
        
    g.add_edge(eigen.get_external_output(0), g.get_internal_output(0))
    return g

def source_term()->Graph:
    g = Graph(4+2+1+1+1, 4, "proper-max-eigen-y")
    c1 = Constant(0)
    for u in range(4):
        g.add_edge((c1,0), g.get_internal_output(u))
    
    return g

