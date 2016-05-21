data Day = Mon | Tue | Wed | Thu | Fri | Sat | Sun
	deriving (Eq, Ord, Bounded, Read, Show)
fromEnum' :: Day -> Int
fromEnum' d = case d of
    Mon -> 0
    Tue -> 1
    Wed -> 2
    Thu -> 3
    Fri -> 4
    Sat -> 5
    Sun -> 6
toEnum' :: Int -> Day
toEnum' n = case (mod n 7) of
    0 -> Mon
    1 -> Tue
    2 -> Wed
    3 -> Thu
    4 -> Fri
    5 -> Sat
    6 -> Sun
succ' :: Day -> Day
--succ' d = toEnum (fromEnum d + 1)
succ' d = toEnum' $ succ $ fromEnum' d
pred' :: Day -> Day
--pred' d = toEnum (fromEnum d - 1)
pred' d = toEnum' $ pred $ fromEnum' d

instance Enum Day where
    fromEnum = fromEnum'
    toEnum = toEnum'
    succ = succ'
    pred = pred'
weekend :: Day -> Bool
weekend d = (fromEnum d) >= 5

data Rect = MkRect Double Double --ширина; высота
    deriving (Eq)
area :: Rect -> Double
area (MkRect x y) = x * y
isSquare :: Rect -> Bool
isSquare (MkRect x y) = x == y
getArea x y =
    let r = MkRect x y
    in area r
instance Show Rect where
    show (MkRect x y) = (show x) ++ "x" ++ (show y)
data Rect' a = MkRect' {width, height :: a} deriving Eq
area' :: Num a => Rect' a -> a
area' r = (width r) * (height r)
instance Show a=>Show (Rect' a) where
    show r = show (width r) ++ "x" ++ show (height r)







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