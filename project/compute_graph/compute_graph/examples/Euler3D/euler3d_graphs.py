from typing import Callable, List
from compute_graph.DAG import *
from compute_graph.DAG.ops import Divide, Sqrt
from compute_graph.DAG.primitive_node import Constant

def irho_graph()->Graph:
    g = Graph(1,1, "irho")
    div = Divide()
    c1 = Constant(1)

    g.add_edge((c1, 0), (div, 0))
    g.add_edge(g.get_internal_input(0), (div, 1))

    g.add_edge((div, 0), g.get_internal_output(0))

    return g

def p_graph()->Graph:
    #(gamma-1) * (Q[3] - 0.5*irho*(Q[1]*Q[1]+Q[2]*Q[2]))
    g = Graph(5,1, 'p')

    c1 = Constant(0.4)
    half = Constant(0.5)


    sub1 = Subtract()
    add1 = Add(3)
    mul1 = Multiply(2)
    mul2 = Multiply(2)
    mul25 = Multiply(2)
    mul3 = Multiply(2)
    mul4 = Multiply(2)
    mul5 = Multiply(2)

    # Q[1]*Q[1]
    g.add_edge(g.get_internal_input(1), (mul1, 0))
    g.add_edge(g.get_internal_input(1), (mul1, 1))

    # Q[2]*Q[2]
    g.add_edge(g.get_internal_input(2), (mul2, 0))
    g.add_edge(g.get_internal_input(2), (mul2, 1))

    # Q[3]*Q[3]
    g.fill_node_inputs([g.get_internal_input(3), g.get_internal_input(3)], mul25)

    # (Q[1]*Q1[1]+Q[2]*Q[2]+Q[3]*Q[3])
    g.fill_node_inputs([mul1, mul2, mul25], add1)

    # irho * (Q1[1]...Q[2])
    g.fill_node_inputs([(add1, 0), g.get_internal_input(0)], mul3)
    
    # 0.5 * irho * (Q1[1]...Q[2])
    g.fill_node_inputs([half, (mul3, 0)], mul4)

    # Q[3] - 0.5 * ...
    g.fill_node_inputs([g.get_internal_input(4), (mul4, 0)], sub1)
    
    # 0.4 * (Q[3] - ...)
    g.fill_node_inputs([c1, sub1], mul5)


    g.add_edge((mul5, 0), g.get_internal_output(0))

    return g



def flux_x()->Graph:
    g = Graph(5+5,5, "flux_x")
    p = p_graph()
    irho = irho_graph()

    f1 = Multiply(3)
    f2 = Multiply(3)
    f3 = Multiply(3)
    f4 = Multiply(3)

    add1 = Add(2)
    add2 = Add(2)

    # p
    g.fill_node_inputs([irho, g.get_internal_input(1), g.get_internal_input(2), g.get_internal_input(3), g.get_internal_input(4)], p) 

    # irho
    g.add_edge(g.get_internal_input(0), (irho, 0))

    # F[0]
    g.add_edge(g.get_internal_input(1), g.get_internal_output(0))

    # F[1]
    g.fill_node_inputs([irho , g.get_internal_input(1), g.get_internal_input(1)], f1)
    g.fill_node_inputs([f1, p], add1)
    g.add_edge((add1, 0), g.get_internal_output(1))

    # F[2]
    g.fill_node_inputs([irho, g.get_internal_input(1), g.get_internal_input(2)], f2)
    g.add_edge((f2, 0), g.get_internal_output(2))

    # F[3]
    g.fill_node_inputs([irho, g.get_internal_input(1), g.get_internal_input(3)], f3)
    g.add_edge((f3, 0), g.get_internal_output(3))

    # F[3]
    g.fill_node_inputs([g.get_internal_input(4), p], add2)
    g.fill_node_inputs([irho, g.get_internal_input(1), add2], f4)
    g.add_edge((f4, 0), g.get_internal_output(4))

    return g

