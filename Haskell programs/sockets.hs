import Network
import System.IO
import Control.Concurrent
import Control.Concurrent.MVar
import Control.Monad
import System.Directory
import Data.Char

main = withSocketsDo $ do
    sock <- listenOn $ PortNumber 8080
    loop sock
    sClose sock

loop sock = do
    (h, n, p) <- accept sock
    hSetBuffering h LineBuffering
    forkIO $ handle (h, n, p)
    loop sock

handle (h, n, p) = do
    s <- hGetLine h
    putStrLn $ (n ++ ": " ++ s)
    let (cmd, arg1) = span (not.isSpace) s
    let arg = dropWhile isSpace arg1
    case cmd of
        "quit" -> hClose h
        "list" -> do
                    files <- listCommand
                    transferData h files $ length files
                    handle (h, n, p)
        "get" -> do
                    fileExistance <- doesFileExist $ "./Data/" ++ arg
                    if fileExistance
                    then do
                        file <- getFile $ "./Data/" ++ arg
                        let f = lines file
                        transferData h f $ length(f)
                    else do
                        transferData h [] (-1)
        _ -> handle (h, n, p)

getFile name = do
    file <- readFile name 
    return file

listCommand = do
    list <- getDirectoryContents "./Data"
    files <- filterM (\x -> doesFileExist $ "./Data/" ++ x) list 
    mapM_ putStrLn files
    return files

transferData h list len = do
    hPutStrLn h $ show len
    mapM_ (hPutStrLn h) list