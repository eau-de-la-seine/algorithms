/** 
 * Power function
 *
 * Wikipedia: https://en.wikipedia.org/wiki/Exponentiation
 * 
 * Example :
 * 		2^3 = 2 x 2 x 2 = 8
 * 		power(2, 3) = 8
 *
 *
 * @param number
 * @param pow
 * @return 			the `pow`-th power of `number`
 * 
 * @author Gokan EKINCI
 */
int power(int number, int pow) {
    int j = 1;
	for(int i = 0; i < pow; i++){
	    j = j * number;
    }

    return j;
}
	