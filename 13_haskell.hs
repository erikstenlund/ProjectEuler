import System.Environment

-- Takes file containing the numbers as argument.
main = do
    [fileName] <- getArgs
    numbers <- readFile fileName
    putStrLn . take 10 . show . sum . map parseInteger $ lines numbers

parseInteger :: String -> Integer
parseInteger = read . filter (/='\n')
