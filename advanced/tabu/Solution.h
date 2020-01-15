//
// Created by wojtek on 27/11/2019.
//

#ifndef ADVANCED_SOLUTION_H
#define ADVANCED_SOLUTION_H

#include "../Machine.h"


class Solution {

public:

    static const int P = 4;

    std::vector<Machine> machines;
    std::vector<bool> dirty;

    Solution() = default;
    explicit Solution(std::vector<Machine> machines);

    unsigned long tardinessValue();

    Solution makeCopy();

    std::vector<Machine> & result();

    void insertTask(size_t machine_index, size_t position, Task task);
    void eraseTask(size_t machine_index, size_t position);

    void print();
};


#endif //ADVANCED_SOLUTION_H
