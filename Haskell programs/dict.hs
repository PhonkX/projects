import Data.List
import Data.Char
import qualified Data.Set as Set
import System.Environment
import System.Exit
import qualified Control.Exception as Ex

addWords :: Set.Set String -> String -> Set.Set String
addWords dic line = let
    xs = words line 
    ys = map (\w -> filter isLetter w) xs
    dic1 = Set.fromList ys 
  in Set.union dic dic1

checkArgs :: [String] -> IO [String]
checkArgs xs = 
    if length xs == 2 then return xs
    else do
           {- putStrLn "Usage: dict [input_file] [output_file]"
            exitFailure-}
            die "Usage: dict [input_file] [output_file]"

safeReadFile fn = do
    Ex.catch (do {s <- readFile fn; return s}) handler
    where
        handler :: Ex.SomeException -> IO String
        handler e = do
            putStrLn $ show e
            exitFailure

safeWriteFile fn ss = do
    Ex.catch (do {writeFile fn ss}) handler
    where
        handler :: Ex.SomeException -> IO ()
        handler e = do
            putStrLn $ show e
            exitFailure

main = do  
    xs <- getArgs
    [fin, fout] <- checkArgs xs 
    s <- safeReadFile fin
    let ss = lines s
    let ts = Set.toList $ foldl addWords Set.empty ss
  {-  let ws = foldl (++) [] (map words ss)
    let zs = map (\w -> filter isLetter w) ws --лямбда-функция
    let ts = sort $ nub $ zs-}
    let ks = map (filter isLetter) ts
    safeWriteFile fout $ unlines ts