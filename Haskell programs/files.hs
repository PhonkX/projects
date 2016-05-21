main = do
    s<-readFile "in.txt"
    let ss = lines s
   -- let l = length s
    let n = length ss
    let l = sum $ map length ss
    putStrLn (show(n) ++ "         " ++ show(l))
   -- putStrLn (show(n) ++ "        " ++ show(l-n+1))
   -- writeFile "out.txt" $ unlines ts