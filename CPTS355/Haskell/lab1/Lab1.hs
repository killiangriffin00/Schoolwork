-- CptS 355 - Lab 1 (Haskell) - Spring 2021
-- Name: 
-- Collaborated with: 

module Lab1     
    where

-- 1.insert

insert n item [] | (n == 0) = item : []
                 | otherwise = []
insert n item (x:xs) | n > 0 = x : (insert (n-1) item xs)
                     | n == 0 = item : x : xs

-- 2. insertEvery

insertEvery n item [] = []
insertEvery n item iL = helper (n-1) n item iL
                        where
                            helper n ni item [] = []
                            helper n ni item (x:xs) | n > 0 = x : (helper (n-1) ni item xs)
                                                    | otherwise = x : (helper ni ni item (item : xs))
                     


-- 3. getSales


-- 4. sumSales


-- 5. split


-- 6. nSplit

