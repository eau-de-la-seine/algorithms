#include "generic_linked_list.h"
/* For malloc() and free() */
#include <stdlib.h>


void* Iterator_get(Iterator* iterator) {
	return iterator->_element;
}



int Iterator_has_next(Iterator* iterator) {
	return iterator->_nextIterator != NULL;
}



Iterator* Iterator_next(Iterator* iterator) {
	return iterator->_nextIterator;
}



Iterator* Iterator_remove_and_next(Iterator* iterator) {
	/* Prepare result */
	Iterator* nextIterator = iterator->_nextIterator;

	--iterator->_parentList->_nb;

	/* Attach previous and next nodes */
	if (iterator->_previousIterator != NULL && iterator->_nextIterator != NULL) {
		iterator->_previousIterator->_nextIterator = iterator->_nextIterator;
	}

	/* Deleting iterator: */
	free(iterator);
	
	return nextIterator;
}



List List_make(){
	List list = {
		0,
		NULL,
		NULL,
		List_size,
		List_get_element,
		List_add_element,
		List_update_element,
		List_remove_element,
		List_remove_all,
		List_remove_and_free_all,
		List_iterator
	};
	
	return list;
}



size_t List_size(List* list) {
	return list->_nb;
}



void* List_get_element(List* list, unsigned int index) {
	Iterator* iterator = list->_firstIterator;
	unsigned int i = 0;

	/* Checking range */
	if (list->_nb == 0 || index > list->_nb - 1) {
		return NULL;
	}
		
	for (; i < index; i++) {
		iterator = iterator->_nextIterator;
	}
	
	return iterator->_element;
}



int List_add_element(List* list, void* element) {
	Iterator* newIterator = (Iterator*) malloc(sizeof(*newIterator));
	
	/* If malloc failed */
	if(newIterator == NULL) {
		return 0;
	}

	/* Init iterator fields */
	newIterator->_element = element;
	newIterator->_nextIterator = NULL;
	newIterator->_previousIterator = NULL;
	newIterator->_parentList = list;
	newIterator->hasNext = Iterator_has_next;
	newIterator->get = Iterator_get;
	newIterator->next = Iterator_next;
	newIterator->removeAndNext = Iterator_remove_and_next;

	/* If we don't have any element in the list */
	if(list->_nb == 0) {
		list->_firstIterator = newIterator;
		list->_lastIterator = newIterator;
	}
	/* Else (there's already element(s) in the list) */
	else {
		newIterator->_previousIterator = list->_lastIterator;
		list->_lastIterator->_nextIterator = newIterator;
		list->_lastIterator = newIterator;
	}
	
	++list->_nb;
	
	return 1;
}



int List_update_element(List* list, unsigned int index, void* element) {
	Iterator* iterator = list->_firstIterator;
	unsigned int i = 0;

	/* Checking range */
	if (list->_nb == 0 || index > list->_nb - 1) {
		return 0;
	}
		
	for (; i < index; i++) {
		iterator = iterator->_nextIterator;
	}
	
	/* Overwrite element: */
	iterator->_element = element;
	
	return 1;
}



 void* List_remove_element(List* list, unsigned int index) {
	Iterator* iterator = list->_firstIterator;
	unsigned int i = 0;
	void* removedElement = NULL;

	/* Checking range */
	if (list->_nb == 0 || index > list->_nb - 1) {
		return NULL;
	}
	
	for (; i < index; i++) {
		iterator = iterator->_nextIterator;
	}
	
	/* Prepare result */
	removedElement = iterator->_element;
	
	/* Deleting iterator (decrementation is done in removeAndNext): */
	iterator->removeAndNext(iterator);
	
	return removedElement;
}



void List_remove_all(List* list) {
	if (list->_nb != 0) {
		Iterator* iterator = list->_firstIterator;
			
		unsigned int i = 0;
		for (; i < list->_nb; i++) {
			Iterator* iteratorToFree = iterator;
			
			/* Update iterator's reference */
			iterator = iterator->_nextIterator;
			
			/* Free iterator */
			free(iteratorToFree);
		}
	}
	
	/* Reinite list size */
	list->_nb = 0;
}



void List_remove_and_free_all(List* list) {
	if (list->_nb != 0) {
		Iterator* iterator = list->_firstIterator;
			
		unsigned int i = 0;
		for (; i < list->_nb; i++) {
			Iterator* iteratorToFree = iterator;
			
			/* Update iterator's reference */
			iterator = iterator->_nextIterator;
			
			/* Free element */
			free(iteratorToFree->_element);
			
			/* Free iterator */
			free(iteratorToFree);
		}
	}
	
	/* Reinite list size */
	list->_nb = 0;
}


int Iterator_emptyIterator_has_next() {
	return 0;
}



Iterator* List_iterator(List* list) {
	static Iterator emptyIterator = {
		NULL, NULL, NULL, NULL, Iterator_emptyIterator_has_next, NULL, NULL, NULL
	};

	return (list->_firstIterator != NULL) ? list->_firstIterator : &emptyIterator;
}
