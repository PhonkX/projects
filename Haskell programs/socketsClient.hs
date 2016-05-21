import Network
import System.IO
import Control.Concurrent
import Control.Concurrent.MVar
import Data.Char
import Control.Monad

main = withSocketsDo $ do
    h <- connectTo "localhost" $ PortNumber 8080
    hSetBuffering h LineBuffering
    handle h

handle h = do
    s <- getLine
    let (cmd, arg1) = span (not.isSpace) s
    let arg = dropWhile isSpace arg1
    hPutStrLn h s
    case cmd of
        "quit" -> hClose h
        "list" -> do 
                    files <- getList h
                    case files of
                        Nothing -> putStrLn "Неверная директория"
                        Just x -> mapM_ putStrLn x
                    handle h
        "get" -> do
                    getFile h arg
                    handle h
        _ -> do
                putStrLn "Неверная команда"
                handle h

getFile h name = do
    file <- getList h
    {-if file == Nothing
    then
        putStrLn "File does not exist"
    else do
        let f = reverse file-}
    case file of
        Nothing -> putStrLn "File does not exist"
        Just f -> writeFile name $ unlines f


getList :: Handle -> IO( Maybe( [String]))
getList h = do 
    n <- hGetLine h
    if read(n) == (-1)
    then
        return Nothing
    else do
        xs <- getFileList1 h [] $ read n
        return $ Just xs

getFileList1 :: Handle -> [String] -> Int -> IO [String]
getFileList1 h list n = do
    if n == 0 then return list
    else do
        s <- hGetLine h
        getFileList1 h (s:list) (n - 1)