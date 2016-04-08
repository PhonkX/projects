dot xs ys = sum $ zipWith (*) xs ys

fibbs = 1:1:zipWith (+) fibbs (tail fibbs)
fibb n = fibbs !! n

maxstr :: [String] -> String
maxstr [] = ""
--maxstr xs = filter p xs
--        where p x xs = (length x == maximum (map length xs))
maxstr xs = let
    y = maximum $ map length xs
    p s = length s == y
  in head $ filter p xs

maxstr' :: [String] -> String
maxstr' [] = ""

maxstr' xs = let
        ys = zip xs (map length xs)
        max2 (s1, n1) (s2, n2) = if n1 < n2 then (s2, n2) else (s1, n1)
    in fst $ foldl max2 (head ys) (tail ys)

maxstrrec :: [String] -> String
maxstrrec [] = ""
maxstrrec [x] = x
maxstrrec (x:xs) = let
        y = maxstrrec xs
    in if length x > length y then x else y

sieve (x: xs) = x : sieve [y | y <- xs, y `mod` x /= 0 ]
primes :: [Integer]
primes = sieve [2..]

divisors :: Int -> [Integer]
divisors n = div2 (toInteger n) [] primes
--div2 :: Int -> [Int] -> [Integer]
div2 1 ds _ = reverse ds
div2 n ds (p:ps) = if n `mod` p == 0 then div2 (n `div` p) (p:ds) (p:ps) else div2 n ds ps 