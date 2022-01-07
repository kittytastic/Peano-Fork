from node import *
import unittest


class TestNodeINIT(unittest.TestCase):
    def test_global_ids(self):
        a = Node(1,2)
        b = Node(3,4)
        c = Node(4,5)

        self.assertEqual(a.id+1, b.id)
        self.assertEqual(b.id+1, c.id)


class TestGraph(unittest.TestCase):
    def test_square_brackets(self):
        a = Node(None, None)
        b = Node(None, None)

        g = Graph(2, 3)
        g[a]={b}
        self.assertEqual(g[a], {b})


if __name__=="__main__":
    unittest.main()