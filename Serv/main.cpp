#include <iostream>
#include "base.h"
#include "interface.h"
#include "communicator.h"
#include "calc.h"
#include "error.h"
#include "log.h"

int main(int argc, const char** argv) {
    interface z;
    try {
        if (!z.parser(argc, argv)) {
            return 1;
        }
        std::string basefile = z.get_base();
        std::string logfile = z.get_log();
        z.setup_connection(basefile, logfile);
    } catch (const crit_err& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return 1;
    } catch (const no_crit_err& e) {
        std::cerr << "Некритическая ошибка: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Неизвестная ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0; 
}
