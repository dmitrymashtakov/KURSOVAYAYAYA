#pragma once
#include "log.h"
#include <string>
class interface {
    int port;
public:
    interface(){}
    void comm_proc(int argc, const char** argv);
};
