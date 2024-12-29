# MyMalloc-by-C
The code manages a fixed-size memory array using a custom structure, ‘struct data‘, to keep track of block metadata.
# Memory Management in C

This project implements a simple memory management system in C using a fixed-size array to simulate memory allocation and deallocation. It demonstrates custom versions of `malloc` and `free` using metadata to manage allocated memory blocks.

## Features

1. **Custom Memory Allocation (`MyMalloc`)**:
   - Allocates a block of memory of the specified size if sufficient free space is available.
   - Returns a pointer to the usable memory block.

2. **Custom Memory Deallocation (`MyFree`)**:
   - Frees the memory block allocated by `MyMalloc`.
   - Prevents double freeing and out-of-bounds access.

3. **Memory Metadata Management**:
   - Each memory block is tracked using a `struct data` containing:
     - `size`: The size of the allocated memory block.
     - `isAllocated`: A flag indicating whether the block is allocated or free.

4. **Error Handling**:
   - Handles allocation failures when sufficient memory is unavailable.
   - Detects invalid or double-free operations.

## Structure

### Metadata Structure
```c
struct data {
    int size;          // Size of the memory block
    bool isAllocated;  // Allocation status
};
```

### Memory Array
The memory is simulated using a fixed-size array:
```c
#define MEMORY_SIZE 25000
char Memory[MEMORY_SIZE] = {0};
```

### Functions

1. **`MyCheck(int size)`**:
   - Finds a free block of memory large enough to accommodate the requested size.
   - Returns the starting index of the block or `-1` if no suitable block is found.

2. **`SetBlock(int index, int size)`**:
   - Marks a block of memory as allocated and updates its metadata.

3. **`MyMalloc(int size)`**:
   - Allocates memory and returns a pointer to the usable block.
   - Prints an error message if allocation fails.

4. **`MyFree(void *ptr)`**:
   - Frees the allocated memory block and updates its metadata.
   - Validates the pointer before freeing to prevent errors.

5. **`GetBlockSize(int index)`**:
   - Retrieves the size of a memory block from its metadata.

## Usage

### Example Code
```c
int main() {
    void *allocatedMemory = MyMalloc(1000);

    if (allocatedMemory) {
        printf("Memory allocated at address: %p\n", allocatedMemory);

        struct data *meta = (struct data *)&Memory[0];
        printf("Block Marker: [%d], Block Size: [%d]\n", meta->isAllocated, meta->size);
    }

    MyFree(allocatedMemory);
    MyFree(allocatedMemory); // Attempting to free again

    return 0;
}
```

### Example Output
```
Starting [status box]: 0
Ending [box]: 1035
Memory allocated at address: 0x55ccf1d04060
Block Marker: [1], Block Size: [1000]
Memory block starting at index 0 has been freed.
Memory block not allocated or already freed.
```

## Compilation and Execution

1. Save the code to a file, e.g., `memory_management.c`.
2. Compile the code using a C compiler:
   ```sh
   gcc memory_management.c -o memory_management
   ```
3. Run the executable:
   ```sh
   ./memory_management
   ```

## Notes
- This implementation is a simplified simulation and is not intended for production use.
- The memory array size (`MEMORY_SIZE`) can be adjusted to suit specific requirements.
- Error handling has been implemented to ensure robustness.

## License
This project is licensed under the MIT License. Feel free to use and modify the code as needed.

## Acknowledgments
This implementation was created to demonstrate custom memory management techniques and error handling in C.

