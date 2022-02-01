from typing import List, Set, Dict
from compute_graph.DAG.dag_visitor import DAG_Visitor, DAG_PropsVisitor
from compute_graph.DAG.node import InPort, OutPort
from compute_graph.IR.symbols import IR_Assign, IR_CallLooseFunction, IR_DataTypes, IR_LooseFunction, IR_Symbol, IR_TempVariable, IR_Variable, IR_MultiAssign, IR_SingleAssign, IR_Add, IR_Mul, IR_Sub
from compute_graph.DAG import Graph, Add, Subtract, Multiply, TerminalInput, PassThroughNode, InputPassThrough

class DAG_GatherSubgraphVisitor(DAG_Visitor[Set[Graph]]):
    
    def visitGraph(self, node:Graph)->Set[Graph]:
        children_graphs = [n for n in node.get_sub_nodes() if isinstance(n, Graph)]
        all_decedent_graphs = [self.visit(cg) for cg in children_graphs]
        retrun_set:Set[Graph] = set() 
        return retrun_set.union(*all_decedent_graphs)

    def visitAdd(self, node:Add)->Set[Graph]:
        raise Exception("Not implemented")
    
    def visitSubtract(self, node:Subtract)->Set[Graph]:
        raise Exception("Not implemented")
    
    def visitMultiply(self, node:Multiply)->Set[Graph]:
        raise Exception("Not implemented")
    
    def visitTerminalInput(self, node:TerminalInput)->Set[Graph]:
        raise Exception("Not implemented")
    
    def visitPassThroughNode(self, node:PassThroughNode)->Set[Graph]:
        raise Exception("Not implemented")

    def visitInputPassThrough(self, node:InputPassThrough)->Set[Graph]:
        raise Exception("Not implemented")


class DAGToIRVisitor(DAG_PropsVisitor[IR_Symbol, List[IR_Symbol]]):
    def __init__(self):
        self._temp_var_counter = 0

    def next_temp_var(self):
        self._temp_var_counter += 1
        return IR_TempVariable("tmp", self._temp_var_counter)

    
    def visitGraph(self, node:Graph, props:List[IR_Symbol])->IR_Symbol:
        edges = node.get_edges()
        eval_order = node.eval_order()
        print(eval_order)

        in_vars:List[IR_Variable] = [IR_TempVariable("in", i) for i in range(node.num_inputs)]
        out_vars:List[IR_Variable] = [IR_TempVariable("out", i) for i in range(node.num_outputs)]
        final_vars:Dict[int, IR_Variable] = {}            

        inport_vars:Dict[InPort, IR_Variable] = {InPort((in_node, 0)):in_vars[idx] for idx, in_node in enumerate(node.input_interface)}


        body:List[IR_Assign] = []
        for n in eval_order:
            node_in_vars = [inport_vars[InPort((n,i))] for i in range(n.num_inputs)]
            node_out_vars = [self.next_temp_var() for _ in range(n.num_outputs)]


            if isinstance(n, Graph):
                body.append(IR_MultiAssign(node_out_vars, IR_CallLooseFunction(node_in_vars)))
                raise Exception("Nested graphs support not complete")
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


        return IR_LooseFunction(IR_DataTypes.VOID, in_vars, out_vars,body)

    def visitAdd(self, node:Add, props:List[IR_Symbol])->IR_Symbol:
        return IR_Add(props[0], props[1])
    
    def visitSubtract(self, node:Subtract, props:List[IR_Symbol])->IR_Symbol:
        return IR_Sub(props[0], props[1])
    
    def visitMultiply(self, node:Multiply, props:List[IR_Symbol])->IR_Symbol:
        return IR_Mul(props[0], props[1])
    
    def visitTerminalInput(self, node:TerminalInput, props:List[IR_Symbol])->IR_Symbol:
        raise Exception("Not implemented")
    
    def visitPassThroughNode(self, node:PassThroughNode, props:List[IR_Symbol])->IR_Symbol:
        return props[0]
    
    def visitInputPassThrough(self, node:InputPassThrough, props:List[IR_Symbol])->IR_Symbol:
        return props[0]