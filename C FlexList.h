#include <stdlib.h>
#include <string.h>

char* FL_ErrorMessage = NULL;

enum FlexListType {
	FL_TYPE_BOOL,
	FL_TYPE_BYTE,
	FL_TYPE_SHORT,
	FL_TYPE_INT,
	FL_TYPE_LONG,
	FL_TYPE_FLOAT,
	FL_TYPE_DOUBLE,
	FL_TYPE_CHAR,
	FL_TYPE_STRING,
	FL_TYPE_LIST,
	FL_TYPE_VOID,
	FL_TYPE_UNDEFINED
};

typedef struct {
	void* content;
	FlexListItem* next;
	enum FlexListType type;
} FlexListItem;

typedef struct {
	FlexListItem* first;
	FlexListItem* last;
	unsigned int size;
} FlexList;

int FL_SetLastError(const char* message) {
	free(FL_ErrorMessage);
	FL_ErrorMessage = malloc(strlen(message) + 1);
	if (!FL_ErrorMessage) return -1;  // Speicherfehler
	strcpy(FL_ErrorMessage, message);
	return 0;
}
char* FL_GetLastError() {
	return FL_ErrorMessage;
}

int FL_Add(FlexList* list, void* item, enum FlexListType itemType) {
	if (list == NULL) {
		FL_SetLastError("FlexList* unspecified");
		return -1;
	}
	if (item == NULL) {
		FL_SetLastError("Item unspecified");
		return -1;
	}
	if (itemType < FL_TYPE_BOOL || itemType > FL_TYPE_UNDEFINED) {
		itemType = FL_TYPE_UNDEFINED;
		FL_SetLastError("Item type unspecified. Set to FL_TYPE_UNDEFINED");
	}

	FlexListItem newItem = { item, NULL, itemType };

	if (list->first == NULL) {
		list->first = &newItem;
		list->last = &newItem;
		list->size++;

		return 0;
	}
	else {
		list->last->next = &newItem;
		list->last = &newItem;
		list->size++;

		return 0;
	}
}

int FL_Create(FlexList* list) {
	if (list == NULL) {
		FL_SetLastError("FlexList* unspecified");
		return -1;
	}
	list->first = NULL;
	list->last = NULL;
	list->size = 0;
	return 0;
}

void* FL_GetItem(FlexList* list, unsigned int index) {
	if (list == NULL) {
		FL_SetLastError("FlexList* unspecified");
		return NULL;
	}
	if (index >= list->size) {
		FL_SetLastError("Index out of bounds");
		return NULL;
	}
	FlexListItem* currentItem = list->first;
	for (unsigned int i = 0; i < index; i++) {
		currentItem = currentItem->next;
	}
	return currentItem->content;
}
int FL_RemoveItem(FlexList* list, unsigned int index) {
	if (list == NULL) {
		FL_SetLastError("FlexList* unspecified");
		return NULL;
	}
	if (index >= list->size) {
		FL_SetLastError("Index out of bounds");
		return NULL;
	}
	FlexListItem* previousItem = NULL;
	FlexListItem* currentItem = list->first;
	for (unsigned int i = 0; i < index; i++) {
		if (i == index - 1) {
			previousItem = currentItem;
		}
		currentItem = currentItem->next;
	}
	if (currentItem->next == NULL) {
		previousItem->next = NULL;
	}
	else {
		previousItem->next = currentItem->next;
	}
	free(currentItem);
	list->size--;
}