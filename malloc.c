#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> 
#define MEMORY_SIZE 25000

struct data {
    int size;          
    bool isAllocated; 
};//this struct describe block size and isallocate or not

char Memory[MEMORY_SIZE] = {0}; 

int MyCheck(int size) {
    int i = 0;

    while (i < MEMORY_SIZE) {//check full array
        struct data *meta = (struct data *)&Memory[i];//casting

        if (meta->isAllocated) {// if block is allocated then move to next space
            i = i + meta->size + sizeof(struct data); 
        } 
        
        else {
            bool loopStatus = false;
            int index;
            for(index = i; index <(i + meta->size + sizeof(struct data)) && index < MEMORY_SIZE; index++)
            {// if block is allocated then move to next space
                if (meta->isAllocated) {
                    i = index;
                    loopStatus = false;
                    break;
                }
                loopStatus = true;//free space allocation flag

            }
         if (loopStatus) {// if has free space print details
                printf("Starting [status box]: %d\n", i);
                printf("Ending [box]: %d\n", i + size + sizeof(struct data) - 1);
                return i;
            }
        }
    }
    return -1;
}

void SetBlock(int index, int size) {
    struct data *meta = (struct data *)&Memory[index];
    meta->size = size;
    meta->isAllocated = true;  }// update data 

void *MyMalloc(int size) {
    int ptr = MyCheck(size);
    if (ptr == -1) {
        printf("Memory Allocation failed\n");
        return NULL;
    } else {
        SetBlock(ptr, size);
        return &Memory[ptr + sizeof(struct data)]; 
    }// malloc function handle
}

void MyFree(void *ptr) {
    if (ptr == NULL) {
        printf("Invalid pointer. Nothing to free.\n");
        return;
    }

    int blockStart = (char *)ptr - Memory - sizeof(struct data);

    if (blockStart < 0 || blockStart >= MEMORY_SIZE) {
        printf("Pointer out of bounds. Free failed.\n");
        return;
    }

    struct data *meta = (struct data *)&Memory[blockStart];
    if (!meta->isAllocated) {
        printf("Memory block not allocated or already freed.\n");
        return;
    }


    meta->isAllocated = false; 
    printf("Memory block starting at index %d has been freed.\n", blockStart);
}// free up the heap

int GetBlockSize(int index) {
    struct data *meta = (struct data *)&Memory[index];
    return meta->size; 
}

void print(void *ptr)
{
if (ptr) {
        printf("Memory allocated at address: %p\n", ptr);

        struct data *meta = (struct data *)&Memory[0];
        printf("Block Marker: [%d], Block Size: [%d]\n\n\n", meta->isAllocated, meta->size);
    }

}
int main() {
    void *ptr1 = MyMalloc(1000); 
    print(ptr1);
    void *ptr2 = MyMalloc(2000); 
    print(ptr2);
    void *ptr3 = MyMalloc(1000);
    print(ptr3); 
    void *ptr4 = MyMalloc(3000);
    print(ptr4); 
    
    MyFree(ptr2);
    void *ptr5 = MyMalloc(100); 
    print(ptr5);

    return 0;
}



