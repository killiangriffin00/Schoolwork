import unittest
from HW3 import *

class HW3SampleTests(unittest.TestCase):
    def setUp(self):
        self.myCatsLog = {(7,2020):{"Oceanfish":7, "Tuna":1, "Whitefish":3, "Chicken":4, "Beef":2},
              (8,2020):{"Oceanfish":6, "Tuna":2, "Whitefish":1, "Salmon":3, "Chicken":6},
              (9,2020):{"Tuna":3, "Whitefish":3, "Salmon":2, "Chicken":5, "Beef":2, "Turkey":1, "Sardines":1},
              (10,2020):{"Whitefish":5, "Sardines":3, "Chicken":7, "Beef":3},
              (11,2020):{"Oceanfish":3, "Tuna":2, "Whitefish":2, "Salmon":2, "Chicken":4, "Beef":2, "Turkey":1},
              (12,2020):{"Tuna":2, "Whitefish":2, "Salmon":2, "Chicken":4, "Beef":2, "Turkey":4, "Sardines":1},
              (1,2021):{"Chicken":7,"Beef":3, "Turkey":4, "Whitefish":1, "Sardines":2} } 
        self.graph = {'A':'B','B':'D','C':'G','D':'E','E':'C', 'F':'I','G':'B','H':None,'I':'H'}

    def test_organizebyFlavor(self):
        output = {'Beef': {(7, 2020): 2, (9, 2020): 2, (10, 2020): 3, (11, 2020): 2, (12, 2020): 2, (1, 2021): 3}, 'Chicken': {(7, 2020): 4, (8, 2020): 6, (9, 2020): 5, (10, 2020): 7, (11, 2020): 4, (12, 2020): 4, (1, 2021): 7}, 'Oceanfish': {(7, 2020): 7, (8, 2020): 6, (11, 2020): 3}, 'Salmon': {(8, 2020): 3, (9, 2020): 2, (11, 2020): 2, (12, 2020): 2}, 'Sardines': {(9, 2020): 1, (10, 2020): 3, (12, 2020): 1, (1, 2021): 2}, 'Tuna': {(7, 2020): 1, (8, 2020): 2, (9, 2020): 3, (11, 2020): 2, (12, 2020): 2}, 'Turkey': {(9, 2020): 1, (11, 2020): 1, (12, 2020): 4, (1, 2021): 4}, 'Whitefish': {(7, 2020): 3, (8, 2020): 1, (9, 2020): 3, (10, 2020): 5, (11, 2020): 2, (12, 2020): 2, (1, 2021): 1}}
        self.assertDictEqual(organizebyFlavor(self.myCatsLog),output)

    def test_popularFlavor(self):
        self.assertEqual(popularFlavor(self.myCatsLog),('Chicken', 37) )

    def test_unzip(self):
        self.assertEqual(unzip ([(1,"a",10),(2,"b",11),(3,"c",12),(4,"d",13)]),([1, 2, 3, 4], ['a', 'b', 'c', 'd'], [10, 11, 12, 13]))
        self.assertEqual(unzip ([("CptS",355,{"CptS":355}),("EE",451,{"EE":451}),("CptS",322,{"CptS":322})]) , (["CptS", "EE", "CptS"], [355,451,322], [{"CptS":355},{"EE":451},{"CptS":322}]))

    def test_findCycle(self):
        self.assertEqual(findCycle(self.graph,'A'), ['B', 'D', 'E', 'C', 'G', 'B'])
        self.assertEqual(findCycle(self.graph,'F'),None)

    
    def test_getNextNode(self):
        #test1
        graph_nodes1 = getNextNode(self.graph,'A')
        L = []
        self.assertEqual(graph_nodes1.__next__(),'A')
        self.assertEqual(graph_nodes1.__next__(),'B')
        for i in range(0,15):
            L.append(graph_nodes1.__next__())
        self.assertEqual(L,['D', 'E', 'C', 'G', 'B', 'D', 'E', 'C', 'G', 'B', 'D', 'E', 'C', 'G', 'B'])

        #test2
        graph_nodes2 = getNextNode(self.graph,'F')
        L = []
        self.assertEqual(graph_nodes2.__next__(),'F')
        self.assertEqual(graph_nodes2.__next__(),'I')
        for w in graph_nodes2:
            L.append(w)
        self.assertEqual(L,['H'])

    def test_DecodeIter(self):
        #helper decorator function for DecodeIter tests
        def infWords():
            current = 'a'
            nextchar = chr(ord(current)+1)
            n = 1
            while True:
                yield current
                n += 1
                if n>4:
                    current = ' '
                    n=0
                else:
                    current = nextchar
                    nextchar = chr(ord(nextchar)+1)
                    if nextchar > 'z':
                        nextchar = 'a'

    	#test 1
        ttable1 = {'C':'A', 'D':'B', 'E':'C', 'F':'D', 'G':'E', 'H':'F', 'I':'G', 'J':'H', 'K':'I', 'L':'J', 'M':'K', 'N':'L', 'O':'M', 'P':'N', 'Q':'O', 'R':'P', 'S':'Q', 'T':'R', 'U':'S', 'V':'T', 'W':'U', 'X':'V', 'Y':'W', 'Z':'X', '[':'Y', '\\':'Z', 'c':'a', 'd':'b', 'e':'c', 'f':'d', 'g':'e', 'h':'f', 'i':'g', 'j':'h', 'k':'i', 'l':'j', 'm':'k', 'n':'l', 'o':'m', 'p':'n', 'q':'o', 'r':'p', 's':'q', 't':'r', 'u':'s', 'v':'t', 'w':'u', 'x':'v', 'y':'w', 'z':'x', '{':'y', '|':'z', '2':'0', '3':'1', '4':'2', '5':'3', '6':'4', '7':'5', '8':'6', '9':'7', ':':'8', ';':'9'}
        strInput1 = "R{vjqp ku cp gcu{ vq ngctp, rqygthwn rtqitcookpi ncpiwcig. Kv jcu ghhkekgpv jkij-ngxgn fcvc uvtwevwtgu cpf c ukorng dwv ghhgevkxg crrtqcej vq qdlgev qtkgpvgf-rtqitcookpi. R{vjqp'u gngicpv u{pvcz cpf f{pcoke v{rkpi, vqigvjgt ykvj kvu kpvgtrtgvgf pcvwtg, ocmg kv cp kfgcn ncpiwcig hqt uetkrvkpi cpf tcrkf crrnkecvkqp fgxgnqrogpv kp ocp{ ctgcu qp oquv rncvhqtou."
        output1 = ['to', 'learn,', 'powerful', 'programming', 'language.', 'It', 'has', 'efficient', 'high-level', 'data', 'structures', 'and', 'a', 'simple', 'but', 'effective', 'approach', 'to', 'object', 'oriented-programming.', "Python's", 'elegant', 'syntax', 'and', 'dynamic', 'typing,', 'together', 'with', 'its', 'interpreted', 'nature,', 'make', 'it', 'an', 'ideal', 'language', 'for', 'scripting', 'and', 'rapid', 'application', 'development', 'in', 'many', 'areas', 'on', 'most', 'platforms.']

        words = DecodeIter(ttable1,strInput1)
        L = []
        self.assertEqual(words.__next__(),'Python')
        self.assertEqual(words.__next__(), 'is') 
        self.assertEqual(words.__next__(), 'an')
        self.assertEqual(words.__next__(), 'easy')
        for w in words:
            L.append(w)
        self.assertEqual(L, output1)

    	#test 2
        ttable2 = {'c':'a', 'd':'b', 'e':'c', 'f':'d', 'g':'e', 'h':'f', 'i':'g', 'j':'h', 'k':'i', 'l':'j', 'm':'k', 'n':'l', 'o':'m', 'p':'n', 'q':'o', 'r':'p', 's':'q', 't':'r', 'u':'s', 'v':'t', 'w':'u', 'x':'v', 'y':'w', 'z':'x' }
        strInput2 = infWords()
        output2 = ['ghij', 'klmn', 'opqr', 'stuv', 'wxab', 'abcd', 'efgh', 'ijkl', 'mnop', 'qrst', 'uvwx', 'abab', 'cdef', 'ghij', 'klmn', 'opqr', 'stuv', 'wxab', 'abcd', 'efgh']

        words2 = DecodeIter(ttable2,strInput2)
        L = []
        self.assertEqual(words2.__next__(),'abab')
        self.assertEqual(words2.__next__(), 'cdef') 
        for i in range(0,20):
            L.append(words2.__next__())
        self.assertEqual(L, output2)

if __name__ == '__main__':
    unittest.main()

