#include <stdlib.h>

static char* FL_ErrorMessage;

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

char* FL_GetLastError() {
	return FL_ErrorMessage;
}

int FL_Add(FlexList* list, void* item, enum FlexListType itemType) {
	if (list == NULL) {
		FL_ErrorMessage = "FlexList* unspecified";
		return -1;
	}
	if (item == NULL) {
		FL_ErrorMessage = "Item unspecified";
		return -1;
	}
	if (itemType == NULL) {
		itemType = FL_TYPE_UNDEFINED;
		FL_ErrorMessage = "Item type unspecified. Set to FL_TYPE_UNDEFINED";
	}

	FlexListItem newItem = { item, NULL, itemType };
	list->last->next = &newItem;
	list->last = &newItem;
	list->size++;

	return 0;
}