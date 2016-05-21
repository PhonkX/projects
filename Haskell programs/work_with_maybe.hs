getPos :: Eq a => [a] -> a -> Maybe Int
getPos list el = getPos1 list el 0
    where
        getPos1 [] _ _ = Nothing
        getPos1 (x:xs) el k = if x == el then Just k else getPos1 xs el (k + 1)   

main = do
    number <- getLine
    let n = getPos [1, 2, 3] (read number)
    case n of
        Just k -> putStrLn $ "Found at " ++ (show k)
        Nothing -> putStrLn "Not Found"