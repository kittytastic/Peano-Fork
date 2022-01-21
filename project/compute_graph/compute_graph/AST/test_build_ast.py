import unittest
from parameterized import parameterized #type:ignore

from compute_graph.AST.build_ast import *

class TestAttributeParsing(unittest.TestCase):
    @parameterized.expand([ # type:ignore
       ("var:Type", ("var", AttrTypes.SINGLE, "Type")),
       ("var*:Type", ("var", AttrTypes.LIST, "List[Type]")),
       ("var**:Type", ("var", AttrTypes.LOL, "List[List[Type]]")),
       ("var", ("var", AttrTypes.SINGLE, "Any")),
       ("var*", ("var", AttrTypes.LIST, "List[Any]")),
       ("var**", ("var", AttrTypes.LOL, "List[List[Any]]")),
    ])
    def test(self, arg:str, expected: Optional[CFG_Attribute]):
        self.assertEqual(parse_cfg_attribute(arg), expected)



if __name__=="__main__":
    unittest.main()