#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "avalon_internal.h"


void avalon_list_init(avalon_list *list, uint64_t size) {
	list->elements = NULL;
	list->element_count = 0;
	list->element_max = 0;
	list->element_size = size;
}


void *avalon_list_get_new(avalon_list *list) {
	if (list->element_count == list->element_max) {
		list->element_max = list->element_max * 2 + 1;
		list->elements = realloc(list->elements, list->element_max * list->element_size);
		if (list->elements == NULL) {
			printf("Failed to resize list to %lu items!\n", list->element_count);
		}
	}

	void *element = list->elements + list->element_count * list->element_size;
	list->element_count++;
	return element;
}


void *avalon_list_get(avalon_list *list, uint64_t index) {
	if (index >= list->element_count) { return NULL; }
	return list->elements + index * list->element_size;
}
