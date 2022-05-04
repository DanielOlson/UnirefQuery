//
// Created by Olson, Daniel (NIH/NIAID) [E] on 5/3/22.
//

#include "UnirefHeap.h"
#include <fstream>


int UnirefHeap::ProcessTuple(std::tuple<int, std::string, std::string>tup) {
    int n = std::get<0>(tup);
    if (heap.size() < heap_size) {
        heap.push(tup);
    }

    else if (n > std::get<0>(heap.top())){
        heap.push(tup);
        heap.pop();
    }
    return 0;
}

int nForHeader(const std::string &header) {
    int state = 0;
    int n = 0;
    for (int i = 0; i < header.size(); ++i) {
        if (state == 0) {
            if (header[i] == 'n')
                state = 1;
        }

        else if (state == 1) {
            if (header[i] == '=')
                state++;
            else
                state = 0;
        }

        else {
            int c = header[i] - '0';
            if (c >= 0 && c <= 9)
                n = (n * 10) + c;
            else
                break;

        }
    }

    return n;
}

void UnirefHeap::ReadFile(std::string file_path) {
    std::ifstream file(file_path, std::ifstream::in);

    std::string header_line = "";
    int n = 0;
    std::string seq = "";

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.length() > 0) {

                if (line[0] == '>') {
                    if (seq.length() > 0 && seq.length() < max_seq_len) {
                        ProcessTuple(std::make_tuple(n, header_line, seq));
                    }

                    header_line = line;
                    n = nForHeader(header_line);
                    seq = "";
                }

                else {
                    for (int i = 0; i < line.length(); ++i) {
                        char c = line[i];
                        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
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

    while (heap.size() > 0) {
        auto i = heap.top();
        printf("%s\n%s\n", std::get<1>(i).c_str(), std::get<2>(i).c_str());
        heap.pop();
    }

}