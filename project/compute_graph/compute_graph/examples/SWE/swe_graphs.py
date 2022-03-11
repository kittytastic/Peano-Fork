from typing import Callable, List
from compute_graph.DAG import *
from compute_graph.DAG.ops import Divide, Sqrt
from compute_graph.DAG.primitive_node import Constant, DebugNode

# NCP
# Q            (unknowns+aux)
# deltaQ       (unknowns+aux)
# patch center (2)
# patch dx     (1)
# t            (1)
# OUT:         (unknowns)


# Flux + Eigen
# Q            (unknowns+aux)
# patch center (2)
# patch dx     (1)
# t            (1)
# dt           (1)
# OUT:         (unknowns)

def swe_ncp_x()->Graph:
    g = Graph(3+1 + 3+1 + 2+1+1+1, 3, "swe ncp x")

    grav = Constant(9.81)
    add1 = Add(2)
    mul1 = Multiply(3)

    g.fill_node_inputs([g.get_internal_input(4+0), g.get_internal_input(4+3)], add1)
    g.fill_node_inputs([grav, g.get_internal_input(0), add1], mul1)
    g.add_edge((mul1, 0), g.get_internal_output(1))

    zero = Constant(0.0)
    g.add_edge((zero, 0), g.get_internal_output(0))
    g.add_edge((zero, 0), g.get_internal_output(2))
    return g

def swe_ncp_y()->Graph:
    g = Graph(3+1 + 3+1 + 2+1+1+1, 3, "swe ncp x")

    grav = Constant(9.81)
    add1 = Add(2)
    mul1 = Multiply(3)

    g.fill_node_inputs([g.get_internal_input(4+0), g.get_internal_input(4+3)], add1)
    g.fill_node_inputs([grav, g.get_internal_input(0), add1], mul1)
    g.add_edge((mul1, 0), g.get_internal_output(2))

    zero = Constant(0.0)
    g.add_edge((zero, 0), g.get_internal_output(0))
    g.add_edge((zero, 0), g.get_internal_output(1))
    return g


def swe_flux_x()->Graph:
    g = Graph(3+1  +2+1+1+1, 3, "swe flux x")

    ih = Divide()
    one = Constant(1)

    g.fill_node_inputs([one, g.get_internal_input(0)], ih)

    # F[0]
    g.add_edge(g.get_internal_input(1), g.get_internal_output(0))
    
    # F[1]
    mul1 = Multiply(3)
    g.fill_node_inputs([ih, g.get_internal_input(1), g.get_internal_input(1)], mul1)
    g.add_edge((mul1, 0), g.get_internal_output(1))
    
    # F[2]
    mul2 = Multiply(3)
    g.fill_node_inputs([ih, g.get_internal_input(1), g.get_internal_input(2)], mul2)
    g.add_edge((mul2,0), g.get_internal_output(2))

    return g

def swe_flux_y()->Graph:
    g = Graph(3+1  +2+1+1+1, 3, "swe flux y")

    ih = Divide()
    one = Constant(1)

    g.fill_node_inputs([one, g.get_internal_input(0)], ih)

    # F[0]
    g.add_edge(g.get_internal_input(2), g.get_internal_output(0))
    
    # F[1]
    mul1 = Multiply(3)
    g.fill_node_inputs([ih, g.get_internal_input(2), g.get_internal_input(1)], mul1)
    g.add_edge((mul1, 0), g.get_internal_output(1))
    
    # F[2]
    mul2 = Multiply(3)
    g.fill_node_inputs([ih, g.get_internal_input(2), g.get_internal_input(2)], mul2)
    g.add_edge((mul2,0), g.get_internal_output(2))

    return g

def swe_max_eigen_base(normal: str)->Graph:
    assert(normal=="x" or normal=="y")
    if normal=="x":
        u_input = 1
    else:
        u_input = 2
    
    g = Graph(3+1  +2+1+1+1, 1, f"swe max eigen {normal}")
    one = Constant(1.0)
    ih = Divide()
    grav = Constant(9.81)
    c = Sqrt()
    u = Multiply(2)
    result = Max(2)

    add1 = Add(2)
    add2 = Add(2)
    sub1 = Subtract()
    mul1 = Multiply(2)

    g.fill_node_inputs([one, g.get_internal_input(0)], ih)

    g.fill_node_inputs([g.get_internal_input(0), g.get_internal_input(3)], add1)
    g.fill_node_inputs([grav, add1], mul1)
    g.fill_node_inputs([mul1], c)

    g.fill_node_inputs([ih, g.get_internal_input(u_input)], u)

    g.fill_node_inputs([u,c], sub1)
    g.fill_node_inputs([u,c], add2)
    g.fill_node_inputs([sub1,add2], result)

    g.add_edge((result,0), g.get_internal_output(0))
    return g

def swe_max_eigen_x()->Graph:
    return swe_max_eigen_base("x")

def swe_max_eigen_y()->Graph:
    return swe_max_eigen_base("y")

   