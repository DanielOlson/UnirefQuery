//
// Created by Olson, Daniel (NIH/NIAID) [E] on 5/3/22.
//

#ifndef UNIREFQUERY_UNIREFHEAP_H
#define UNIREFQUERY_UNIREFHEAP_H
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>

class UnirefHeap {
public:
    int smallest_item = 100000000;
    int heap_size = 10000;
    int max_seq_len = 750;
    std::vector<std::tuple<int, std::string, std::string>> heap;

    UnirefHeap(int max_len, int size) {
        heap_size = size;
        max_seq_len = max_len;

    }

    void ReadFile(std::string file_path);
    void OutputHeap();
};


#endif //UNIREFQUERY_UNIREFHEAP_H