def flux_y()->Graph:
    common_fact = 2
    g = Graph(5+5,5, "flux_y")
    p = p_graph()
    irho = irho_graph()

    f1 = Multiply(3)
    f2 = Multiply(3)
    f3 = Multiply(3)
    f4 = Multiply(3)

    add1 = Add(2)
    add2 = Add(2)

    # p
    g.fill_node_inputs([irho, g.get_internal_input(1), g.get_internal_input(2), g.get_internal_input(3), g.get_internal_input(4)], p) 

    # irho
    g.add_edge(g.get_internal_input(0), (irho, 0))

    # F[0]
    g.add_edge(g.get_internal_input(common_fact), g.get_internal_output(0))

    # F[1]
    g.fill_node_inputs([irho , g.get_internal_input(common_fact), g.get_internal_input(1)], f1)
    g.add_edge((f1, 0), g.get_internal_output(1))

    # F[2]
    g.fill_node_inputs([irho, g.get_internal_input(common_fact), g.get_internal_input(2)], f2)
    g.fill_node_inputs([f2, p], add1)
    g.add_edge((add1, 0), g.get_internal_output(2))

    # F[3]
    g.fill_node_inputs([irho, g.get_internal_input(common_fact), g.get_internal_input(3)], f3)
    g.add_edge((f3, 0), g.get_internal_output(3))

    # F[3]
    g.fill_node_inputs([g.get_internal_input(4), p], add2)
    g.fill_node_inputs([irho, g.get_internal_input(common_fact), add2], f4)
    g.add_edge((f4, 0), g.get_internal_output(4))

    return g

def flux_z()->Graph:
    common_fact = 3
    g = Graph(5+5,5, "flux_z")
    p = p_graph()
    irho = irho_graph()

    f1 = Multiply(3)
    f2 = Multiply(3)
    f3 = Multiply(3)
    f4 = Multiply(3)

    add1 = Add(2)
    add2 = Add(2)

    # p
    g.fill_node_inputs([irho, g.get_internal_input(1), g.get_internal_input(2), g.get_internal_input(3), g.get_internal_input(4)], p) 

    # irho
    g.add_edge(g.get_internal_input(0), (irho, 0))

    # F[0]
    g.add_edge(g.get_internal_input(common_fact), g.get_internal_output(0))

    # F[1]
    g.fill_node_inputs([irho , g.get_internal_input(common_fact), g.get_internal_input(1)], f1)
    g.add_edge((f1, 0), g.get_internal_output(1))

    # F[2]
    g.fill_node_inputs([irho, g.get_internal_input(common_fact), g.get_internal_input(2)], f2)
    g.add_edge((f2, 0), g.get_internal_output(2))

    # F[3]
    g.fill_node_inputs([irho, g.get_internal_input(common_fact), g.get_internal_input(3)], f3)
    g.fill_node_inputs([f3, p], add1)
    g.add_edge((add1, 0), g.get_internal_output(3))

    # F[3]
    g.fill_node_inputs([g.get_internal_input(4), p], add2)
    g.fill_node_inputs([irho, g.get_internal_input(common_fact), add2], f4)
    g.add_edge((f4, 0), g.get_internal_output(4))

    return g

def _eigen_base(dir:str):
    assert(dir=="x" or dir=="y" or dir=="z")
    g = Graph(5+5,1, f"max_eigen_{dir}")
    p = p_graph()
    irho = irho_graph()

    mul1 = Multiply(3)
    mul2 = Multiply(2)

    add1 = Add(2)
    sub1 = Subtract()

    abs1 = Abs()
    abs2 = Abs()
    max1 = Max(2)
    c = Sqrt()

    gamma = Constant(1.4)

    # p
    g.fill_node_inputs([(irho, 0), g.get_internal_input(1), g.get_internal_input(2), g.get_internal_input(3), g.get_internal_input(4)], p) 

    # irho
    g.add_edge(g.get_internal_input(0), (irho, 0))


    # c
    g.fill_node_inputs([gamma, p, irho], mul1)
    g.fill_node_inputs([mul1], c)

    # Q[x] * irho
    if dir=="x": x=1
    elif dir =="y": x=2
    else: x=3 
    g.fill_node_inputs([g.get_internal_input(x), irho], mul2)
    
    # max
    g.fill_node_inputs([mul2, c], sub1)
    g.fill_node_inputs([sub1], abs1)
    g.fill_node_inputs([mul2, c], add1)
    g.fill_node_inputs([add1], abs2)
    g.fill_node_inputs([abs1, abs2], max1)
    
    g.add_edge((max1, 0), g.get_internal_output(0))

    return g

def max_eigen_x():
    return _eigen_base("x")

def max_eigen_y():
   return _eigen_base("y")


def max_eigen_z():
   return _eigen_base("z") 

