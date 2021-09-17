{-Haskell HW2 HUnit test cases
 Please add at least 2 additional tests for problems 3(b,c) and 4(a,b,c)-}

module HW2SampleTests
    where

import Test.HUnit
import Data.Char
import Data.List (sort)
import HW2


-- Sample Tree Integer examples given in the assignment prompt; make sure to provide your own tree examples
-- Your trees should have minimum 4 levels. 
tree1 =  NODE "grand-grand-mom" 
         (NODE "grand-mom" 
               (LEAF "aunt") 
               (NODE "mom" 
                      (LEAF "me") 
                      (LEAF "brother"))) 
          (LEAF "grand-uncle")

tree2 = NODE 1 (NODE 2 (NODE 3 (LEAF 4) (LEAF 5)) (LEAF 6)) 
               (NODE 7 (LEAF 8) (LEAF 9))

tree3 = NODE 1 (NODE 2 (NODE 3 (NODE 4 (NODE 5 (LEAF 6) (LEAF 7)) (LEAF 8)) (NODE 9 (LEAF 10) (LEAF 11))) (LEAF 12)) 
               (NODE 13 (LEAF 14) (NODE 15 (LEAF 16) (NODE 17 (LEAF 18) (LEAF 19))))

tree4 = NODE 1 (NODE 2 (NODE 3 (NODE 4 (NODE 5 (LEAF 6) (LEAF 7)) (NODE 8 (LEAF 9) (LEAF 10))) (LEAF 11)) (LEAF 12)) 
               (LEAF 13)

leveltree1 = LNODE ("grand-grand-mom",3,1) (LNODE ("grand-mom",1,2) (LLEAF "aunt") (LNODE ("mom",1,1) (LLEAF "me") (LLEAF "brother"))) (LLEAF "grand-uncle")
leveltree2 = LNODE (1,3,2) (LNODE (2,2,1) (LNODE (3,1,1) (LLEAF 4) (LLEAF 5)) (LLEAF 6)) (LNODE (7,1,1) (LLEAF 8) (LLEAF 9))
leveltree3 = LNODE (1,5,4) (LNODE (2,4,1) (LNODE (3,3,2) (LNODE (4,2,1) (LNODE (5,1,1) (LLEAF 6) (LLEAF 7)) (LLEAF 8)) (LNODE (9,1,1) (LLEAF 10) (LLEAF 11))) (LLEAF 12)) (LNODE (13,1,3) (LLEAF 14) (LNODE (15,1,2) (LLEAF 16) (LNODE (17,1,1) (LLEAF 18) (LLEAF 19))))
leveltree4 = LNODE (1,5,1) (LNODE (2,4,1) (LNODE (3,3,1) (LNODE (4,2,2) (LNODE (5,1,1) (LLEAF 6) (LLEAF 7)) (LNODE (8,1,1) (LLEAF 9) (LLEAF 10))) (LLEAF 11)) (LLEAF 12)) (LLEAF 13)

p1a_test1 = TestCase (assertEqual "longest-test1" [7,8,9,10]  (longest [[1],[5,7],[1,2,3],[7,8,9,10]]) )  
p1a_test2 = TestCase (assertEqual "longest-test2" "longest"  (longest ["which","of","these","words","is","the","longest","?"]) ) 
p1a_test3 = TestCase (assertEqual "longest-test3" [] ((longest [])::[Int]) ) 

p1b_test1 = TestCase (assertEqual "longestTail-test1" [7,8,9,10]  (longestTail [[1],[5,7],[1,2,3],[7,8,9,10]]) )  
p1b_test2 = TestCase (assertEqual "longestTail-test2" "longest"  (longestTail ["which","of","these","words","is","the","longest","?"]) ) 
p1b_test3 = TestCase (assertEqual "longestTail-test3" []  ((longestTail [])::[Int]) ) 

p1c_test1 = TestCase (assertEqual "mylongest-test1" [7,8,9,10]  (mylongest [[1],[5,7],[1,2,3],[7,8,9,10]]) )  
p1c_test2 = TestCase (assertEqual "mylongest-test2" "longest"  (mylongest ["which","of","these","words","is","the","longest","?"]) ) 
p1c_test3 = TestCase (assertEqual "mylongest-test3" []  ((mylongest [])::[Int]) ) 

myCatsLog = [((7,2020),[("Oceanfish",7),("Tuna",1),("Whitefish",3),("Chicken",4),("Beef",2)]),
             ((8,2020),[("Oceanfish",6),("Tuna",2),("Whitefish",1),("Salmon",3),("Chicken",6)]),
             ((9,2020),[("Tuna",3),("Whitefish",3),("Salmon",2),("Chicken",5),("Beef",2),("Turkey",1),("Sardines",1)]),
             ((10,2020),[("Whitefish",5),("Sardines",3),("Chicken",7),("Beef",3)]),
             ((11,2020),[("Oceanfish",3),("Tuna",2),("Whitefish",2),("Salmon",2),("Chicken",4),("Beef",2),("Turkey",1)]),
             ((12,2020),[("Tuna",2),("Whitefish",2),("Salmon",2),("Chicken",4),("Beef",2),("Turkey",4),("Sardines",1)]),              
             ((1,2021),[("Chicken",7),("Beef",3),("Turkey",4),("Whitefish",1),("Sardines",2)])
 ]

