/**
 * Bubble sort (tri à bulle)
 *
 * Wikipedia: https://en.wikipedia.org/wiki/Bubble_sort
 * 
 * Detailed steps:
		6 0 3 5 1 4 2   // We compare 6 and 0 : we reverse
		0 6 3 5 1 4 2   // We compare 6 and 3 : we reverse
		0 3 6 5 1 4 2   // We compare 6 and 5 : we reverse
		0 3 5 6 1 4 2   // We compare 6 and 1 : we reverse
		0 3 5 1 6 4 2   // We compare 6 and 4 : we reverse
		0 3 5 1 4 6 2   // We compare 6 and 2 : we reverse
		0 3 5 1 4 2 6   // We have finished the first loop, the last element is 6, no more need to come back to tab[6]
		0 3 5 1 4 2 6   // We compare 0 and 3 : we let
		0 3 5 1 4 2 6   // We compare 3 and 5 : we let
		0 3 5 1 4 2 6   // We compare 5 and 1 : we reverse
		0 3 1 5 4 2 6   // We compare 5 and 4 : we reverse
		0 3 1 4 5 2 6   // We compare 5 and 2 : we reverse
		0 3 1 4 2 5 6   // We have finished the second loop, the last-1 element is 5, no more need to come back to tab[5]
		0 3 1 4 2 5 6   // We compare 0 and 3 : we let
		0 3 1 4 2 5 6   // We compare 3 and 1 : we reverse
		0 1 3 4 2 5 6   // We compare 3 and 4 : we let
		0 1 3 4 2 5 6   // We compare 4 and 2 : we reverse
		0 1 3 2 4 5 6   // We have finished the third  loop, the last-2 element is 4, no more need to come back to tab[4]
		0 1 3 2 4 5 6   // We compare 0 and 1 : we let
		0 1 3 2 4 5 6   // We compare 1 and 3 : we let
		0 1 3 2 4 5 6   // We compare 3 and 2 : we reverse
		0 1 2 3 4 5 6   // We have finished the fourth loop, the last-3 element is 3, no more need to come back to tab[3]
		0 1 2 3 4 5 6   // We compare 0 and 1 : we let
		0 1 2 3 4 5 6   // We compare 1 and 2 : we let
		0 1 2 3 4 5 6   // We have finished the fifth  loop, the last-4 element is 2, no more need to come back to tab[2]
		0 1 2 3 4 5 6   // We compare 0 and 1 : we let
		0 1 2 3 4 5 6   // We have finished the sixth  loop, the last-5 element is 1, no more need to come back to tab[1]
		
 * 
 * @param tab[]			An array of interger elements to sort
 * @param lastIndex		Last index of array
 *
 * @author Gokan EKINCI
 */
void bubble_sort(int tab[], int lastIndex) {
	int ordered = 0, temp, i;
	while (!ordered) {
		for (i = 0; i < lastIndex; i++) {
			// swap
			if (tab[i] > tab[i+1]) {
				temp = tab[i];
				tab[i] = tab[i+1];
				tab[i+1] = temp;
			}
		}

		--lastIndex;

		if (lastIndex == 1) {
			ordered = 1;
		}
	}
}
