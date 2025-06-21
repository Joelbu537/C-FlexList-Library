#ifndef LIST_H
#define LIST_H

char* FL_ErrorMessage;

enum FlexListType;

// Crack-Gedanken von irgendwann:
// Wenn List-Length > 10 und ComplexityPointer == NULL, neue ComplexityPointer.
// Target Index ist 10.145. Wie vorgehen?
// 10000-Dictionary nutzen um zu Index 10.000 zu springen.
// Wie herausfinden dass wir nach 10000 suchen?
// Index zu string, Stringlänge ermitteln.
// 
// Die Stringlänge == log10(10000) == 4 Directory-Sprünge.
// num = index;
// char str[(int)((ceil(log10(num))+1)*sizeof(char))];
// sprintf(str, "%d", index);

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
int FL_SetLastError(const char* message);
/**
 * @brief Used to get the last error message.
 *
 * @return Returns the most recent error message.
 */
char* FL_GetLastError();
/**
 * @brief Creates a new FlexList instance.
 *
 * @return Returns a FlexList* on success, NULL on failure.
 */
FlexList* FL_Create();
/**
 * @brief Adds a new FlexListItem to the back of a FlexList.
 *
 * @param list A FlexList pointer pointing to the list you wish to add something to.
 * @param item A pointer pointing to the value you want to store in this FlexListItem.
 * @param itemType The type of the item you want to store in this FlexListItem.
 *
 * @return Returns 0 on success, -1 on failure.
 */
int FL_Add(FlexList* list, void* item, enum FlexListType itemType);
//NOT FIXED
/**
 * @brief Gets a void* from a FlexList at a specified position.
 *
 * @param list A FlexList pointer pointing to the list you wish to add something to.
 * @param index The index of the item you wish to get.
 *
 * @return Returns a void* on success, NULL on failure.
 */
void* FL_GetItem(FlexList* list, unsigned int index);
//NOT FIXED
/**
 * @brief Gets the data type of a FlexListItem.
 *
 * @param list A FlexList pointer pointing to the target list.
 * @param index The index of the item you wish to get the datatype.
 *
 * @return Returns a enum FlexListType on success, enum FlexListType FL_TYPE_UNDEFINED on failure.
 */
enum FlexListType FL_GetItemType(FlexList* list, unsigned int index);
/**
 * @brief Gets the length of a FlexList.
 *
 * @param list A FlexList pointer pointing to the list you wish to get the length of.
 *
 * @return Returns an unsigned integer representing the length of the list.
 */
unsigned int FL_GetLength(FlexList* list);
/**
 * @brief Removes an item from a FlexList at a specified position.
 *
 * @param list A FlexList pointer pointing to the list you wish to remove an item from.
 * @param index The index of the item you wish to remove.
 *
 * @return Returns 0 on success, -1 on failure.
 */
int FL_RemoveItem(FlexList* list, unsigned int index);
/*int main() {
	FlexList* testList = FL_Create();
	unsigned int length = FL_GetLength(testList);
	printf("List Length: %u\n", length);
	FL_Add(testList, "Test", FL_TYPE_STRING);
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
}*/
#endif