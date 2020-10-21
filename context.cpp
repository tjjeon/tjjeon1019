#include <string>
#include "context.h"


std::string Context::toString() const {
    return function + "," + std::to_string(line);
}