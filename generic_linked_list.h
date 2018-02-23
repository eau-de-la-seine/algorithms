#ifndef GENERIC_LINKED_LIST_H
#define GENERIC_LINKED_LIST_H

/* For size_t */
#include <stddef.h>



/**
 * A List interface with an "object oriented" pattern
 * 
 * @author Gokan EKINCI
 */
typedef struct List List;



/**
 * An iterator represents a cursor on the current container
 *
 * @author Gokan EKINCI 
 */
typedef struct Iterator Iterator;



/**
 * A container has the element and a pointer on the next container
 * 
 * @author Gokan EKINCI
 */
typedef struct LinkedContainer LinkedContainer;



struct LinkedContainer {
	void* _element;
	LinkedContainer* _nextContainer;
	LinkedContainer* _previousContainer;
};



struct Iterator {
	/**
	 * Reprensents the cursor on the current element
	 */
	LinkedContainer* _container;

	/**
	 * Reprensents the cursor on the previous element which is mostly required for the last element in the list
	 */
	LinkedContainer* _containerToRemove;


	/**
	 * Useful for updating list size when container is removed, and also reset the first container in the list if the removed element was at index 0
	 */
	List* _parentList;


	/**
	* If there's next element
	*
	* @param iterator		This iterator
	* @return 				1 if there's next element, 0 otherwise
	*/
	int (*hasNext) (Iterator* iterator);


	/**
	* Return next iterator
	* 
	* @param iterator		This iterator
	* @return 				Element in the current container
	*/
	void* (*next) (Iterator* iterator);


	/**
	* Remove the current container and attach previous container to the next
	* /!\ : It does not free() the element !
	* /!\ : Must be executed after next()
	* /!\ : Must not be executed more than once per loop
	*
	* @param iterator		This iterator
	*/
	void (*remove) (Iterator* iterator);
};



struct List {
	/**
	 * Number of elements in the list, 0 if the list is empty
	 */
	size_t _nb;


	/**
	 * First element in the list, useful for browsing elements from there
	 */
	LinkedContainer* _firstContainer;


	/**
	 * Last element in the list, useful for adding elements from there (and don't looping from the first element)
	 */
	LinkedContainer* _lastContainer;


	/**
	* List's size (number of elements in the list)
	*
	* @param list		This list
	* @return 			List's size
	*/
	size_t (*size) (List* list);


	/**
	* Get element in the list by given index
	*
	* @param list		This list
	* @param index		Index of the element we are looking for
	* @return 			NULL if could not get element, object otherwise
	*/
	void* (*get) (List* list, unsigned int index);


	/**
	* Add a new element to the list
	*
	* @param list		This list
	* @param element	The element to add
	* @return 			0 if could not add element, 1 otherwise
	*/
	int (*add) (List* list, void *element);


	/**
	* Update element in the list by given index
	* The old referenced element will be overwritten
	*
	* @param list		This list
	* @param index		Index of the element
	* @param element	The element which will overwrite the old one
	* @return 			0 if could not update element, 1 otherwise
	*/
	int (*update) (List* list, unsigned int index, void *element);


	/**
	* Remove element in the list by given index
	* This function does not free() element, developer can use free() on return value
	* 
	* @param list		This list
	* @param index		Index of the element
	* @return 			NULL if could not delete element, object otherwise
	*/
	void* (*remove) (List* list, unsigned int index);


	/**
	* Remove all list elements (containers) in the list, but does not free() the elements
	*
	* @param list		This list
	*/
	void (*removeAll) (List* list);


	/**
	* Remove all list elements (containers) in the list, and also free() the elements
	*
	* @param list						This list
	* @param freeElementCallback		Optional callback is executed before `free()` on the element. Use NULL if you don't have a callback.
	*/
	void (*removeAndFreeAll) (List* list, void (*freeElementCallback)(void* element));


	/**
	* Return iterator on the first container in the list
	*
	* @param list		This list
	* @return 			iterator on the first element. Result maybe NULL if there's no element in the list
	*/
	Iterator (*iterator) (List* list);
};




/**
 * Make a new linked list
 * This implementation is not threadsafe
 *
 * @return 			The new linked list
 */
List List_LinkedList();


#endif
