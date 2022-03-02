from compute_graph.main import dag_to_IR
from compute_graph.DAG import Graph
from compute_graph.DAG.transform import DAG_TransformChain
from compute_graph.IR.transform import IR_TransformChain
from compute_graph.language_backend.backend_base import LanguageBackend
from compute_graph.DAG.graph import DAG_Message

class FullStackTransform():
    def __init__(self, DAG_tf:DAG_TransformChain, IR_tf: IR_TransformChain, lang_backend: LanguageBackend, verbose:bool=False) -> None:
        self.DAG_tf = DAG_tf
        self.IR_tf = IR_tf
        self.lang_backend = lang_backend
        self.verbose = verbose

    def v_print(self, msg:str):
        if self.verbose:
            print(msg)


    def tf(self, in_DAG: Graph) -> str:
        msgs = in_DAG.validate()
        ec, wc, _ = DAG_Message.get_stats(msgs)
        
        if self.verbose:
            DAG_Message.print_summary(msgs, max_msg=10)
        else:
            if ec > 0 or (wc>0 and not self.verbose):
                DAG_Message.print_summary(msgs, max_msg=10)
            else:
                DAG_Message.print_summary(msgs, max_msg=0)
        

        self.v_print("Preforming DAG transforms")
        tf_DAG = self.DAG_tf.tf(in_DAG)
        self.v_print("Transforming to IR")
        start_IR = dag_to_IR(tf_DAG)
        self.v_print("Preforming IR transforms")
        tf_IR = self.IR_tf.tf(start_IR)
        self.v_print("Preforming Codegen")
        code = self.lang_backend.code_gen(tf_IR)
        return code