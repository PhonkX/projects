import System.Random
guess :: Int ->Int -> IO ()
guess n k= do
    s <- getLine
    let number = read s
    case (compare number n) of
        EQ -> do
                    putStrLn "Win!"
                    putStrLn ("Numbers of try: "++(show k))
                    return ()
        LT -> do
                    putStrLn "Your number is lesser"
                    guess n (k + 1)
        GT -> do
                    putStrLn "Your number is greater"
                    guess n (k + 1)

main = do
        n <- randomRIO (1,10)
        guess n 1
