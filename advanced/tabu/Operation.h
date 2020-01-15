//
// Created by wojtek on 08/12/2019.
//

#ifndef ADVANCED_OPERATION_H
#define ADVANCED_OPERATION_H

#include <string>

enum OperationEnum {
    InsertOperation,
    SwapOperation
};

class Operation {
public:
    OperationEnum type;
    size_t p1;
    long id1;
    size_t p2;
    long id2;
    long remainingTime;

    Operation() = default;
    Operation(OperationEnum type, size_t pos1, long id1, size_t pos2, long id2, long remainingTime);

    std::string getKey();

};

bool operator == (const Operation &lhs, const Operation &rhs);


#endif //ADVANCED_OPERATION_H
