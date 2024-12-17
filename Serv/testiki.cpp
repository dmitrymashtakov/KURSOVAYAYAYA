#include <chrono>
#include <UnitTest++/UnitTest++.h>
#include <filesystem>
#include <fstream>
#include <boost/numeric/conversion/cast.hpp>
#include <limits>
#include <thread>
#include <sstream>
#include "log.h"
#include "communicator.h"
#include "calc.h"
#include "base.h"
#include "interface.h"
#include "error.h"

namespace po = boost::program_options;
SUITE(InterfaceTests) {

TEST(hParameter) {
        interface iface;
        const char* argv[] = {"program", "-h"};
        int argc = sizeof argv / sizeof nullptr - 1;
        bool res = iface.parser(argc, argv);
        CHECK_EQUAL(1, res);
    }
TEST(helpParameter) {
        interface iface;
        const char* argv[] = {"program", "--help"};
        int argc = sizeof argv / sizeof nullptr - 1;
        bool res = iface.parser(argc, argv);
        CHECK_EQUAL(1, res);
    }
TEST(hWithOtherParameter) {
        interface iface;
        const char* argv[] = {"program", "-p", "12345", "-h"};
        int argc = sizeof argv / sizeof nullptr - 1;
        bool res = iface.parser(argc, argv);
        CHECK_EQUAL(1, res);
    }

TEST(Port1Valid) {
    interface iface;
    const char* argv[] = {"program", "-p", "33333"};
    CHECK(iface.parser(3, argv));
    CHECK_EQUAL(iface.get_port(), 33333);
}

TEST(Port2Valid) {
    interface iface;
    const char* argv[] = {"program", "--port", "33333"};
    CHECK(iface.parser(3, argv));
    CHECK_EQUAL(iface.get_port(), 33333);
}
TEST(Port3Valid) {
    interface iface;
    const char* argv[] = {"program", "--port", "33334"};
    CHECK(iface.parser(3, argv));
    CHECK_EQUAL(iface.get_port(), 33334);
}

TEST(PortInvalid) {
    interface iface;
    const char* argv[] = {"program", "-p", "70000"};
    CHECK_THROW(iface.parser(3, argv), crit_err);
}

TEST(Base1FileOption) {
    interface iface;
    const char* argv[] = {"program", "-b", "base.txt"};
    CHECK(iface.parser(3, argv));
}

TEST(Base2FileOption) {
    interface iface;
    const char* argv[] = {"program", "--basefile", "base.txt"};
    CHECK(iface.parser(3, argv));
}

TEST(BaseFileNoValue) {
    interface iface;
    const char* argv[] = {"program", "-b"};
    CHECK_THROW(iface.parser(2, argv), po::invalid_command_line_syntax);
}

TEST(LogFile1Option) {
    interface iface;
    const char* argv[] = {"program", "-l", "log.txt"};
    CHECK(iface.parser(3, argv));
}

TEST(LogFile2Option) {
    interface iface;
    const char* argv[] = {"program", "--logfile", "log.txt"};
    CHECK(iface.parser(3, argv));
}

TEST(LogFileNoValue) {
    interface iface;
    const char* argv[] = {"program", "-l"};
    CHECK_THROW(iface.parser(2, argv), po::invalid_command_line_syntax);
}

TEST(MultipleOptionsNoValues) {
    interface iface;
    const char* argv[] = {"program", "-p", "-b"};
    CHECK_THROW(iface.parser(3, argv), po::invalid_command_line_syntax);
}

TEST(MultipleOptionsWithValues) {
    interface iface;
    const char* argv[] = {"program", "-p", "33334", "-b", "base.txt", "-l", "log.txt"};
    CHECK(iface.parser(7, argv));
}

TEST(InvalidOption) {
    interface iface;
    const char* argv[] = {"program", "-z"};
    CHECK_THROW(iface.parser(2, argv), po::unknown_option);
}

TEST(NoParameters) {
    interface iface;
    const char* argv[] = {"program"};
    CHECK(iface.parser(1, argv));
}
}

