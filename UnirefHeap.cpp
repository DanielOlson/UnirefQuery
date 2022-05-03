//
// Created by Olson, Daniel (NIH/NIAID) [E] on 5/3/22.
//

#include "UnirefHeap.h"
#include <fstream>

struct gt_n {
    inline bool operator() (const std::tuple<int, std::string, std::string>& struct1,
            const std::tuple<int, std::string, std::string>& struct2)
    {
        return (std::get<0>(struct1) > std::get<0>(struct2));
    }
};

int nForHeader(const std::string &header) {
    int state = 0;
    int n = 0;
    for (int i = 0; i < header.size(); ++i) {
        if (state == 0) {
            if (header[i] == 'n')
                state++;
        }

        else if (state == 1) {
            state++;
        }

        else {
            int c = header[i] - '0';
            if (c >= 0 && c <= 9)
                n = (n * 10) + c;
            else
                return n;
        }
    }

    return n;
}

void UnirefHeap::ReadFile(std::string file_path) {
    int state = 0;

    std::ifstream file(file_path);

    std::string header_line = "";
    int n = 0;
    std::string seq = "";

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.length() > 0) {
                if (line[0] == '>') {
                    if (seq.length() > 0 && seq.length() < max_seq_len) {
                        // add the sequence to the heap
                        if (heap.size() < heap_size) {
                            heap.push_back(std::make_tuple(n, header_line, seq));
                            std::push_heap(heap.begin(), heap.end(), gt_n());
                            if (n < smallest_item)
                                smallest_item = n;
                        }

                        else {
                            if (n > smallest_item) {
                                heap.pop_back();

                                std::pop_heap(heap.begin(), heap.end(), gt_n());
                                heap.push_back(std::make_tuple(n, header_line, seq));
                                std::push_heap(heap.begin(), heap.end(), gt_n());

                                smallest_item = std::get<0>(heap.back());
                            }

                        }

                        header_line = line;
                        n = nForHeader(header_line);
                        seq = "";
                    }
                }

                else {
                    for (int i = 0; i < line.length(); ++i) {
                        char c = line[i];
                        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= "Z")) {
                            c = std::toupper(c);
                            seq.push_back(c);
                        }
                    }
                }
            }
        }
        file.close();
    }

    else {
        printf("Unable to open file.\n");
        exit(-1);
    }
}

void UnirefHeap::OutputHeap() {
    std::sort_heap(heap.begin(), heap.end(), gt_n());
    for (const auto &i : heap) {
        printf("%s\n%s\n", std::get<1>(i).c_str(), std::get<2>(i).c_str());
    }
}