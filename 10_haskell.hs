import System.Environment

main :: IO ()
main = do
	n <- fmap head getArgs 
	putStrLn $ show $ sum $ primes (read n :: Int)

primes :: Int -> [Int]
primes n = sieve [2..n] n
	where 
		sieve [] n = []
		sieve (p:xs) n
			| p > (ceiling $ sqrt $ fromIntegral n ::Int) = (p:xs) 
			| isPrime p == True = p : sieve [x | x <- xs, x `rem` p /= 0] n
			| otherwise = sieve xs n

isPrime p = null . filter (==0) $ map (rem p) [2..(p - 1)] 
	
