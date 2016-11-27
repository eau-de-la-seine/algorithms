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


    #include "generic_linked_list.h"
    #include <stdio.h> // for printf
    
    int main(void) {
        List list = List_make();
        int i1 = 123, i2 = 456, i3 = 789, i4 = 321, i5 = 654, i6 = 987;
    
        // add + get
        list.add(&list, &i1);
        list.add(&list, &i2);
        list.add(&list, &i3);
        printf("%d\n", *(int*) list.get(&list, 0));
        printf("%d\n", *(int*) list.get(&list, 1));
        printf("%d\n", *(int*) list.get(&list, 2));
    
        // update + get
        list.update(&list, 0, &i4);
        list.update(&list, 1, &i5);
        list.update(&list, 2, &i6);
        printf("%d\n", *(int*) list.get(&list, 0));
        printf("%d\n", *(int*) list.get(&list, 1));
        printf("%d\n", *(int*) list.get(&list, 2));
	
        // remove + size
        list.remove(&list, 3); // tried with 0, 1, 2, 3
        printf("%d\n", list.size(&list));
    
        // removeAll + size
        list.removeAll(&list);
        printf("%d\n", list.size(&list));
        
        // Iterator
        printf("\n\nIterate: \n");
        list.add(&list, &i1);
        list.add(&list, &i2);
        list.add(&list, &i3);
	
        // Iterator loop pattern
        for (Iterator* it = list.iterator(&list); it != NULL; it = it->next(it)) {
            printf("%d\n", *(int*) it->get(it));
        }

        // Iterator loop with remove pattern
        Iterator* ite = list.iterator(&list);
        while (ite != NULL) {
            int* element = (int*) ite->get(ite);
            // You can free() element if you have instanciated it with malloc()
            if (*element == 456) {
                ite = ite->removeAndNext(ite);
            } else {
                ite = ite->next(ite);
            }
        }
    
        printf("\n");
        for (Iterator* it = list.iterator(&list); it != NULL; it = it->next(it)) {
            printf("%d\n", *(int*) it->get(it));
        }
    
        return 0;
    }

