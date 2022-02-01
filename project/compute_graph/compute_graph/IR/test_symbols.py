from compute_graph.IR.symbols import *
import unittest

class TestIRSymIN(unittest.TestCase):
    def test_object_1(self):
        t1 = IR_TempVariable("test", 1)
        t2 = IR_TempVariable("test", 2)
        a1 = IR_SingleAssign(t1, t2)

        self.assertTrue(t1 in a1)
        self.assertTrue(t2 in a1)
    
    def test_object_2(self):
        t1 = IR_TempVariable("test", 1)
        t2 = IR_TempVariable("test", 2)
        t3 = IR_TempVariable("test", 3)
        s1 = IR_Sub(t1, t2)
        a1 = IR_SingleAssign(t3, s1)

        self.assertTrue(t1 in a1)
        self.assertTrue(t2 in a1)
        self.assertTrue(t3 in a1)
        self.assertTrue(s1 in a1)
    
    def test_object_3(self):
        t1 = IR_TempVariable("test", 1)
        t2 = IR_TempVariable("test", 2)
        a1 = IR_CallFunction([t1, t2])

        self.assertTrue(t1 in a1)
        self.assertTrue(t2 in a1)
    
    def test_class_1(self):
        t1 = IR_TempVariable("test", 1)
        t2 = IR_TempVariable("test", 2)
        a1 = IR_SingleAssign(t1, t2)

        self.assertTrue(IR_TempVariable in a1)
    
    def test_class_2(self):
        t1 = IR_TempVariable("test", 1)
        t2 = IR_TempVariable("test", 2)
        t3 = IR_TempVariable("test", 3)
        s1 = IR_Sub(t1, t2)
        a1 = IR_SingleAssign(t3, s1)

        self.assertTrue(IR_TempVariable in a1)
        self.assertTrue(IR_Sub in a1)
    
    def test_class_3(self):
        t1 = IR_TempVariable("test", 1)
        t2 = IR_TempVariable("test", 2)
        a1 = IR_CallFunction([t1, t2])

        self.assertTrue(IR_TempVariable in a1)

class TestIRSymReplace(unittest.TestCase):
    def test_1(self):
        t1 = IR_TempVariable("test", 1)
        t2 = IR_TempVariable("test", 2)
        n1 = IR_TempVariable("new", 1)
        a1 = IR_SingleAssign(t1, t2)

        self.assertEqual(a1.replace(t2, n1), 1)
        self.assertEqual(a1.expr, n1)
    
    def test_2(self):
        t1 = IR_TempVariable("test", 1)
        t2 = IR_TempVariable("test", 2)
        n1 = IR_TempVariable("new", 1)
        s1 = IR_Sub(t1, t2)
        a1 = IR_SingleAssign(t2, s1)

        self.assertEqual(a1.replace(t2, n1), 2)
        self.assertEqual(a1.assign_var, n1)
        self.assertEqual(s1.rval, n1)
    
    def test_3(self):
        t1 = IR_TempVariable("test", 1)
        t2 = IR_TempVariable("test", 2)
        n1 = IR_TempVariable("new", 1)
        a1 = IR_CallFunction([t1, t2])

        self.assertEqual(a1.replace(t2, n1), 1)
        self.assertEqual(a1.args[1], n1)
    
    def test_4(self):
        t1 = IR_TempVariable("test", 1)
        n1 = IR_TempVariable("new", 1)

        with self.assertRaises(Exception):
            t1.replace(t1, n1)


if __name__=="__main__":
    unittest.main()