p2a_test1 = TestCase (assertEqual "getMonths-test1" [(7,2020),(8,2020)] (getMonths myCatsLog 4 "Oceanfish") ) 
p2a_test2 = TestCase (assertEqual "getMonths-test2" [(8,2020),(10,2020),(1,2021)] (getMonths myCatsLog 5 "Chicken" )) 

p2b_test1 = TestCase (assertEqual "monthlyCans-test1" [((7,2020),17),((8,2020),18),((9,2020),17),((10,2020),18),((11,2020),16),((12,2020),17),((1,2021),17)] (monthlyCans myCatsLog)) 

p3a_test1 = TestCase (assertEqual "convert-test1" (SCORE 4) (convert (LETTER 'A')) ) 
p3a_test2 = TestCase (assertEqual "convert-test2" (SCORE 2) (convert (LETTER 'C')) ) 
p3a_test3 = TestCase (assertEqual "convert-test3" (SCORE 0) (convert (LETTER 'F')) ) 
p3a_test4 = TestCase (assertEqual "convert-test4" (PASS) (convert PASS) ) 
p3a_test5 = TestCase (assertEqual "convert-test5" (SCORE 10) (convert (SCORE 10) ) ) 
p3a_test6 = TestCase (assertEqual "convert-test6" (FAIL) (convert (FAIL) ) )
p3a_test7 = TestCase (assertEqual "convert-test7" (SCORE 3) (convert (LETTER 'B') ) )  

p3b_test1 = TestCase (assertEqual "sumGrades-test1" (SCORE 14) (sumGrades [LETTER 'A', PASS , FAIL, SCORE 1, SCORE 2, SCORE 4, FAIL, PASS, LETTER 'D',LETTER 'C'] ) ) 
p3b_test2 = TestCase (assertEqual "sumGrades-test2" (SCORE 0) (sumGrades [PASS, FAIL]) ) 
p3b_test3 = TestCase (assertEqual "sumGrades-test3" (SCORE 0) (sumGrades []) )
p3b_test4 = TestCase (assertEqual "sumGrades-test4" (SCORE 11) (sumGrades [LETTER 'A', FAIL, SCORE 2, SCORE 5, LETTER 'F']) )
p3b_test5 = TestCase (assertEqual "sumGrades-test5" (SCORE 0) (sumGrades [LETTER 'F', FAIL, PASS, SCORE 0]) )

organize_output1 = [[("MATH216",SCORE 1),("CptS322",SCORE 4)], [("CptS355",LETTER 'A'),("CptS321",LETTER 'D'),("Math171",LETTER 'C')],[("CptS499",PASS),("EE499",FAIL)]]
organize_output2 = [[("MATH216",SCORE 1),("CptS322",SCORE 4)],[],[("CptS499",PASS),("EE499",FAIL)]]
organize_output3 = [[],[("CptS355",LETTER 'A'),("CptS321",LETTER 'D'),("Math171",LETTER 'C')],[]]
p3c_test1 = TestCase (assertEqual "organize-test1" organize_output1 (organize [("CptS355", LETTER 'A'), ("CptS499",PASS),("EE499",FAIL),("MATH216",SCORE 1), ("CptS322",SCORE 4), ("CptS321",LETTER 'D'),("Math171",LETTER 'C')] )) 
p3c_test2 = TestCase (assertEqual "organize-test2" organize_output2 (organize [("CptS499",PASS) , ("EE499",FAIL), ("MATH216",SCORE 1), ("CptS322",SCORE 4)]) ) 
p3c_test3 = TestCase (assertEqual "organize-test3" organize_output3 (organize [("CptS355", LETTER 'A'), ("CptS321",LETTER 'D'),("Math171",LETTER 'C')]) ) 
p3c_test4 = TestCase (assertEqual "organize-test4" [[], [], [("CptS355", FAIL)]] (organize [("CptS355", FAIL)]) ) 
p3c_test5 = TestCase (assertEqual "organize-test5" [[], [("CptS321",LETTER 'D')], []] (organize [("CptS321",LETTER 'D')]) ) 


p4a_test1 = TestCase (assertEqual "createLevelTree-test1" leveltree1  (createLevelTree tree1) ) 
p4a_test2 = TestCase (assertEqual "createLevelTree-test2" leveltree2  (createLevelTree tree2) ) 
p4a_test3 = TestCase (assertEqual "createLevelTree-test2" leveltree3  (createLevelTree tree3) )
p4a_test4 = TestCase (assertEqual "createLevelTree-test2" leveltree4  (createLevelTree tree4) )  

