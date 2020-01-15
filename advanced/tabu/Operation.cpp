//
// Created by wojtek on 08/12/2019.
//

#include "Operation.h"

Operation::Operation(OperationEnum type, size_t pos1, long id1, size_t pos2, long id2, long remainingTime) {
    this->type = type;
    this->p1 = pos1;
    this->p2 = pos2;
    this->id1 = id1;
    this->id2 = id2;
    this->remainingTime = remainingTime;
}

std::string Operation::getKey() {
    return std::to_string(type) + "-" + std::to_string(this->p1) + ":" + std::to_string(this->id1) + "-" + std::to_string(this->p2) + ":" + std::to_string(this->id2);
}

bool operator == (const Operation & lhs, const Operation & rhs) {
    return lhs.type == rhs.type && lhs.p1 == rhs.p1 && lhs.p2 == rhs.p2 && lhs.id1 == rhs.id1 && lhs.id2 == rhs.id2;
}
