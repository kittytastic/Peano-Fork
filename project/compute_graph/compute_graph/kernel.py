from typing import Dict, Optional, List, Set

from compute_graph.AST.ast_nodes_g import AST_Function
from compute_graph.AST.ast_node_base import AST_Node
from compute_graph.AST.ast_nodes_g import AST_Compound
from compute_graph.AST.variables import Variable, VariableReference
from compute_graph.graph import Graph
from compute_graph.node import InPort, Node, OutPort
from compute_graph.primative_nodes import TerminalInput


class Kernel():
    def __init__(self, input_vars: List[Variable], output_vars: List[Variable]) -> None:
        self.dag:Optional[Graph] = None
        self.kernel_to_dag_in_map: Optional[Dict[VariableReference, InPort]]=None
        self.dag_to_kernel_out_map: Optional[Dict[OutPort, VariableReference]]=None
        self.input_vars = input_vars
        self.input_refs = sum([len(v.get_references()) for v in input_vars])
        self.output_vars = output_vars
        self.output_refs = sum([len(v.get_references()) for v in output_vars])

    def set_DAG(self, dag: Graph, kernel_to_dag_in_map: Dict[VariableReference, InPort], dag_to_kernel_out_map: Dict[OutPort, VariableReference]):
        allowed_input_refs = set([vr for v in self.input_vars for vr in v.get_references()])
        allowed_output_refs = set([vr for v in self.output_vars for vr in v.get_references()])

        used_in_ref:Set[VariableReference] = set()
        used_out_ref:Set[VariableReference] = set()

        # Check all inputs used
        for vr, ip in kernel_to_dag_in_map.items():
            if vr not in allowed_input_refs:
                raise Exception(f"Cannot map the reference {vr} to DAG input {ip} as {vr} is not in a member of an input variable")
            
            used_in_ref.add(vr)

        unused_in_vr = allowed_input_refs-used_in_ref
        if len(unused_in_vr)>0:
            print(f"Warning: some input variable references are not used by dag")
        
        # Check all outputs used
        for op, vr in dag_to_kernel_out_map.items():
            if vr not in allowed_output_refs:
                raise Exception(f"Cannot map DAG output {op} to variable reference {vr} as {vr} is not in a member of an output variable")
            
            used_out_ref.add(vr)

        unused_out_vr = allowed_output_refs-used_out_ref
        if len(unused_out_vr)>0:
            print(f"Warning: some output variable references are not used by dag")
        
        # Set self
        self.dag = dag
        self.kernel_to_dag_in_map = kernel_to_dag_in_map
        self.dag_to_kernel_out_map = dag_to_kernel_out_map

    def ast_compile(self, memory_map: Dict[OutPort, VariableReference], traversal_order: List[Node]):
        assert(self.dag!=None)
        assert(self.dag_to_kernel_out_map!=None)
        assert(self.kernel_to_dag_in_map!=None)


        tin = [TerminalInput() for _ in range(self.dag.num_inputs)]
        tin_edges:Dict[InPort, OutPort] = {self.dag.get_external_input(i): OutPort((tin[i],0)) for i in range(self.dag.num_inputs)}
        tin_mm = {tin_edges[ip]:vr for vr, ip in self.kernel_to_dag_in_map.items()}

        inverse_edges = self.dag.inverse_edges()

        # Add input mappings
        inverse_edges = {**inverse_edges, **tin_edges}
        full_memory_map = {**memory_map, **tin_mm}

        # Add output mappings
        full_memory_map = {**full_memory_map, **self.dag_to_kernel_out_map}

        var_def = self._var_definitions(memory_map)
        body = self._DAG_to_AST(inverse_edges, full_memory_map, traversal_order)
        tail = self._var_output_set(full_memory_map)
        body_ast = AST_Compound(var_def+body+tail)
        return AST_Function("kernel", [], body_ast) 


    def _var_definitions(self, memory_map: Dict[OutPort, VariableReference])->List[AST_Node]:
        variables = set([vr.var for vr in memory_map.values()])
        
        dec_expr = [v.declare() for v in variables]
        dec_expr = [e for e in dec_expr if e is not None]

        return dec_expr
    
    def _var_output_set(self, memory_map: Dict[OutPort, VariableReference])->List[AST_Node]:
        assert(self.dag)
        assert(self.dag_to_kernel_out_map)
        out_ports = [OutPort((on, 0)) for on in self.dag.output_interface]
        out_vars_refs = [self.dag_to_kernel_out_map[op] for op in out_ports]

        out_expr = [vr.set(memory_map[p].ref()) for p, vr in zip(out_ports, out_vars_refs)]

        return out_expr

    def _DAG_to_AST(self, inverse_edges:Dict[InPort, OutPort], memory_map: Dict[OutPort, VariableReference], traversal_order: List[Node])->List[AST_Node]:
        

        compute_expr:List[AST_Node] = []
        
        for n in traversal_order:
            in_port_connections = [inverse_edges[InPort((n, p))] for p in range(n.num_inputs)]
            in_port_var_ref = [memory_map[p] for p in in_port_connections] # inject mappings
            in_port_ast = [pvr.ref() for pvr in in_port_var_ref]

            node_ast = n.ast_visit(in_port_ast)

            out_port_store_var_ref = [memory_map[OutPort((n, p))] for p in range(n.num_outputs)]
            out_port_set_ast = [vr.set(ast) for vr, ast in zip(out_port_store_var_ref, node_ast)]

            compute_expr += out_port_set_ast

        return compute_expr 