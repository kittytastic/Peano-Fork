from compute_graph.main import dag_to_IR
from compute_graph.DAG import Graph
from compute_graph.DAG.transform import DAG_TransformChain
from compute_graph.IR.transform import IR_TransformChain
from compute_graph.language_backend.backend_base import LanguageBackend

class FullStackTransform():
    def __init__(self, DAG_tf:DAG_TransformChain, IR_tf: IR_TransformChain, lang_backend: LanguageBackend, verbose:bool=False) -> None:
        self.DAG_tf = DAG_tf
        self.IR_tf = IR_tf
        self.lang_backend = lang_backend
        self.verbose = verbose


    def tf(self, in_DAG: Graph) -> str:
        tf_DAG = self.DAG_tf.tf(in_DAG)
        start_IR = dag_to_IR(tf_DAG)
        tf_IR = self.IR_tf.tf(start_IR)
        code = self.lang_backend.code_gen(tf_IR)
        return code