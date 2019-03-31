#include "generic_linked_list.h"
/* For malloc() and free() */
#include <stdlib.h>



int Iterator_hasNext(Iterator* iterator) {
	return iterator->_container != NULL;
}



void* Iterator_next(Iterator* iterator) {
	void* element = iterator->_container->_element;
	iterator->_containerToRemove = iterator->_container;
	iterator->_container = iterator->_container->_nextContainer;
	return element;
}



void Iterator_remove(Iterator* iterator) {
	/* If current function called once, iterator->_containerToRemove should never be NULL */
	if (iterator->_containerToRemove == NULL) {
		return;
	}

	--iterator->_parentList->_nb;

	if (iterator->_containerToRemove->_previousContainer == NULL) {
		/* Case : Removing the first element (index 0) */

		/* Test if there's an element after the element to remove */
		if (iterator->_container != NULL) {
			iterator->_container->_previousContainer = NULL;
		}

		iterator->_parentList->_firstContainer = iterator->_container;
	} else {
		/* Case : There's element before current element */
		/* Attach previous and next nodes (iterator->_container can be NULL if iterator->_containerToRemove was the last in the list) */
		iterator->_containerToRemove->_previousContainer->_nextContainer = iterator->_container;
	}

	/* Deleting container */
	free(iterator->_containerToRemove);
	iterator->_containerToRemove = NULL;
}



size_t List_size(List* list) {
	return list->_nb;
}



void* List_get(List* list, unsigned int index) {
	LinkedContainer* container = list->_firstContainer;
	unsigned int i = 0;

	/* Checking range */
	if (list->_nb == 0 || index > list->_nb - 1) {
		return NULL;
	}

	for (; i < index; i++) {
		container = container->_nextContainer;
	}

	return container->_element;
}



int List_add(List* list, void* element) {
	LinkedContainer* newContainer = (LinkedContainer*) malloc(sizeof(*newContainer));

	/* If malloc failed */
	if (newContainer == NULL) {
		return 0;
	}

	/* Init container's fields */
	newContainer->_element = element;
	newContainer->_nextContainer = NULL;
	newContainer->_previousContainer = NULL;

	/* If we don't have any element in the list */
	if (list->_nb == 0) {
		list->_firstContainer = newContainer;
		list->_lastContainer = newContainer;
	}
	/* Else (there's already element(s) in the list) */
	else {
		newContainer->_previousContainer = list->_lastContainer;
		list->_lastContainer->_nextContainer = newContainer;
		list->_lastContainer = newContainer;
	}

	list->_nb = list->_nb + 1;

	return 1;
}



int List_update(List* list, unsigned int index, void* element) {
	LinkedContainer* container = list->_firstContainer;
	unsigned int i = 0;

	/* Checking range */
	if (list->_nb == 0 || index > list->_nb - 1) {
		return 0;
	}
		
	for (; i < index; i++) {
		container = container->_nextContainer;
	}
	
	/* Overwrite element: */
	container->_element = element;
	
	return 1;
}



void* List_remove(List* list, unsigned int index) {
	LinkedContainer* containerToFree = list->_firstContainer;
	unsigned int i = 0;
	void* removedElement = NULL;
	Iterator iterator;

	/* Checking range */
	if (list->_nb == 0 || index > list->_nb - 1) {
		return NULL;
	}
	
	for (; i < index; i++) {
		containerToFree = containerToFree->_nextContainer;
	}
	
	/* Prepare result */
	removedElement = containerToFree->_element;
	
	/* Deleting container and decrementing list size done in Iterator_remove() : */
	iterator._containerToRemove = containerToFree;
	iterator._container = containerToFree->_nextContainer;
	iterator._parentList = list;
	Iterator_remove(&iterator);
	
	return removedElement;
}



void List_removeAll(List* list) {
	if (list->_nb == 0) {
		return;
	}

	LinkedContainer* currentContainer = list->_firstContainer;

	unsigned int i = 0;
	for (; i < list->_nb; i++) {
		LinkedContainer* containerToFree = currentContainer;

		/* Update container's reference */
		currentContainer = currentContainer->_nextContainer;

		/* Free iterator */
		free(containerToFree);
	}

	/* Reset list size */
	list->_nb = 0;
}



void List_removeAndFreeAll(List* list, void (*freeElementCallback)(void* element)) {
	if (list->_nb == 0) {
		return;
	}

	LinkedContainer* currentContainer = list->_firstContainer;
		
	unsigned int i = 0;
	for (; i < list->_nb; i++) {
		LinkedContainer* containerToFree = currentContainer;

		/* Update container's reference */
		currentContainer = currentContainer->_nextContainer;

		/* Free element content */
		if (freeElementCallback != NULL) {
			freeElementCallback(containerToFree->_element);
		}

		/* Free element */
		free(containerToFree->_element);

		/* Free container */
		free(containerToFree);
	}

	/* Reset list size */
	list->_nb = 0;
}



int Iterator_emptyIterator_hasNext() {
	return 0;
}



Iterator List_iterator(List* list) {
	static Iterator emptyIterator = {
		NULL, NULL, NULL, Iterator_emptyIterator_hasNext, NULL, NULL
	};

	if (list->_firstContainer != NULL) {
		Iterator iterator;
		iterator._parentList = list;
		iterator._container = list->_firstContainer;
		iterator._containerToRemove = NULL;
		iterator.hasNext = Iterator_hasNext;
		iterator.next = Iterator_next;
		iterator.remove = Iterator_remove;
		return iterator;
	}

	return emptyIterator;
}



List List_LinkedList() {
	List list = {
		0,
		NULL,
		NULL,
		List_size,
		List_get,
		List_add,
		List_update,
		List_remove,
		List_removeAll,
		List_removeAndFreeAll,
		List_iterator
	};
	
	return list;
}
