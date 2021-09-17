-- CPTS 355 Spring 2021
-- NAME: Killian Griffin
-- ASSIGNMENT: Homework 2

module HW2
     where

{- 1. longest & longestTail &  mylongest - 20%-}

{- (a) longest - 5% -}
     longest :: (Eq a) => [[a]] -> [a]
     longest l = helper l []
                        where helper :: (Eq c) => [[c]] -> [c] -> [c]
                              helper [] b = b
                              helper (x:xs) b | b == [] = helper xs x
                                              | length b < length x = helper xs x
                                              | otherwise = helper xs b

{- (b) longestTail - 10% -}
     longestTail :: (Eq a) => [[a]] -> [a]
     longestTail l = helper l []
                        where helper :: (Eq c) => [[c]] -> [c] -> [c]
                              helper [] b = b
                              helper (x:xs) b | b == [] = helper xs x
                                              | length b < length x = helper xs x
                                              | otherwise = helper xs b

{- (c) mylongest - 5% -}
     mylongest :: (Eq a) => [[a]] -> [a]
     mylongest l = foldl longer [] l
                    where longer x y | length y > length x = y
                                     | otherwise = x

-----------------------------------------------------------

{- 2. getMonths & monthlyCans 20% -}

{- (a) getMonths - 10%-}
-- please don't include the myCatsLog list in your dolution file. 
     getMonths :: (Eq t2) => [((a, b), [(t2, Int)])] -> Int -> t2 -> [(a, b)]
     getMonths l n s = map getMonth (filter (\x -> exceedCans n s x) l)
                         where getMonth :: (Eq t2) => ((a, b), [(t2, Int)]) -> (a,b)  
                               getMonth ((x, y), _) = (x, y)
                               exceedCans :: (Eq b) => Int -> b -> ((x, y),[(b, Int)]) -> Bool
                               exceedCans n s (month, list) | foldl (+) 0 (map getNum (filter (\x -> isFlavor s x) list)) > n = True
                                                            | otherwise = False
                                                                 where getNum (x, y) = y
                                                                       isFlavor :: (Eq d) => d -> (d, e) -> Bool
                                                                       isFlavor a (x, y) | a == x = True
                                                                                         | otherwise = False

{- (b) monthlyCans - 10%-}
     monthlyCans :: Num t1 => [((a1,a2), [(t2, t1)])] -> [((a1,a2), t1)]
     monthlyCans l = map numCans l
                    where numCans :: Num t1 => ((a1, a2), [(t2, t1)]) -> ((a1, a2), t1)
                          numCans (month, e) = (month, foldl (+) 0 (map getNum e))
                                   where getNum (x, y) = y

-----------------------------------------------------------

{- 3. convert, sumGrades, and organize  - 23% -}

--define the Grade datatype
     data Grade = LETTER Char |  SCORE Int | PASS | FAIL 
                   deriving (Show, Eq, Ord)

{- (a) convert - 3% -}
     convert :: Grade -> Grade
     convert (SCORE s) = SCORE s
     convert (PASS) = PASS
     convert (FAIL) = FAIL
     convert (LETTER l) | l == 'A' = (SCORE 4)
                        | l == 'B' = (SCORE 3)
                        | l == 'C' = (SCORE 2)
                        | l == 'D' = (SCORE 1)
                        | l == 'F' = (SCORE 0)

{- (b) sumGrades - 10% -}
     sumGrades :: [Grade] -> Grade
     sumGrades l = SCORE (foldl (+) 0 (map getNum (map convert l)))
                    where getNum :: Grade -> Int
                          getNum PASS = 0
                          getNum FAIL = 0
                          getNum (SCORE s) = s

{- (c) organize - 10% -}
     organize :: [(a, Grade)] -> [[(a, Grade)]]
     organize l = [filter isScore l, filter isLetter l, filter isPF l]
                    where isScore (s, (SCORE a)) = True
                          isScore (s, a) = False
                          isLetter (s, (LETTER a)) = True
                          isLetter (s, a) = False
                          isPF (s, PASS) = True
                          isPF (s, FAIL) = True
                          isPF (s, a) = False

-----------------------------------------------------------

{-4 - createLevelTree & listify & isBalanced  - 27%-}

     data Tree a = LEAF a | NODE a (Tree a) (Tree a)
                    deriving (Show, Read, Eq)

     data LevelTree a = LLEAF a | LNODE (a,Int,Int) (LevelTree a) (LevelTree a)
                         deriving (Show, Read, Eq)

{- (a) createLevelTree - 12% -}
     createLevelTree :: Tree a -> LevelTree a
     createLevelTree (LEAF l) = LLEAF l
     createLevelTree t = getFinalNode (helper t)
                         where getFinalNode (l, n) = l
                               helper :: Tree a -> (LevelTree a, Int)
                               helper (LEAF l) = ((LLEAF l), 1)
                               helper (NODE a l r) = ((LNODE (a, getNum(helper l), getNum(helper r) ) (getNode(helper l)) (getNode(helper r))), (1 + max (getNum(helper l)) (getNum(helper r))))
                                                                      where getNum (l, n) = n
                                                                            getNode (l, n) = l

{- (b) listify - 6% -}
     listify :: LevelTree a -> [(a, Int, Int)]
     listify (LLEAF a)= [(a, 0, 0)]
     listify (LNODE a l r) = a : (listify l ++ listify r)

{- (c) isBalanced - 10% -}
     isBalanced :: LevelTree a -> Bool
     isBalanced (LLEAF a) = True
     isBalanced (LNODE (a, l1, r1) l2 r2) | (not (isBalanced l2)) || (not (isBalanced r2)) = False
                                           | (max l1 r1 - min l1 r1) > 1 = False
                                           | otherwise = True

{-Testing your tree functions - 4%-}
-- include your tree examples in the test file. 

