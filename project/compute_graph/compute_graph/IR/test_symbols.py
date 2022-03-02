from typing import Set, Tuple
from compute_graph.IR.symbols import *
import unittest

from compute_graph.IR.symbols.functions import IR_CallTightFunction

class TestIRSymIN(unittest.TestCase):
    def test_object_1(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        t2 = IR_TempVariable(UniqueVariableName("test"))
        a1 = IR_SingleAssign(t1, t2)

        self.assertTrue(t1 in a1)
        self.assertTrue(t2 in a1)
    
    def test_object_2(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        t2 = IR_TempVariable(UniqueVariableName("test"))
        t3 = IR_TempVariable(UniqueVariableName("test"))
        s1 = IR_Sub(t1, t2)
        a1 = IR_SingleAssign(t3, s1)

        self.assertTrue(t1 in a1)
        self.assertTrue(t2 in a1)
        self.assertTrue(t3 in a1)
        self.assertTrue(s1 in a1)
    
    def test_object_3(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        t2 = IR_TempVariable(UniqueVariableName("test"))
        a1 = IR_CallTightFunction("", [t1, t2])

        self.assertTrue(t1 in a1)
        self.assertTrue(t2 in a1)
    
    def test_class_1(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        t2 = IR_TempVariable(UniqueVariableName("test"))
        a1 = IR_SingleAssign(t1, t2)

        self.assertTrue(IR_TempVariable in a1)
    
    def test_class_2(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        t2 = IR_TempVariable(UniqueVariableName("test"))
        t3 = IR_TempVariable(UniqueVariableName("test"))
        s1 = IR_Sub(t1, t2)
        a1 = IR_SingleAssign(t3, s1)

        self.assertTrue(IR_TempVariable in a1)
        self.assertTrue(IR_Sub in a1)
    
    def test_class_3(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        t2 = IR_TempVariable(UniqueVariableName("test"))
        a1 = IR_CallTightFunction("", [t1, t2])

        self.assertTrue(IR_TempVariable in a1)

class TestIRSymReplace(unittest.TestCase):
    def test_1(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        t2 = IR_TempVariable(UniqueVariableName("test"))
        n1 = IR_TempVariable(UniqueVariableName("new"))
        a1 = IR_SingleAssign(t1, t2)

        self.assertEqual(a1.replace(t2, n1), 1)
        self.assertEqual(a1.expr, n1)
    
    def test_2(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        t2 = IR_TempVariable(UniqueVariableName("test"))
        n1 = IR_TempVariable(UniqueVariableName("new"))
        s1 = IR_Sub(t1, t2)
        a1 = IR_SingleAssign(t2, s1)

        self.assertEqual(a1.replace(t2, n1), 2)
        self.assertEqual(a1.assign_var, n1)
        self.assertEqual(s1.rval, n1)
    
    def test_3(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        t2 = IR_TempVariable(UniqueVariableName("test"))
        n1 = IR_TempVariable(UniqueVariableName("new"))
        a1 = IR_CallTightFunction("", [t1, t2])

        self.assertEqual(a1.replace(t2, n1), 1)
        self.assertEqual(a1.args[1], n1)
    
    def test_4(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        n1 = IR_TempVariable(UniqueVariableName("new"))

        with self.assertRaises(Exception):
            t1.replace(t1, n1)

class TestIRSymGetInstance(unittest.TestCase):
    def test_1(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        t2 = IR_TempVariable(UniqueVariableName("test"))
        a1 = IR_SingleAssign(t1, t2)

        self.assertEqual(a1.get_instances(IR_TempVariable), set([t1, t2]))
    
    def test_2(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        t2 = IR_TempVariable(UniqueVariableName("test"))
        t3 = IR_TempVariable(UniqueVariableName("test"))
        s1 = IR_Sub(t1, t2)
        a1 = IR_SingleAssign(t3, s1)

        self.assertEqual(a1.get_instances(IR_TempVariable), set([t1,t2,t3]))
    
    def test_3(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        t2 = IR_TempVariable(UniqueVariableName("test"))
        a1 = IR_CallTightFunction("", [t1, t2])

        self.assertEqual(a1.get_instances(IR_TempVariable), set([t1,t2]))
    
class TestIRSymGetAttributes(unittest.TestCase):
    def test_1(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        expected:Tuple[Set[str], Set[str]] = (set(), set())
        self.assertEqual(t1._get_sub_symbol_keys(), expected) # type: ignore
    
    def test_2(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        a1 = IR_Add(t1, t1)
        expected:Tuple[Set[str], Set[str]] = ({"lval", "rval"}, set())
        self.assertEqual(a1._get_sub_symbol_keys(), expected) # type: ignore
    
    def test_3(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        a1 = IR_CallTightFunction("", [t1])
        expected:Tuple[Set[str], Set[str]] = (set(), {"args"})
        self.assertEqual(a1._get_sub_symbol_keys(), expected) # type: ignore
    
    def test_4(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        a1 = IR_CallTightFunction("", [])
        expected:Tuple[Set[str], Set[str]] = (set(), set())
        self.assertEqual(a1._get_sub_symbol_keys(), expected) # type: ignore
        
        a1.args = [t1] # type: ignore
        expected:Tuple[Set[str], Set[str]] = (set(), {"args"})
        self.assertEqual(a1._get_sub_symbol_keys(), expected) # type: ignore
    
    def test_5(self):
        t1 = IR_TempVariable(UniqueVariableName("test"))
        a1 = IR_TightFunction(IR_DataTypes.VOID, [t1], [], IR_NoReturn(), "")
        expected:Tuple[Set[str], Set[str]] = ({"return_statement"}, {"args"})
        self.assertEqual(a1._get_sub_symbol_keys(), expected) # type: ignore
        
        a1.body = [t1] # type: ignore
        expected:Tuple[Set[str], Set[str]] = ({"return_statement"}, {"args", "body"})
        self.assertEqual(a1._get_sub_symbol_keys(), expected) # type: ignore

if __name__=="__main__":
    unittest.main()