listify_output1 =  [("grand-grand-mom",3,1),("grand-mom",1,2), ("aunt",0,0),("mom",1,1),("me",0,0),("brother",0,0),("grand-uncle",0,0)]
listify_output2 =  [(1,3,2),(2,2,1),(3,1,1),(4,0,0),(5,0,0),(6,0,0),(7,1,1),(8,0,0),(9,0,0)]
listify_output3 =  [(1,5,4),(2,4,1),(3,3,2),(4,2,1),(5,1,1),(6,0,0),(7,0,0),(8,0,0),(9,1,1),(10,0,0),(11,0,0),(12,0,0),(13,1,3),(14,0,0),(15,1,2),(16,0,0),(17,1,1),(18,0,0),(19,0,0)]
listify_output4 =  [(1,5,1),(2,4,1),(3,3,1),(4,2,2),(5,1,1),(6,0,0),(7,0,0),(8,1,1),(9,0,0),(10,0,0),(11,0,0),(12,0,0),(13,0,0)]
p4b_test1 = TestCase (assertEqual "listify-test1" listify_output1 (listify leveltree1) ) 
p4b_test2 = TestCase (assertEqual "listify-test2" listify_output2  (listify leveltree2) ) 
p4b_test3 = TestCase (assertEqual "listify-test2" listify_output3  (listify leveltree3) ) 
p4b_test4 = TestCase (assertEqual "listify-test2" listify_output4  (listify leveltree4) ) 

p4c_test1 = TestCase (assertEqual "isBalanced-test1" False (isBalanced leveltree1) ) 
p4c_test2 = TestCase (assertEqual "isBalanced-test2" True  (isBalanced leveltree2) ) 
p4c_test3 = TestCase (assertEqual "isBalanced-test2" False  (isBalanced leveltree3) ) 
p4c_test4 = TestCase (assertEqual "isBalanced-test2" False  (isBalanced leveltree4) ) 


tests = TestList [ TestLabel "Problem 1a - test1 " p1a_test1,
                   TestLabel "Problem 1a - test2 " p1a_test2,
                   TestLabel "Problem 1a - test3 " p1a_test3,                   
                   TestLabel "Problem 1b - test1 " p1b_test1,
                   TestLabel "Problem 1b - test2 " p1b_test2,                   
                   TestLabel "Problem 1b - test3 " p1b_test3,                                      
                   TestLabel "Problem 1c - test1 " p1c_test1,
                   TestLabel "Problem 1c - test2 " p1c_test2,
                   TestLabel "Problem 1c - test3 " p1c_test3,                                      
                   TestLabel "Problem 2a - test1 " p2a_test1,
                   TestLabel "Problem 2a - test2 " p2a_test2,  
                   TestLabel "Problem 2b - test1 " p2b_test1,  
                   TestLabel "Problem 3a - test1 " p3a_test1,
                   TestLabel "Problem 3a - test2 " p3a_test2,  
                   TestLabel "Problem 3a - test3 " p3a_test3, 
                   TestLabel "Problem 3a - test4 " p3a_test4, 
                   TestLabel "Problem 3a - test5 " p3a_test5, 
                   TestLabel "Problem 3a - test6 " p3a_test6,
                   TestLabel "Problem 3a - test7 " p3a_test7,  
                   TestLabel "Problem 3b - test1 " p3b_test1,
                   TestLabel "Problem 3b - test2 " p3b_test2,
                   TestLabel "Problem 3b - test3 " p3b_test3,
                   TestLabel "Problem 3b - test4 " p3b_test4,
                   TestLabel "Problem 3b - test5 " p3b_test5,
                   TestLabel "Problem 3c - test1 " p3c_test1,
                   TestLabel "Problem 3c - test2 " p3c_test2,
                   TestLabel "Problem 3c - test3 " p3c_test3,
                   TestLabel "Problem 3c - test4 " p3c_test4,
                   TestLabel "Problem 3c - test5 " p3c_test5,
                   TestLabel "Problem 4a - test1 " p4a_test1,
                   TestLabel "Problem 4a - test2 " p4a_test2,
                   TestLabel "Problem 4a - test3 " p4a_test3,
                   TestLabel "Problem 4a - test4 " p4a_test4,
                   TestLabel "Problem 4b - test1 " p4b_test1,
                   TestLabel "Problem 4b - test2 " p4b_test2,
                   TestLabel "Problem 4b - test3 " p4b_test3,
                   TestLabel "Problem 4b - test4 " p4b_test4,
                   TestLabel "Problem 4c - test1 " p4c_test1,
                   TestLabel "Problem 4c - test2 " p4c_test2,
                   TestLabel "Problem 4c - test3 " p4b_test3,
                   TestLabel "Problem 4c - test4 " p4b_test4
                 ] 
                  

-- shortcut to run the tests
run = runTestTT  tests