import Control.Concurrent
import Control.Concurrent.MVar

{-writer m k = do
    n <- takeMVar m
    print k
    putMVar m n
    --threadDelay 1000
    if k == 1100 then return ()
    else writer m (k + 1)

main = do
    m <- newMVar ()
    forkIO (writer m 1000)
    forkIO (writer m 1000)
    threadDelay 5000000-}

writer m n k last = do
    --k <- takeMVar m
    if k == last then return()
    else do
        putMVar m (k + 1)
        --putStrLn $ "Put " ++ (show (k+1))
        showMessage n $ "Put " ++ (show (k+1))
        writer m n (k + 1) last

reader m n last = do
    k <- takeMVar m
    --putStrLn $ "Read " ++ (show k)
    showMessage n $ "Read " ++ (show k)
    if k == last then return()
    else reader m n last

showMessage :: MVar () -> String -> IO()
showMessage m s = do 
    takeMVar m 
    putStrLn s
    putMVar m ()

main = do 
    m <- newEmptyMVar
    n <- newMVar ()
    forkIO (writer m n 0 1000)
    forkIO (reader m n 1000)
    threadDelay 5000000
