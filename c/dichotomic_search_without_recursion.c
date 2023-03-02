/**
 * Using the dichotomic search
 * 
 *
 * @param array         An array with integer elements, must be sorted in ascending order
 * @param arrayLength   Length of the array
 * @param elem          The element of the index we are looking for
 * @return              Index of the array if "elem" matches with an element, -1 if no element found
 *
 * @author Gokan EKINCI
 */
int indexOf(int array[], int arrayLength, int elem) {
	int start = 0;
	int last = arrayLength - 1;

	while (start <= last) {
		int index = (start + last) / 2;
		if (array[index] < elem) start = index + 1;
		else if (array[index] > elem) last = index - 1;
		else return index;
	}

	return -1;
}
