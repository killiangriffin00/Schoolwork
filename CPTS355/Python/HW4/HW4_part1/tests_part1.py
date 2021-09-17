from stacks import Stacks
import unittest
import sys
sys.path.append('../')
from stacks import *

class HW4Sampletests_part1(unittest.TestCase):
    #If the setUp doesn't clear the stacks succesfully, copy the following function to HW4_part1.py and call it in setup. 

    def setUp(self):
        #create the Stack object
        self.psstacks = Stacks()
        #clear the opstack and the dictstack
        self.psstacks.clearBoth() 

    # Tests for helper functions : define, lookup   
    def test_lookup1(self):
        self.psstacks.dictPush({'/v':3, '/x': 20})
        self.psstacks.dictPush({'/v':4, '/x': 10})
        self.psstacks.dictPush({'/v':5})
        self.assertEqual(self.psstacks.lookup('x'),10)
        self.assertEqual(self.psstacks.lookup('v'),5)

    def testLookup2(self):
        self.psstacks.dictPush({'/a':355})
        arrayV = ArrayConstant([3,5,5])
        self.psstacks.dictPush({'/a':arrayV})
        self.assertTrue(self.psstacks.lookup("a") is arrayV)
        self.assertEqual(self.psstacks.lookup("a").value,arrayV.value)

    def test_define1(self):
        self.psstacks.dictPush({})
        self.psstacks.define("/n1", 4)
        self.assertEqual(self.psstacks.lookup("n1"),4)

    def test_define2(self):
        self.psstacks.dictPush({})
        self.psstacks.define("/n1", 4)
        self.psstacks.define("/n1", 5)
        self.psstacks.define("/n2", 6)
        self.assertEqual(self.psstacks.lookup("n1"),5)
        self.assertEqual(self.psstacks.lookup("n2"),6)        

    def test_define3(self):
        self.psstacks.dictPush({})
        self.psstacks.define("/n1", 4)
        self.psstacks.dictPush({})
        self.psstacks.define("/n2", 6)
        self.psstacks.define("/n2", 7)
        self.psstacks.dictPush({})
        self.psstacks.define("/n1", 6)
        self.assertEqual(self.psstacks.lookup("n1"),6)
        self.assertEqual(self.psstacks.lookup("n2"),7)    
    #-----------------------------------------------------
    #Arithmatic operator tests
    def test_add(self):
        #9 3 add
        self.psstacks.opPush(9)
        self.psstacks.opPush(3)
        self.psstacks.add()
        self.assertEqual(self.psstacks.opPop(),12)

    def test_sub(self):
        #10 2 sub
        self.psstacks.opPush(10)
        self.psstacks.opPush(2)
        self.psstacks.sub()
        self.assertEqual(self.psstacks.opPop(),8)

    def test_mul(self):
        #2 40 mul
        self.psstacks.opPush(2)
        self.psstacks.opPush(40)
        self.psstacks.mul()
        self.assertEqual(self.psstacks.opPop(),80)
    #-----------------------------------------------------
    #Comparison operators tests
    def test_eq1(self):
        #6 6 eq
        self.psstacks.opPush(6)
        self.psstacks.opPush(6)
        self.psstacks.eq()
        self.assertEqual(self.psstacks.opPop(),True)

    def test_eq2(self):
        #[1 2 3 4] [4 3 2 1] eq
        self.psstacks.opPush(ArrayConstant([1,2,3,4]))
        self.psstacks.opPush(ArrayConstant([1,2,3,4]))
        self.psstacks.eq()
        self.assertEqual(self.psstacks.opPop(),False)
        arr1 = ArrayConstant([1,2,3,4])
        self.psstacks.opPush(arr1)
        self.psstacks.opPush(arr1)
        self.psstacks.eq()
        self.assertEqual(self.psstacks.opPop(),True)

    def test_lt(self):
        #3 6 lt
        self.psstacks.opPush(3)
        self.psstacks.opPush(6)
        self.psstacks.lt()
        self.assertEqual(self.psstacks.opPop(),True)

    def test_gt(self):
        #4 5 gt
        self.psstacks.opPush(4)
        self.psstacks.opPush(5)
        self.psstacks.gt()
        self.assertEqual(self.psstacks.opPop(),False)

    #-----------------------------------------------------
    #stack manipulation operator tests
    def test_dup(self):
        #[3 5 5 True 4]  dup
        self.psstacks.opPush(ArrayConstant([3,5,5,True,4]))
        self.psstacks.dup()
        isSame = self.psstacks.opPop() is self.psstacks.opPop()
        self.assertTrue(isSame)

    def test_exch(self):
        # /x 10 exch
        self.psstacks.opPush('/x')
        self.psstacks.opPush(10)
        self.psstacks.exch()
        self.assertEqual(self.psstacks.opPop(),'/x')
        self.assertEqual(self.psstacks.opPop(),10)

    def test_pop(self):
        l1 = len(self.psstacks.opstack)
        self.psstacks.opPush(10)
        self.psstacks.pop()
        l2 = len(self.psstacks.opstack)
        self.assertEqual(l1,l2)

    def test_copy(self):
        #true 1 3 4 3 copy
        self.psstacks.opPush(True)
        self.psstacks.opPush(1)
        self.psstacks.opPush(3)
        self.psstacks.opPush(4)
        self.psstacks.opPush(3)
        self.psstacks.copy()
        self.assertTrue(self.psstacks.opPop()==4 and self.psstacks.opPop()==3 and self.psstacks.opPop()==1 and self.psstacks.opPop()==4 and self.psstacks.opPop()==3 and self.psstacks.opPop()==1 and self.psstacks.opPop()==True)
        
    def test_clear(self):
        #10 /x clear
        self.psstacks.opPush(10)
        self.psstacks.opPush("/x")
        self.psstacks.clear()
        self.assertEqual(len(self.psstacks.opstack),0)

    #-----------------------------------------------------
    #String operator tests
    def test_length(self):
        #(CptS355) length
        self.psstacks.opPush(StrConstant('(CptS355)'))
        self.psstacks.length()
        self.assertEqual(self.psstacks.opPop(),7)      
        self.assertTrue(len(self.psstacks.opstack)==0) 
        #length will not push back the string onto the opstack

    def test_length_StrConstant(self):
        self.psstacks.opPush(StrConstant('(ABCDEFGHIJKLMNOPQRSTUVWXYZ)'))
        self.psstacks.length()
        self.assertEqual(self.psstacks.opPop(),26)
        self.assertTrue(len(self.psstacks.opstack)==0)

    def test_length_ArrayConstant(self):
        self.psstacks.opPush(ArrayConstant([0,1,2,4,5]))
        self.psstacks.length()
        self.assertEqual(self.psstacks.opPop(), 5)
        self.assertTrue(len(self.psstacks.opstack) == 0)

    def test_get_StrConstant1(self):
        #(CptS355) 3 get
        self.psstacks.opPush(StrConstant('(CptS355)'))
        self.psstacks.opPush(3)
        self.psstacks.get()
        self.assertEqual(self.psstacks.opPop(),83)
        self.assertTrue(len(self.psstacks.opstack)==0)
        #get will not push back the string onto the opstack

    def test_get_StrConstant2(self):
        self.psstacks.opPush(StrConstant('(Python)'))
        self.psstacks.opPush(0)
        self.psstacks.get()
        self.assertEqual(self.psstacks.opPop(), 80)
        self.assertTrue(len(self.psstacks.opstack) == 0)

    def test_get_ArrayConstant1(self):
        #[0,1,2,100,4] 3 get
        self.psstacks.opPush(ArrayConstant([0,1,2,100,4]))
        self.psstacks.opPush(3)
        self.psstacks.get()
        self.assertEqual(self.psstacks.opPop(),100)
        self.assertTrue(len(self.psstacks.opstack)==0)
        #get will not push back the string onto the opstack 

    def test_get_ArrayConstant2(self):
        self.psstacks.opPush(ArrayConstant([0,1,0,0,0,0]))
        self.psstacks.opPush(1)
        self.psstacks.get()
        self.assertEqual(self.psstacks.opPop(),1)
        self.assertTrue(len(self.psstacks.opstack)==0)

    def test_put_StrConstant1(self):
        #(CptS451) dup 4 51 put 
        str1 = StrConstant('(CptS451)')
        self.psstacks.opPush(str1)
        self.psstacks.dup()  #duplicating the string reference
        self.psstacks.opPush(4)
        self.psstacks.opPush(51)  # ascii value for '3'
        self.psstacks.put()  #put will not push back the changed string onto the opstack 
        str2 = self.psstacks.opPop()
        self.assertTrue(str2 is str1)  #we pop the string reference we copied with "dup"; check if it the same object
        self.assertEqual(str2.value,'(CptS351)')  #we check if the StrConstant object value is updated
        self.assertTrue(len(self.psstacks.opstack)==0)

    def test_put_StrConstant2(self):
        #/x (CptS321) def x 6 50 put x
        str1 = StrConstant('(CptS321)')
        self.psstacks.opPush('/x')
        self.psstacks.opPush(str1)
        self.psstacks.psDef()  #defines x; x holds the string reference
        self.psstacks.opPush(self.psstacks.lookup('x'))
        self.psstacks.opPush(6)
        self.psstacks.opPush(50)  # ascii value for '1'
        self.psstacks.put()  #put will not push back the changed string onto the opstack 
        self.psstacks.opPush(self.psstacks.lookup('x'))
        str2 = self.psstacks.opPop()
        self.assertTrue(str2 is str1)  #we pop the string reference we saved in x; check if it the same object
        self.assertEqual(str2.value,'(CptS322)')  #we check if the StrConstant object value is updated
        self.assertTrue(len(self.psstacks.opstack)==0)

    def test_put_StrConstant3(self):
        str1 = StrConstant('(Python)')
        self.psstacks.opPush('/x')
        self.psstacks.opPush(str1)
        self.psstacks.psDef()
        self.psstacks.opPush(self.psstacks.lookup('x'))
        self.psstacks.opPush(1)
        self.psstacks.opPush(105)
        self.psstacks.put()
        self.psstacks.opPush(self.psstacks.lookup('x'))
        str2 = self.psstacks.opPop()
        self.assertTrue(str2 is str1)
        self.assertEqual(str2.value,'(Pithon)')
        self.assertTrue(len(self.psstacks.opstack)==0)

    def test_put_ArrayConstant1(self):
        #[3,5,5] dup dup dup 1 2 put 2 2  put 
        arr1 = ArrayConstant([3,5,5])
        self.psstacks.opPush(arr1)
        self.psstacks.dup()  #duplicating the array reference
        self.psstacks.dup()  #duplicating the array reference
        self.psstacks.dup()  #duplicating the array reference
        self.psstacks.opPush(1)
        self.psstacks.opPush(2)  # the item at index 1 will be replaced by 2
        self.psstacks.put()  #put will not push back the changed array onto the opstack 
        self.psstacks.opPush(2)
        self.psstacks.opPush(2)  # the item at index 2 will be replaced by 2
        self.psstacks.put()  #put will not push back the changed array onto the opstack 
        arr2 = self.psstacks.opPop()
        self.assertTrue(arr2 is arr1)  #we pop the string reference we copied with "dup"; check if it the same object
        self.assertEqual(arr2.value,[3,2,2])  # we check if the ArrConstant object value is updated
        arr3 = self.psstacks.opPop()
        self.assertTrue(arr3 is arr1)  #we pop the string reference we copied with "dup"; check if it the same object
        self.assertEqual(arr3.value,[3,2,2])  # we check if the ArrConstant object value is updated
        self.assertTrue(len(self.psstacks.opstack)==0)

    def test_put_ArrayConstant2(self):
        #/x [1,1,1] def x 1 3 put x 
        arr1 = ArrayConstant([1,1,1])
        self.psstacks.opPush('/x')
        self.psstacks.opPush(arr1)
        self.psstacks.psDef()  #defines x; x holds the array reference
        self.psstacks.opPush(self.psstacks.lookup('x'))  # pushed the array reference x holds onto the stack
        self.psstacks.opPush(1)
        self.psstacks.opPush(3)  # the item at index 1 will be replaced by 3
        self.psstacks.put()  #put will not push back the changed array onto the opstack 
        self.psstacks.opPush(self.psstacks.lookup('x'))  # pushed the array reference x holds onto the stack
        arr2 = self.psstacks.opPop()
        self.assertTrue(arr2 is arr1)  #we pop the array reference ; check if it the same object
        self.assertEqual(arr2.value,[1,3,1])  # we check if the ArrConstant object value is updated
        self.assertTrue(len(self.psstacks.opstack)==0)

    def test_put_ArrayConstant3(self):
        arr1 = ArrayConstant([0,0,0,0,0,0,1,0,0])
        self.psstacks.opPush('/x')
        self.psstacks.opPush(arr1)
        self.psstacks.psDef()
        self.psstacks.opPush(self.psstacks.lookup('x'))
        self.psstacks.opPush(6)
        self.psstacks.opPush(0)
        self.psstacks.put()
        self.psstacks.opPush(self.psstacks.lookup('x'))
        arr2 = self.psstacks.opPop()
        self.assertTrue(arr2 is arr1)
        self.assertEqual(arr2.value,[0,0,0,0,0,0,0,0,0])
        self.assertTrue(len(self.psstacks.opstack)==0)


    #-----------------------------------------------------
    #dictionary stack operators
    def test_dict(self):
        #1 dict
        self.psstacks.opPush(1)
        self.psstacks.psDict()
        self.assertEqual(self.psstacks.opPop(),{})

    def test_psDef(self):
        #/x 10 def /x 20 def x
        self.psstacks.dictPush({})
        self.psstacks.opPush("/x")
        self.psstacks.opPush(10)
        self.psstacks.psDef()
        self.psstacks.opPush("/x")
        self.psstacks.opPush(20)
        self.psstacks.psDef()
        self.assertEqual(self.psstacks.lookup('x'),20)

    def test_psDef2(self):
        #/x 10 def 1 dict begin /y 20 def x
        self.psstacks.dictPush({})
        self.psstacks.opPush("/x")
        self.psstacks.opPush(10)
        self.psstacks.psDef()
        self.psstacks.dictPush({})
        self.psstacks.opPush("/y")
        self.psstacks.opPush(20)
        self.psstacks.psDef()
        self.assertEqual(self.psstacks.lookup('x'),10)

    def test_psDef4(self):
        self.psstacks.dictPush({})
        self.psstacks.opPush("/x")
        self.psstacks.opPush(0)
        self.psstacks.psDef()
        self.psstacks.opPush("/x")
        self.psstacks.opPush(1)
        self.psstacks.psDef()
        self.assertEqual(self.psstacks.lookup('x'),1)

    def test_beginEnd(self):
        #/x 3 def 1 dict begin /x 4 def end x
        self.psstacks.opPush(1)
        self.psstacks.psDict()
        self.psstacks.opPush("/x")
        self.psstacks.opPush(3)
        self.psstacks.psDef()
        self.psstacks.opPush(1)
        self.psstacks.psDict()
        self.psstacks.begin()
        self.psstacks.opPush("/x")
        self.psstacks.opPush(4)
        self.psstacks.psDef()
        self.psstacks.end() 
        self.assertEqual(self.psstacks.lookup('x'),3)

    def test_psDef3(self):
        #/x 3 def 1 dict begin /x 30 def 1 dict begin /x 300 def end x
        # define x in the bottom dictionary
        self.psstacks.dictPush({})
        self.psstacks.opPush("/x")
        self.psstacks.opPush(3)
        self.psstacks.psDef()
        # define x in the second dictionary
        self.psstacks.dictPush({})
        self.psstacks.opPush("/x")
        self.psstacks.opPush(30)
        self.psstacks.psDef()
        # define x in the third dictionary
        self.psstacks.dictPush({})
        self.psstacks.opPush("/x")
        self.psstacks.opPush(300)
        self.psstacks.psDef()
        self.psstacks.dictPop()
        self.assertEqual(self.psstacks.lookup('x'),30)

if __name__ == '__main__':
    unittest.main()

