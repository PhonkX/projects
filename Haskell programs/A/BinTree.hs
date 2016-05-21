module A.BinTree where

data BinTree a = Leaf | Node a (BinTree a) (BinTree a)
    deriving (Eq)
insTree :: Ord a => BinTree a -> a -> BinTree a
insTree Leaf x = Node x Leaf Leaf
insTree tr@(Node y l r) x = case compare x y of
        LT -> Node y (insTree l x) r
        GT -> Node y l (insTree r x)
        EQ -> tr

listToTree :: Ord a => [a] -> BinTree a
listToTree xs = foldl insTree Leaf xs

treeToList :: Ord a => BinTree a -> [a]
treeToList Leaf = []
treeToList (Node x l r) = (treeToList l) ++ [x] ++ (treeToList r)

treeSort :: Ord a => [a] -> [a]
treeSort = treeToList . listToTree 

elemTree :: Ord a => BinTree a -> a -> Bool
elemTree Leaf x = False
elemTree (Node y l r) x = case (compare x y) of
        LT -> elemTree l x
        GT -> elemTree r x
        EQ -> True

sizeTree :: Ord a => BinTree a -> Int
sizeTree Leaf = 0
sizeTree (Node x l r) = (sizeTree l) + (sizeTree r) + 1

heightTree :: Ord a => BinTree a -> Int
heightTree Leaf = 0
heightTree (Node x l r) = (max (heightTree l) (heightTree r)) + 1

instance Show a => Show (BinTree a) where
    show t = show' t 0 where
        show' Leaf _ = "\n"
        show' (Node x l r) k = 
                show' l (k+2) ++ (replicate k ' ') ++ (show x) ++ show' r (k+2)