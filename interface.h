#pragma once
#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include "log.h"
#include "base.h"
#include "communicator.h"
#include "error.h"

class interface {
    int port;

public:
    interface() : port(33333) {}
    bool parser(int argc, const char** argv);
    void setup_connection(const std::string& basefile, const std::string& logfile);
    void spravka(const boost::program_options::options_description& opts);
    int get_port() const { return port; }
};
