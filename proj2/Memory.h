#include <iostream>
#include "List.h"

class MyMemoryBlock {
    public:
        MyMemoryBlock(int ind = 0, int len = 0); // constructor
        int get_length(); // return the current length of the memory block.
        int get_index(); // return the index of the memory block.
        int allocate_mem(int len); // emulates memory allocation
        void free_mem(int len);

    private:
        int index;
        int length;
};

template <typename T>
class MyMemory : MyMemoryBlock {
    public:
        MyMemory(int num = 0, int len = 0); // constructor
        ~MyMemory(); // deconstructor
        void resize(int num = 100, int len = 100); // resize the system memory
        int req_mem(int len); // request memory of size
        bool release_mem(int ind, int len); // de-allocate memory.
        void merge_mem(); // merge small neighboring blocks
        void dump(); // dump the content of mlist

    private:
        cop4530::List<MyMemoryBlock> mlist;
        int max_index;
        int block_size;
};
