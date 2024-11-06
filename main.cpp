#include <iostream>
#include "base.h"
#include "interface.h"
#include "communicator.h"
#include "calc.h"
#include "error.h"
#include "log.h"

int main(int argc,const char** argv)
{
    interface z;
    z.comm_proc(argc,argv);
    return 0;
}
