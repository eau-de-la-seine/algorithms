#ifndef GENERIC_LINKED_LIST_H
#define GENERIC_LINKED_LIST_H

/* For size_t */
#include <stddef.h>


/**
 * An iterator represents a container which has the element and a pointer on the next container
 *
 * @author Gokan EKINCI 
 */
typedef struct Iterator Iterator;


/**
 * Generic Linked List with an "object oriented" pattern
 * 
 * @author Gokan EKINCI
 */
typedef struct List List;

 

struct Iterator {
	void* _element;
	Iterator* _nextIterator;
	Iterator* _previousIterator;
	
	/**
	 * Useful for updating list size when iterator removed
	 */
	List* _parentList;
	
	/**
	 * Methods
	 */
	int (*hasNext) (Iterator* iterator);
	void* (*get) (Iterator* iterator);
	Iterator* (*next) (Iterator* iterator);
	Iterator* (*removeAndNext) (Iterator* iterator);
};



struct List {
	/**
	 * Number of elements in the list, 0 if the list is empty
	 */
	size_t _nb;
	
	/**
	 * First element in the list, useful for browsing elements from there
	 */
	Iterator* _firstIterator;
	
	/**
	 * Last element in the list, useful for adding elements from there (and don't looping from the first element)
	 */
	Iterator* _lastIterator;
	
	/*
	 * Methods, see {@link List_make()} for function pointer refences
	 */
	size_t (*size) (List* list);
	void* (*get) (List* list, unsigned int index);
	int (*add) (List* list, void *element);
	int (*update) (List* list, unsigned int index, void *element);
	void* (*remove) (List* list, unsigned int index);
	void (*removeAll) (List* list);
	void (*removeAndFreeAll) (List* list);
	Iterator* (*iterator) (List* list);
};

/**
 * If there's next element
 *
 * @param iterator		Current iterator
 * @return 				1 if there's next element, 0 otherwise
 */
int Iterator_has_next(Iterator* iterator);


/**
 * Return element inside the iterator
 *
 * @param iterator		Current iterator
 * @return 				element
 */
void* Iterator_get(Iterator* iterator);


/**
 * Return next iterator
 * 
 * @param iterator		Current iterator
 * @return 				next iterator, NULL if it has not next iterator
 */
Iterator* Iterator_next(Iterator* iterator);


/**
 * Remove current element and attach previous container to the next, then return next iterator
 * /!\ : It does not free() element !
 *
 * @param iterator		Current iterator
 * @return				next iterator, NULL if it has not next iterator
 */
Iterator* Iterator_remove_and_next(Iterator* iterator);


/**
 * Make a new list
 * This implementation is not threadsafe
 *
 * @return 			The new list
 */
List List_make();


/**
 * List's size (number of elements in the list)
 *
 * @param list		Current list
 * @return 			List's size
 */
size_t List_size(List* list);


/**
 * Get element in the list by given index
 *
 * @param list		Current list
 * @param index		Index of the element we are looking for
 * @return 			NULL if could not get element, object otherwise
 */
void* List_get_element(List* list, unsigned int index);


/**
 * Add a new element to the list
 *
 * @param list		Current list
 * @param element	The element to add
 * @return 			0 if could not add element, 1 otherwise
 */
int List_add_element(List* list, void *element);


/**
 * Update element in the list by given index
 * The old referenced element will be overwritten
 *
 * @param list		Current list
 * @param index		Index of the element
 * @param element	The element which will overwrite the old one
 * @return 			0 if could not update element, 1 otherwise
 */
int List_update_element(List* list, unsigned int index, void *element);


/**
 * Remove element in the list by given index
 * This function does not free() element, developer can use free() on return value
 * 
 * @param list		Current list
 * @param index		Index of the element
 * @return 			NULL if could not delete element, object otherwise
 */
void* List_remove_element(List* list, unsigned int index);


/**
 * Remove all list elements (iterators) in the list, but does not free() the elements
 *
 * @param list		Current list
 */
void List_remove_all(List* list);


/**
 * Remove all list elements (iterators) in the list, and also free() the elements
 *
 * @param list		Current list
 */
void List_remove_and_free_all(List* list);


/**
 * Return iterator on the first element
 *
 * @return 			iterator on the first element. Result maybe NULL if there's no element in the list
 */
Iterator* List_iterator(List* list);

#endif
