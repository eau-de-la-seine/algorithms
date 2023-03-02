/** 
 * Factorial function without recursion
 *
 * Wikipedia: https://en.wikipedia.org/wiki/Factorial
 *
 * Example:
	0! = 1
	1! = 1
	2! = 2 x 1 = 2
	3! = 3 x 2 x 1 = 6
	4! = 4 x 3 x 2 x 1 = 24
	5! = 5 x 4 x 3 x 2 x 1 = 120
	...
 * 
 * @param n
 * @return 		factorial of n
 *
 * @author Gokan EKINCI
 */
unsigned int factorial(unsigned int n) {
	if (n < 2) {
		return 1;
	}

	unsigned int c = n;
	while (c != 1) {
		n *= --c;
	}

	return n;
}
