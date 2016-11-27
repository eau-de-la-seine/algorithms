#include <stdlib.h> // malloc and free
#include "generic_linked_list.h"


void* Iterator_get(Iterator* iterator) {
	return iterator->_element;
}



Iterator* Iterator_next(Iterator* iterator) {
	return iterator->_nextIterator;
}



Iterator* Iterator_remove_and_next(Iterator* iterator) {
	--iterator->_parentList->_nb;

	// Attach previous and next nodes
	if (iterator->_previousIterator != NULL && iterator->_nextIterator != NULL) {
		iterator->_previousIterator->_nextIterator = iterator->_nextIterator;
	}
	
	// Prepare result
	Iterator* nextIterator = iterator->_nextIterator;

	// Deleting iterator:
	free(iterator);
	iterator = NULL;
	
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



int List_size(List* list) {
	return list->_nb;
}



void* List_get_element(List* list, unsigned int index) {
	if (list->_nb == 0 || index > list->_nb - 1) {
		return NULL;
	}
	
	Iterator* iterator = list->_firstIterator;
		
	unsigned int i = 0;
	for (; i < index; i++) {
		iterator = iterator->_nextIterator;
	}
	
	return iterator->_element;
}



int List_add_element(List* list, void* element) {
	Iterator* newIterator = (Iterator*) malloc(sizeof(*newIterator));
	
	// If malloc failed
	if(newIterator == NULL) {
		return 0;
	}

	// Init iterator fields
	newIterator->_element = element;
	newIterator->_nextIterator = NULL;
	newIterator->_previousIterator = NULL;
	newIterator->_parentList = list;
	newIterator->get = Iterator_get;
	newIterator->next = Iterator_next;
	newIterator->removeAndNext = Iterator_remove_and_next;

	// If we don't have any element in the list
	if(list->_nb == 0) {
		list->_firstIterator = newIterator;
		list->_lastIterator = newIterator;
	}
	// Else (there's already element(s) in the list)
	else {
		newIterator->_previousIterator = list->_lastIterator;
		list->_lastIterator->_nextIterator = newIterator;
		list->_lastIterator = newIterator;
	}
	
	++list->_nb;
	
	return 1;
}



int List_update_element(List* list, unsigned int index, void* element) {
	if (list->_nb == 0 || index > list->_nb - 1) {
		return 0;
	}
	
	Iterator* iterator = list->_firstIterator;
		
	int i = 0;
	for (; i < index; i++) {
		iterator = iterator->_nextIterator;
	}
	
	// Overwrite element:
	iterator->_element = element;
	
	return 1;
}



 void* List_remove_element(List* list, unsigned int index) {
	if (list->_nb == 0 || index > list->_nb - 1) {
		return NULL;
	}
	
	Iterator* iterator = list->_firstIterator;
	
	unsigned int i = 0;
	for (; i < index; i++) {
		iterator = iterator->_nextIterator;
	}
	
	// Prepare result
	void* removedElement = iterator->_element;
	
	// Deleting iterator (decrementation is done in removeAndNext):
	iterator->removeAndNext(iterator);
	
	return removedElement;
}



void List_remove_all(List* list) {
	if (list->_nb != 0) {
		Iterator* iterator = list->_firstIterator;
			
		unsigned int i = 0;
		for (; i < list->_nb; i++) {
			Iterator* iteratorToFree = iterator;
			
			// Update iterator's reference
			iterator = iterator->_nextIterator;
			
			// Free iterator
			free(iteratorToFree);
			iteratorToFree = NULL;
		}
	}
	
	// Reinite list size
	list->_nb = 0;
}



void List_remove_and_free_all(List* list) {
	if (list->_nb != 0) {
		Iterator* iterator = list->_firstIterator;
			
		unsigned int i = 0;
		for (; i < list->_nb; i++) {
			Iterator* iteratorToFree = iterator;
			
			// Update iterator's reference
			iterator = iterator->_nextIterator;
			
			// Free element
			free(iteratorToFree->_element);
			iteratorToFree->_element = NULL;
			
			// Free iterator
			free(iteratorToFree);
			iteratorToFree = NULL;
		}
	}
	
	// Reinite list size
	list->_nb = 0;
}



Iterator* List_iterator(List* list) {
	return list->_firstIterator;
}
