#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> // For using fixed-width integer types like int32_t
#define MEMORY_SIZE 25000

struct data
{
    int size;
    bool isAlocated;
};

char Memory[MEMORY_SIZE] = {0}; // Initialize the memory array to zero

int MyCheck(int size) {
    int i = 0;

    while (i < MEMORY_SIZE) {
        if (Memory[i] == 'T') {
            i = i + *((int *)&Memory[i + 1]) + 2 + sizeof(int); // Adjust for size of int
        } else {
            bool loopStatus = false;
            int index;
            for (index = i; index < i + size + 2 + sizeof(int) && index < MEMORY_SIZE; index++) {
                if (Memory[index] == 'T') {
                    i = index;
                    loopStatus = false;
                    break;
                }
                loopStatus = true;
            }

            if (loopStatus) {
                printf("Starting [status box]: %d\n", i);
                printf("Ending [box]: %d\n", index - 1);
                return i;
            }
        }
    }
    return -1; // No valid block found
}

void SetBlock(int index, int size) {
    Memory[index] = 'T';  // Mark as occupied
    *((int *)&Memory[index + 1]) = size; // Store size as an int
}

void *MyMalloc(int size) {
    int ptr = MyCheck(size);
    if (ptr == -1) {
        printf("Memory Allocation failed\n");
        return NULL;
    } else {
        SetBlock(ptr, size);
        return &Memory[ptr + 2 + sizeof(int)]; // Return usable memory
    }
}

void MyFree(void *ptr) {
    if (ptr == NULL) {
        printf("Invalid pointer. Nothing to free.\n");
        return;
    }

    // Calculate the index in Memory where this block starts
    int blockStart = (char *)ptr - Memory - (2 + sizeof(int));

    if (blockStart < 0 || blockStart >= MEMORY_SIZE) {
        printf("Pointer out of bounds. Free failed.\n");
        return;
    }

    if (Memory[blockStart] != 'T') {
        printf("Memory block not allocated or already freed.\n");
        return;
    }

    // Mark the block as free
    Memory[blockStart] = 0; // Clear the block marker
    printf("Memory block starting at index %d has been freed.\n", blockStart);
}

int GetBlockSize(int index) {
    return *((int *)&Memory[index + 1]); // Retrieve block size
}

int main() {
    void *allocatedMemory = MyMalloc(1000); // Allocate 1000 bytes

    if (allocatedMemory) {
        printf("Memory allocated at address: %p\n", allocatedMemory);
        printf("Block Marker: [%c], Block Size: [%d]\n", Memory[0], GetBlockSize(0));
    }

    MyFree(allocatedMemory); // Free the allocated memory

    // Try freeing the same memory again
    MyFree(allocatedMemory);

    return 0;
} 