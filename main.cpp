#include <iostream>
#include "UnirefHeap.h"

int main(int argc, const char *argv[]) {
    std::priority_queue<int> queue;
    if (argc != 4) {
        printf("./UnirefQuery <file path> <max seq length> <heap size>\n");
        exit(0);
    }
    UnirefHeap *heap = new UnirefHeap(std::atoi(argv[2]), std::atoi(argv[3]));
    heap->ReadFile(std::string(argv[1]));
    heap->OutputHeap();
    return 0;
}
