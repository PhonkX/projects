nextLine strList = do
    s <- getLine
    if null s then return (reverse strList)
    else
        nextLine (s : strList)


main = do
    n <- nextLine []
    print n