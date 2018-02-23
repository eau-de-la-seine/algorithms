Some functions and libraries I have created myself during my studies

* Sort functions
    * `bubble_sort` (on interger arrays)
	
* Sequence functions
    * `factorial` (with and without recursion version)
    * `fibonacci` (recursion version)

* Algebra functions
    * power

* Libraries
    * Generic Linked List
	

### Bubble sort
  
    // INCLUDE bubble_sort.c
    #include <stdio.h>

    int main(){
        int tab[] = {6, 0, 3, 5, 1, 4, 2};
	    int tabSize = 7;
        bubble_sort(&tab[0], tabSize - 1);
	
	    int i = 0;
        for(; i < tabSize; i++) {
		    printf("%d ", tab[i]);
	    }
	
        return 0;
    }


### Generic Linked List


    #include "../generic_linked_list.h"
    #include <stdio.h>
    #include <stdlib.h>

    int main(void) {
        List list = List_LinkedList();
        int i1 = 123, i2 = 456, i3 = 789, i4 = 321, i5 = 654, i6 = 987;
        Iterator ite;

        printf("\nadd + get:\n");
        list.add(&list, &i1);
        list.add(&list, &i2);
        list.add(&list, &i3);
        printf("    %d\n", *(int*) list.get(&list, 0));
        printf("    %d\n", *(int*) list.get(&list, 1));
        printf("    %d\n", *(int*) list.get(&list, 2));

        printf("\nupdate + get:\n");
        list.update(&list, 0, &i4);
        list.update(&list, 1, &i5);
        list.update(&list, 2, &i6);
        printf("    %d\n", *(int*) list.get(&list, 0));
        printf("    %d\n", *(int*) list.get(&list, 1));
        printf("    %d\n", *(int*) list.get(&list, 2));

        printf("\nremove + size:\n");
        /* tried with 0, 1, 2, 3 | Should not remove with 3 */
        printf("    Size before remove: %lu\n", list.size(&list));
        list.remove(&list, 0);
        printf("    Size after  remove: %lu\n", list.size(&list));

        printf("\nremoveAll + size:\n");
        list.removeAll(&list);
        printf("    %lu\n", list.size(&list));
        

        printf("\nIterate loop pattern: \n");
        list.add(&list, &i1);
        list.add(&list, &i2);
        list.add(&list, &i3);

        ite = list.iterator(&list);
        while (ite.hasNext(&ite)) {
            printf("    %d\n", *(int*) ite.next(&ite));
        }


        printf("\nIterator loop with remove pattern (remove 456): \n");
        ite = list.iterator(&list);
        while (ite.hasNext(&ite)) {
            int* element = (int*) ite.next(&ite);
            /* You can free() element if you have instanciated it with malloc() */
            if (*element == 456) {
                ite.remove(&ite);
            }
        }

        ite = list.iterator(&list);
        while (ite.hasNext(&ite)) {
            printf("    %d\n", *(int*) ite.next(&ite));
        }
        printf("    Size after  remove: %lu\n", list.size(&list));


        printf("\nIterator loop with remove pattern (remove 123): \n");
        ite = list.iterator(&list);
        while (ite.hasNext(&ite)) {
            int* element = (int*) ite.next(&ite);
            /* You can free() element if you have instanciated it with malloc() */
            if (*element == 123) {
                ite.remove(&ite);
            }
        }

        ite = list.iterator(&list);
        while (ite.hasNext(&ite)) {
            printf("    %d\n", *(int*) ite.next(&ite));
        }
        printf("    Size after  remove: %lu\n", list.size(&list));


        printf("\nIterator loop with remove pattern (remove 789): \n");
        ite = list.iterator(&list);
        while (ite.hasNext(&ite)) {
            int* element = (int*) ite.next(&ite);
            /* You can free() element if you have instanciated it with malloc() */
            if (*element == 789) {
                ite.remove(&ite);
            }
        }

        ite = list.iterator(&list);
        while (ite.hasNext(&ite)) {
            printf("    %d\n", *(int*) ite.next(&ite));
        }
        printf("    Size after  remove: %lu\n", list.size(&list));


        printf("\nadding one element (&i1) and loop:\n");
        list.add(&list, &i1);
        ite = list.iterator(&list);
        while (ite.hasNext(&ite)) {
            printf("    %d\n", *(int*) ite.next(&ite));
        }
        printf("    Size after add: %lu\n", list.size(&list));
        printf("    Iterator loop with remove pattern (remove &i1): \n");
        ite = list.iterator(&list);
        while (ite.hasNext(&ite)) {
            int* element = (int*) ite.next(&ite);
            /* You can free() element if you have instanciated it with malloc() */
            if (element == &i1) {
                ite.remove(&ite);
            }
        }
        printf("    Size after  remove: %lu\n", list.size(&list));


        printf("\nadding one element (&i2) and loop:\n");
        list.add(&list, &i2);
        ite = list.iterator(&list);
        while (ite.hasNext(&ite)) {
            printf("    %d\n", *(int*) ite.next(&ite));
        }
        printf("    Size after add: %lu\n", list.size(&list));
        printf("    Iterator loop with remove pattern (remove &i2): \n");
        ite = list.iterator(&list);
        while (ite.hasNext(&ite)) {
            int* element = (int*) ite.next(&ite);
            /* You can free() element if you have instanciated it with malloc() */
            if (element == &i2) {
                ite.remove(&ite);
            }
        }
        printf("    Size after  remove: %lu\n", list.size(&list));

        /* Free all allocated memory before quit */
        /* list.removeAll(&list); */
        return 0;
    }


Compiled with:

    gcc -Wall -Wextra -ansi -pedantic -fsanitize=leak -fno-omit-frame-pointer ../generic_linked_list.c main.c -o list

