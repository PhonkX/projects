import Control.Concurrent
import Control.Concurrent.MVar
import Control.Concurrent.STM
import Control.Monad
import System.Random

type Fork = TMVar Int

newFork i = newTMVarIO i
takeFork f = takeTMVar f
releaseFork f i = putTMVar f i

randomDelay n = do
    d <- randomRIO (1, n)
    threadDelay (d * 1000000)

showMessage :: MVar () -> String -> IO()
showMessage m s = do 
    takeMVar m 
    putStrLn s
    putMVar m ()

philosopher :: String -> (Fork, Fork) -> MVar () -> IO ()
philosopher name (left, right) m = forever $ do
    showMessage m (name ++ " is hungry")
    (l, r) <- atomically $ do
        l <- takeFork left
        r <- takeFork right
        return (l, r)
    showMessage m (name ++ " got forks " ++ (show l) ++ " and " ++ (show r))
    randomDelay 2
    atomically $ do
        releaseFork left l
        releaseFork right r
    showMessage m (name ++ " is thinking")
    randomDelay 3

main = do
    m <- newMVar ()
    forks <- mapM newFork [1..5]
    let ph = map philosopher ["Socrat", "Plato", "Cartesius", "Aristotel", "Kant"]
    let forkPairs = zip forks (tail.cycle $ forks)
    let ph1 = zipWith ($) ph forkPairs
    threads <- mapM forkIO (zipWith ($) ph1 $ repeat m) 
    getLine
    mapM_ killThread threads