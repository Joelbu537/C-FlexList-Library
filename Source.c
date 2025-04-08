#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

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
	FL_TYPE_UNDEFINED,
	FL_TYPE_NULL
};

// Crack-Gedanken von irgendwann:
// Wenn List-Length > 10 und ComplexityPointer == NULL, neue ComplexityPointer.

struct FlexListItem;
typedef struct FlexListItem {
	void* content;
	struct FlexListItem* next;
	enum FlexListType type;
} FlexListItem;
struct FlexList;
typedef struct FlexList {
	FlexListItem* first;
	FlexListItem* last;
	unsigned int size;
	struct FlexList* complexityDictionary;
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
	if (FL_ErrorMessage != NULL) {
		free(FL_ErrorMessage);
	}

	FL_ErrorMessage = malloc(strlen(message) + 1);
	if (!FL_ErrorMessage) {
		return -1;
	}

	strcpy_s(FL_ErrorMessage, strlen(message) + 1, message);

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

	FlexList* dictionary = malloc(sizeof(FlexList));
	if (dictionary == NULL) {
		FL_SetLastError("Memory allocation of a new FlexList instance failed.");
		free(list);
		return NULL;
	}

	// Create the 0st and 1st List* so for loops don't need to be fucked with and work normal and fine and how they are supposed to work.
	// Might be unneccessary

	FlexListItem* zeroComplexity = malloc(sizeof(FlexListItem));
	FlexListItem* oneComplexity = malloc(sizeof(FlexListItem));

	zeroComplexity->content = NULL;
	zeroComplexity->type = FL_TYPE_NULL;
	zeroComplexity->next = oneComplexity;

	oneComplexity->content = NULL;
	oneComplexity->type = FL_TYPE_NULL;
	oneComplexity->next = NULL;

	// Add evrythiong together and return the list.
	dictionary->first = zeroComplexity;
	dictionary->last = oneComplexity;
	dictionary->size = 2;
	dictionary->complexityDictionary = NULL;

	list->complexityDictionary = dictionary;

	//List is now configured.
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
	if (itemType < FL_TYPE_BOOL || itemType > FL_TYPE_NULL) {
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
	}
	else if (list->last != NULL) {
		list->last->next = newItem;
		list->last = newItem;
		list->size++;
	}
	else {
		FL_SetLastError("Unknown error occurred while adding a new Element to a list.");
		return -1;
	}

	//Add dictionary entry if neccesarry.
	if ((int)powf((float)10, (float)list->complexityDictionary->size) < list->size) {
		
	}

	return 0;
}
//NOT FIXED
/**
 * @brief Gets a void* from a FlexList at a specified position.
 *
 * @param list A FlexList pointer pointing to the list you wish to add something to.
 * @param index The index of the item you wish to get.
 *
 * @return Returns a void* on success, NULL on failure.
 */
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
//NOT FIXED
/**
 * @brief Gets the data type of a FlexListItem.
 *
 * @param list A FlexList pointer pointing to the target list.
 * @param index The index of the item you wish to get the datatype.
 *
 * @return Returns a enum FlexListType on success, enum FlexListType FL_TYPE_UNDEFINED on failure.
 */
enum FlexListType FL_GetItemType(FlexList* list, unsigned int index) {
	if (list == NULL) {
		FL_SetLastError("FlexList* unspecified");
		return FL_TYPE_UNDEFINED;
	}
	if (index >= list->size) {
		FL_SetLastError("Index out of bounds");
		return FL_TYPE_UNDEFINED;
	}
	FlexListItem* currentItem = list->first;
	for (unsigned int i = 0; i < index; i++) {
		currentItem = currentItem->next;
	}
	return currentItem->type;
}
/**
 * @brief Gets the length of a FlexList.
 *
 * @param list A FlexList pointer pointing to the list you wish to get the length of.
 * 
 * @return Returns an unsigned integer representing the length of the list.
 */
unsigned int FL_GetLength(FlexList* list) {
	if (list == NULL) {
		FL_SetLastError("FlexList* unspecified.");
		return NULL;
	}
	return list->size;
}
/**
 * @brief Removes an item from a FlexList at a specified position.
 *
 * @param list A FlexList pointer pointing to the list you wish to remove an item from.
 * @param index The index of the item you wish to remove.
 *
 * @return Returns 0 on success, -1 on failure.
 */
int FL_RemoveItem(FlexList* list, unsigned int index) {
	if (list == NULL) {
		FL_SetLastError("FlexList* unspecified.");
		return -1;
	}
	if (index >= list->size) {
		FL_SetLastError("Index out of bounds.");
		return -1;
	}

	FlexListItem* previousItem = NULL;
	FlexListItem* currentItem = list->first;
	for (unsigned int i = 0; i < index; i++) {
		previousItem = currentItem;
		currentItem = currentItem->next;
	}

	// First element
	if (currentItem == list->first) {
		list->first = currentItem->next;
		if (list->first == NULL) {
			list->last = NULL;
		}
	}
	// Last element
	else if (currentItem == list->last) {
		list->last = previousItem;
		list->last->next = NULL;
	}
	// Fall 3: Defalt
	else {
		previousItem->next = currentItem->next;
	}

	free(currentItem);
	list->size--;
	return 0;
}
int main() {
	FlexList* testList = FL_Create();
	unsigned int length = FL_GetLength(testList);
	printf("List Length: %u\n", length);
	FL_Add(testList,"Test", FL_TYPE_STRING);
	FL_Add(testList, "Test2", FL_TYPE_STRING);
	length = FL_GetLength(testList);
	printf("List Length: %u\n", length);
	FL_RemoveItem(testList, 1);
	length = FL_GetLength(testList);
	printf("List Length: %u\n", length);
	FL_RemoveItem(testList, 0);
	length = FL_GetLength(testList);
	printf("List Length: %u\n", length);
	FL_RemoveItem(testList, 3);
	printf("Latest Error: %s\n", FL_GetLastError());
	return 0;
}