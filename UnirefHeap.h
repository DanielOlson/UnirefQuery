//
// Created by Olson, Daniel (NIH/NIAID) [E] on 5/3/22.
//

#ifndef UNIREFQUERY_UNIREFHEAP_H
#define UNIREFQUERY_UNIREFHEAP_H
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

struct gt_n {
    inline bool operator() ( std::tuple<int, std::string, std::string> struct1,
                             std::tuple<int, std::string, std::string> struct2)
    {
        return (std::get<0>(struct1) > std::get<0>(struct2));
    }
};


class UnirefHeap {
public:
    int smallest_item = 100000000;
    int heap_size = 10000;
    int max_seq_len = 750;
    std::priority_queue<std::tuple<int, std::string, std::string>,
                        std::vector<std::tuple<int, std::string, std::string>>,
                        gt_n> heap;
    UnirefHeap(int max_len, int size) {
        heap_size = size;
        max_seq_len = max_len;
    }

    int ProcessTuple(std::tuple<int, std::string, std::string>tup);
    void ReadFile(std::string file_path);
    void OutputHeap();
};


#endif //UNIREFQUERY_UNIREFHEAP_H
