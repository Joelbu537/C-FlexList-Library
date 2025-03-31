#include <stdio.h>

#include <stdlib.h>
#include <string.h>

char* FL_ErrorMessage = NULL;

enum FlexListType {
	FL_TYPE_BOOL,
	FL_TYPE_BYTE,
	FL_TYPE_SHORT,
	FL_TYPE_INT,
	FL_TYPE_LONG,
	FL_TYPE_SBYTE,
	FL_TYPE_USHORT,
	FL_TYPE_UINT,
	FL_TYPE_ULONG,
	FL_TYPE_FLOAT,
	FL_TYPE_DOUBLE,
	FL_TYPE_CHAR,
	FL_TYPE_STRING,
	FL_TYPE_LIST,
	FL_TYPE_VOID,
	FL_TYPE_UNDEFINED
};
struct FlexListItem;
typedef struct FlexListItem {
	void* content;
	struct FlexListItem* next;
	enum FlexListType type;
} FlexListItem;

typedef struct FlexList {
	FlexListItem* first;
	FlexListItem* last;
	unsigned int size;
} FlexList;

/**
 * @brief Updates the error message.
 *
 *
 * @param message The new error message.
 *
 * @return Returns 0 on success, -1 on failure.
 */
int FL_SetLastError(const char* message) {
	free(FL_ErrorMessage);
	FL_ErrorMessage = malloc(strlen(message) + 1);
	if (!FL_ErrorMessage) return -1;  // Speicherfehler
	strcpy_s(FL_ErrorMessage, sizeof(FL_ErrorMessage), message);
	return 0;
}
/**
 * @brief Used to get the last error message.
 *
 * @return Returns the most recent error message.
 */
char* FL_GetLastError() {
	return FL_ErrorMessage;
}
/**
 * @brief Creates a new FlexList instance.
 *
 * @return Returns a FlexList* on success, NULL on failure.
 */
FlexList* FL_Create() {
	FlexList* list = malloc(sizeof(FlexList));
	if (list == NULL) {
		FL_SetLastError("Memory allocation of a new FlexList instance failed.");
		return NULL;
	}
	list->first = NULL;
	list->last = NULL;
	list->size = 0;
	return list;
}
/**
 * @brief Adds a new FlexListItem to the back of a FlexList.
 *
 * @param list A FlexList pointer pointing to the list you wish to add something to.
 * @param item A pointer pointing to the value you want to store in this FlexListItem.
 * @param itemType The type of the item you want to store in this FlexListItem.
 *
 * @return Returns 0 on success, -1 on failure.
 */
int FL_Add(FlexList* list, void* item, enum FlexListType itemType) {
	if (list == NULL) {
		FL_SetLastError("FlexList* unspecified.");
		return -1;
	}
	if (item == NULL) {
		FL_SetLastError("Item* unspecified.");
		return -1;
	}
	if (itemType < FL_TYPE_BOOL || itemType > FL_TYPE_UNDEFINED) {
		itemType = FL_TYPE_UNDEFINED;
		FL_SetLastError("Item type unspecified. Set to FL_TYPE_UNDEFINED instead.");
	}

	FlexListItem* newItem = malloc(sizeof(FlexListItem));
	if (newItem == NULL) {
		FL_SetLastError("Memory allocation of a new FlexListItem failed.");
		return -1;
	}

	newItem->content = item;
	newItem->type = itemType;
	newItem->next = NULL;

	if (list->first == NULL && list->last == NULL) {
		list->first = newItem;
		list->last = newItem;
		list->size = 1;

		return 0;
	}
	else if (list->last != NULL) {
		list->last->next = newItem;
		list->last = newItem;
		list->size++;

		return 0;
	}
	else {
		FL_SetLastError("Unknown error occurred while adding a new Element to a list.");

		return -1;
	}
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
unsigned int FL_GetLength(FlexList* list) {
	if (list == NULL) {
		FL_SetLastError("FlexList* unspecified");
		return NULL;
	}
	return list->size;
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
int main() {
	FlexList* testList = FL_Create();
	unsigned int length = FL_GetLength(testList);
	printf("List Length: %u\n", length);
	FL_Add(testList,"Test", FL_TYPE_STRING);
	FL_Add(testList, "Test2", FL_TYPE_STRING);
	length = FL_GetLength(testList);
	printf("List Length: %u\n", length);
	return 0;
}