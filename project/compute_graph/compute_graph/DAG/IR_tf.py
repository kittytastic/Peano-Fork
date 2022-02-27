from typing import List, Dict
from compute_graph.DAG.dag_visitor import DAG_Visitor, DAG_PropsVisitor
from compute_graph.DAG.node import InPort, OutPort
from compute_graph.DAG.ops import Divide
from compute_graph.DAG.primitive_node import Constant
from compute_graph.IR.symbols import IR_Assign, IR_CallLooseFunction, IR_DataTypes, IR_LooseFunction, IR_Symbol, IR_TempVariable, IR_Variable, IR_SingleAssign, IR_Add, IR_Mul, IR_Sub, UniqueVariableName, IR_Div, IR_Const
from compute_graph.DAG import Graph, Add, Subtract, Multiply, TerminalInput, PassThroughNode, InputInterface, OutputInterface 

class DAG_GatherSubgraphVisitor(DAG_Visitor[List[Graph]]):
    
    def visitGraph(self, node:Graph)->List[Graph]:
        _, children_graphs = node.get_categoriesed_sub_nodes()
        all_decedent_graphs = [self.visit(cg) for cg in children_graphs]
        return_list:List[Graph] = [g for dgs in all_decedent_graphs for g in dgs]
        return_list.append(node) 
        return return_list

    def visitAdd(self, node:Add)->List[Graph]:
        raise Exception("Not implemented")
    
    def visitSubtract(self, node:Subtract)->List[Graph]:
        raise Exception("Not implemented")
    
    def visitMultiply(self, node:Multiply)->List[Graph]:
        raise Exception("Not implemented")
    
    def visitDivide(self, node:Divide)->List[Graph]:
        raise Exception("Not implemented")
    
    def visitConstant(self, node:Constant)->List[Graph]:
        raise Exception("Not implemented")
    
    def visitTerminalInput(self, node:TerminalInput)->List[Graph]:
        raise Exception("Not implemented")
    
    def visitPassThroughNode(self, node:PassThroughNode)->List[Graph]:
        raise Exception("Not implemented")

    def visitInputInterface(self, node:InputInterface)->List[Graph]:
        raise Exception("Not implemented")

    def visitOutputInterface(self, node:OutputInterface)->List[Graph]:
        raise Exception("Not implemented")


class DAGToIRVisitor(DAG_PropsVisitor[IR_Symbol, List[IR_Symbol]]):
    def __init__(self):
        self._temp_var_counter = 0

    def next_temp_var(self):
        self._temp_var_counter += 1
        return IR_TempVariable(UniqueVariableName(f"tmp{self._temp_var_counter}"))

    
    def visitGraph(self, node:Graph, props:List[IR_Symbol])->IR_Symbol:
        edges = node.get_edges()
        eval_order = node.eval_order()

        in_vars:List[IR_Variable] = [IR_TempVariable(UniqueVariableName(f"in{i}")) for i in range(node.num_inputs)]
        out_vars:List[IR_Variable] = [IR_TempVariable(UniqueVariableName(f"out{i}")) for i in range(node.num_outputs)]
        final_vars:Dict[int, IR_Variable] = {}            

        inport_vars:Dict[InPort, IR_Variable] = {InPort((in_node, 0)):in_vars[idx] for idx, in_node in enumerate(node.input_interface)}


        body:List[IR_Assign] = []
        for n in eval_order:
            node_in_vars:List[IR_Variable] = [inport_vars[InPort((n,i))] for i in range(n.num_inputs)]
            node_out_vars:List[IR_Variable] = [self.next_temp_var() for _ in range(n.num_outputs)]


            if isinstance(n, Graph):
                body.append(IR_CallLooseFunction(n.name, node_in_vars, node_out_vars))
                #raise Exception("Nested graphs support not complete")
            else:
                body.append(IR_SingleAssign(node_out_vars[0], self.visit(n, node_in_vars)))
            
            for idx, op_var in enumerate(node_out_vars):
                outport = OutPort((n, idx))
                
                if n in node.output_interface:
                    o_idx = node.output_interface.index(n)
                    final_vars[o_idx] = node_out_vars[0]
                else:
                    for ip in edges[outport]:
                        inport_vars[ip]=op_var

        for idx, var in final_vars.items():
            body.append(IR_SingleAssign(out_vars[idx], var))


        return IR_LooseFunction(IR_DataTypes.VOID, in_vars, out_vars, body, node.name)

    def visitAdd(self, node:Add, props:List[IR_Symbol])->IR_Symbol:
        return IR_Add(props[0], props[1])
    
    def visitSubtract(self, node:Subtract, props:List[IR_Symbol])->IR_Symbol:
        return IR_Sub(props[0], props[1])
    
    def visitMultiply(self, node:Multiply, props:List[IR_Symbol])->IR_Symbol:
        return IR_Mul(props[0], props[1])

    def visitDivide(self, node:Divide, props:List[IR_Symbol])->IR_Symbol:
       return IR_Div(props[0], props[1]) 

    def visitConstant(self, node:Constant, props:List[IR_Symbol])->IR_Symbol:
        return IR_Const(node.value)
    
    def visitTerminalInput(self, node:TerminalInput, props:List[IR_Symbol])->IR_Symbol:
        raise Exception("Not implemented")
    
    def visitPassThroughNode(self, node:PassThroughNode, props:List[IR_Symbol])->IR_Symbol:
        return props[0]
    
    def visitInputInterface(self, node:InputInterface, props:List[IR_Symbol])->IR_Symbol:
        return props[0]

    def visitOutputInterface(self, node:OutputInterface, props:List[IR_Symbol])->IR_Symbol:
        return props[0]