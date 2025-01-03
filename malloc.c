#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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
            for(index = i; index <(i + size + sizeof(struct data)) && index < MEMORY_SIZE; index++)
            {// if block is allocated then move to next space
                if (meta->isAllocated) {
                    i = index;
                    loopStatus = false;
                    break;
                }
                if (index>=24999){
                    loopStatus = false;
                    i=index+1;
                    break;
                       }
                loopStatus = true;//free space allocation flag
            }
         if (loopStatus) {// if has free space print details
                printf("Alloction --> [Start(%d)....end(%d)]\n\n", i+sizeof(struct data) - 1, i + size + sizeof(struct data) - 1);
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
        printf("Memory Allocation failed\n\n");
        return NULL;
    } else {
        SetBlock(ptr, size);
        return &Memory[ptr + sizeof(struct data)]; 
    }// malloc function handle
}

void MyFree(void *ptr) {

    if (ptr == NULL) {
        printf("Invalid pointer.Can Not Free.\n\n");
        return;
    }
    int blockStart = (char *)ptr - Memory - sizeof(struct data);
    if (blockStart < 0 || blockStart >= MEMORY_SIZE) {
        printf("Pointer can not identify, Sorry\n\n");
        return;
    }
    struct data *meta = (struct data *)&Memory[blockStart];

    if (!meta->isAllocated) {
        printf("Memory block not allocated or already freed.\n\n");
        return;
    }
    meta->isAllocated = false;
    for(int index=blockStart+7;index<(meta->size+blockStart+7);index++){
        Memory[index]=0;
         } 
    meta->size=0;
    printf("Memory block starting at index %d has been freed.\n\n", blockStart);
}// free up the heap

void print(void *ptr)
{
if (ptr) {
        printf("Memory allocated at address: %p\n\n", ptr);

        struct data *meta = (struct data *)&Memory[0];
        printf("Block Marker: [%d], Block Size: [%d]\n\n\n", meta->isAllocated, meta->size);
    }

}

int main() {
    void *ptr1 = MyMalloc(24000); 
    print(ptr1);
    MyFree(ptr1);
    void *ptr3 = MyMalloc(240); 
    MyFree(ptr3);
    void *ptr4 = MyMalloc(30); 
    void *ptr2 = MyMalloc(2000); 



    return 0;
}
