-- CptS 355 - Spring 2021 
-- Homework1 - Haskell
-- Name: Killian Griffin
-- Collaborators: 

module HW1     
    where


-- Q1(a) getUniqueRight
    getUniqueRight :: Eq a => [a] -> [a]
    getUniqueRight [] = []
    getUniqueRight (x : xs) | elem x xs = getUniqueRight xs
                            | otherwise = x : getUniqueRight xs


-- Q1(b) getUniqueLeft
    getUniqueLeft :: Eq a => [a] -> [a]
    getUniqueLeft [] = []
    getUniqueLeft a = helper a []
                        where helper [] y = []
                              helper (x : xs) y | elem x y = helper xs y
                                                | otherwise = x : helper xs (x : y) 


-- Q2(a) cansInLog
    cansInLog :: Num p => [(a, p)] -> p
    cansInLog [] = 0
    cansInLog ((a, p) : xs) = p + cansInLog xs 


-- Q2(b) numCans
    numCans :: (Num p, Eq t) => [((a1, t), [(a2, p)])] -> t -> p
    numCans [] y = 0
    numCans (((a1, t), list) : xs) y | y == t = cansInLog list + numCans xs y
                                     | otherwise = numCans xs y



-- Q2(c) getMonths
    getMonths :: (Ord t1, Eq t2, Num t1) => [((a, b), [(t2, t1)])] -> t1 -> t2 -> [(a, b)]
    getMonths [] x y = []
    getMonths ((month, list) : xs1) x y | exceedCans list x y 0 = month : getMonths xs1 x y 
                                        | otherwise = getMonths xs1 x y
                                            where 
                                                exceedCans [] n m o | o > n = True
                                                                    | otherwise = False
                                                exceedCans ((x, y) : xs2) n m o | x == m = exceedCans xs2 n m (o + y)
                                                                                | otherwise = exceedCans xs2 n m o


-- Q3 deepCount
    deepCount :: (Num p, Eq t) => t -> [[t]] -> p
    deepCount x [] = 0
    deepCount x (y : xs) = count x y + deepCount x xs
                             where count x2 [] = 0 
                                   count x2 (y2 : xs2) | x2 == y2 = 1 + count x2 xs2
                                                       | otherwise = count x2 xs2


-- Q4 clusterConsecutive
    clusterConsecutive :: (Eq a, Num a) => [a] -> [[a]]
    clusterConsecutive [] = []
    clusterConsecutive (x1:xs1) = helper xs1 x1 (x1:[])
                            where helper [] y b = [reverse b] 
                                  helper (x:xs) y b | y + 1 == x = helper xs (y + 1) (x : b)
                                                    | otherwise = (reverse b) : helper xs x (x : [])  


