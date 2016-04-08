add :: Int -> Int -> Int
add x y = x + y

max' :: Int -> Int -> Int
max' x y = if x > y then x else y

sign' :: Int -> Int
sign' x
    | x < 0 = (-1)
    | x > 0 = 1
    | otherwise = 0

fact :: Int -> Integer
fact 0 = 1
fact n
    | n < 0 = error "bad arg"
    | otherwise = (toInteger n) * (fact (n-1) )

fibb :: Int -> Integer
fibb 0 = 1
fibb 1 = 1
fibb n
    | n < 0 = error "bad arg"
    | otherwise = (fibb (n-2)) + (fibb (n-1))

roots :: Double -> Double -> Double -> (Double, Double)
roots a b c = let
    d = b * b - 4.0 * a * c
    sd = sqrt d
    a2 = 1.0 / (2.0 * a)
    x1 = ((-b) + sd) * a2
    x2 = ((-b) - sd) * a2
  in if d < 0 then error "no real roots" else (x1, x2)

roots' a b c = if d < 0 then error "no real roots" else (x1, x2)
    where
        d = b * b - 4.0 * a * c
        sd = sqrt d
        a2 = 1.0 / (2.0 * a)
        x1 = ((-b) + sd) * a2
        x2 = ((-b) - sd) * a2 

isEven :: Int -> String
isEven x = case mod x 2 == 0 of
    True -> "true"
    False -> "false"

triples :: Int -> [(Int, Int, Int)]
triples n = [ (a, b, c) | a <- [1..n], b <- [a..n], c <- [b..n], a*a + b*b == c*c]

len :: [ a ] -> Int
len [] = 0
len (x : xs) = 1 + len xs

len' :: [ a ] -> Int
len' xs = len'' xs 0
    where
        len'' [] n = n
        len'' (x : xs) n = len'' xs (n+1)

elem' :: Eq a => a -> [ a ] -> Bool
elem' _ [] = False
elem' y (x: xs) = if y == x then True else elem' y xs

minim :: [Int] -> Int
minim [] = error "Empty list"
minim [x] = x 
minim (x: xs) = min x (minim xs)

sieve (x: xs) = x : sieve [y | y <- xs, y `mod` x /= 0 ]
primes :: [Integer]
primes = sieve [2..]

qsort :: [Int] -> [Int]
qsort [] = []
qsort (x:xs) = qsort [y | y <- xs, y < x] ++ (x : qsort [y | y <- xs, y >= x])