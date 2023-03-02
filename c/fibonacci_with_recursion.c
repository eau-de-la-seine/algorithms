/** 
 * Fibonacci function with recursion
 *
 * Wikipedia: https://en.wikipedia.org/wiki/Fibonacci_number
 *
 * Example:
	f(0) = 0
    f(1) = 1
	f(2) = 1
	f(3) = 2
	f(4) = 3
	f(5) = 5
	f(6) = 8
	f(7) = 13
	f(8) = 21
	...
 * 
 * @param n
 * @return 		fibonacci of n
 *
 * @author Gokan EKINCI
 */
unsigned int fibonacci(unsigned int n) {
	if (n <= 1) {
		return n;
	}

	return fibonacci(n-1) + fibonacci(n-2);
} 