SUITE(base_file){
	TEST(no_tochka_in_base_path)
	{ 
		base Con;
		std::string path = "test_files/basetxt";
		CHECK_THROW(Con.connect(path),crit_err);
	}
	TEST(empty_path){
		base Con;
		std::string path = "";
		CHECK_THROW(Con.connect(path),crit_err);
	}
	TEST(wrong_path){
		base Con;
		std::string path = "/ZZZ/base.txt";
		CHECK_THROW(Con.connect(path),crit_err);
	}
	TEST(login_plus_pass){
		base Con;
		std::string check_pass = "pswd";
		std::string check_login = "login";
		std::string path = "base.txt";
		Con.connect(path);
		if((Con.get_data()[check_login]!= check_pass) or (Con.get_data().find(check_pass)==Con.get_data().end())){
			CHECK(false);
		}else{
			CHECK(true);
		}
	}
	TEST(Empty_Base){
		base Con;
		std::string path = "test_files/base_empty.txt";
		CHECK_THROW(Con.connect(path),crit_err);
	}
	TEST(no_user_in_base){
		base Con;
		std::string check_login = "ZZZZZ";
		std::string path = "base.txt";
		Con.connect(path);
		CHECK_THROW(Con.get_data().at(check_login), std::out_of_range);
	}
	TEST(login_only) {
    	base Con;
    	std::string check_login = "login";
    	std::string path = "base.txt";
    	Con.connect(path);
    	if(Con.get_data().find(check_login) != Con.get_data().end()) {
        	CHECK(true);
    	} else {
        	CHECK(false);
    	}
}
TEST(pass_only) {
    base Con;
    std::string check_pass = "pswd";
    std::string path = "base.txt";
    Con.connect(path);
    
    if(Con.get_data().find(check_pass) != Con.get_data().end()) {
        CHECK(true);
    } else {
        CHECK(false);
    }
}
TEST(invalid_base){
		base Con;
		std::string path = "test_files/invalid_base.txt";
		CHECK_THROW(Con.connect(path), crit_err);
	}
}

SUITE(Log_file){

TEST(TestWriteLogToFile) {
    logger log;
    std::string path = "/home/stud/KURSOVAYAYAYA/Serv/log.txt";
    std::string message = "Тест записи в журнал";
    log.set_path(path);
    log.writelog(message);
    std::ifstream log_file(path);
    CHECK(log_file.is_open());
    std::string log_content;
    std::getline(log_file, log_content);
    CHECK(log_content.find(message));
    log_file.close();
}

int main() {
    return UnitTest::RunAllTests();
}
	TEST(wrong_path){
		logger l;
		std::string path = "ZZZ/file.txt";
		CHECK_THROW(l.set_path(path),crit_err);
	}
	TEST(correct_path){
		logger l;
		std::string path = "test_files/log.txt";
		CHECK_EQUAL(0,l.set_path(path));
	}
	TEST(no_tochka_in_log){
		logger l;
		std::string path = "test_files/loglog\n";
		CHECK_THROW(l.set_path(path),crit_err);
	}
	TEST(empty_path_log){
		logger l;
		std::string path = "";
		CHECK_THROW(l.set_path(path),crit_err);
	}
}

SUITE(Calculator_test){
	TEST(negative_number_1){
		std::vector<float> v ={9.6,-5.2,2.6,3,0};
		calc c(v);
		CHECK_EQUAL(2,c.send_res());
	}
	TEST(empty_vector){
		std::vector<float> v = {};
		CHECK_THROW(calc c(v), no_crit_err);
	}
	TEST(ProcessVector_LargeInput) {
    std::vector<float> v(1000000, 1); 
    calc c(v);
    float result = c.send_res();
    CHECK_EQUAL(1, result); 
    
}
}


SUITE(communicator_test){
	TEST(salt_generator){
		communicator a;
		std::string s1 = a.generate_salt();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::string s2 = a.generate_salt();
		if(s1 == s2){
			CHECK(false);
		}
		else{
		CHECK(true);
		}
	}
	TEST(salt_len){
		communicator a;
		std::string s = a.generate_salt();
		CHECK_EQUAL(s.length(),16);
	}
	TEST(sha224_gen){
		std::string hash_check = "CEEBAFDF23B30EF786B4A9F72ADF901648BA04AD8EA24D03ECED28E2";
		communicator a;
		std::string SALT = "3e74235568ba8f1e";
		std::string hash = a.sha224(SALT);
		CHECK_EQUAL(hash,hash_check);
	}
	TEST(empty_gen){
		std::string hash_check = "D14A028C2A3A2BC9476102BB288234C415A2B01F828EA62AC5B3E42F";
		communicator a;
		std::string SALT = "";
		std::string hash = a.sha224(SALT);
		CHECK_EQUAL(hash,hash_check);
	}
	TEST(sha224_gen_pswd){
		std::string hash_check = "3A22EEF89BF7AC5AC462309D08CACFC199DEC5418FD87EB4FBD65076";
		communicator a;
		std::string pswd = "P@ssW0rd";
		std::string SALT = "3e74235568ba8f1e";
		std::string hash = a.sha224(SALT+pswd);
		CHECK_EQUAL(hash,hash_check);
	}
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
