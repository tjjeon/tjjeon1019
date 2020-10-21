#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <time.h>




class Context {
public:
    Context(const std::string& f, int l) : function(f), line(l) {}

    // foo:42
    std::string toString() const;

private:
    std::string function;
    int line;
};
