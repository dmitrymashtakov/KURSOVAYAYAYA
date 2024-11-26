//Модули
#include "communicator.h"
#include "log.h"
#include "error.h"
#include "calc.h"

//Сетевое взаимодействие
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

//Для хеширования
#include <sstream>
#include <cryptopp/hex.h>
#include <cryptopp/base64.h>
#include <cryptopp/sha.h>

//Буст библиотеки для генерации SALT
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/variate_generator.hpp>

#define buff_size 1024

std::unique_ptr<char[]> buff(new char[buff_size]);
std::string communicator::sha224(std::string input_str)
{
    using namespace CryptoPP;
    SHA224 hash;
    std::string new_hash;
    StringSource(input_str, true,
                 new HashFilter(hash, new HexEncoder(new StringSink(new_hash))));
    return new_hash;
}
std::string communicator::generate_salt()
{
    time_t now = time(0);
    boost::mt19937 gen(now);
    boost::random::uniform_int_distribution<uint64_t> dist(0,std::numeric_limits<uint64_t>::max());
    boost::variate_generator<boost::mt19937&, boost::random::uniform_int_distribution<uint64_t>> getRand(gen, dist);
    std::stringstream s;
    s << std::hex << dist(gen);
    std::string results(s.str());
    while(results.length()<16) {
        results = '0' + results;
    }
    return results;
}
int communicator::connection(int port,std::map<std::string,std::string> base,logger* l)
{
    try {
        int queue_len = 100;
        sockaddr_in * addr = new (sockaddr_in);
        addr->sin_family = AF_INET;
        addr->sin_port = htons(port);
        inet_aton("127.0.0.1", &addr->sin_addr);
        int s = socket(AF_INET, SOCK_STREAM, 0);
        if (s<=0) {
            throw crit_err("ОШИБКА СОЗДАНИЯ СОКЕТА. КРИТИЧЕСКАЯ ОШИБКА");
        } else {
            l->writelog("Сокет создан");
        }
        auto rc = bind(s,(const sockaddr*)addr,sizeof(sockaddr_in));
        if (rc == -1) {
            throw crit_err("ОШИБКА ПРИВЯЗКИ СОКЕТА. КРИТИЧЕСКАЯ ОШИБКА");
        } else {
            l->writelog("Привязка сокета успешна");
        }
        rc = listen(s,queue_len);
        if(rc ==-1) {
            throw crit_err("ОШИБКА ПРОСЛУШКИ СОКЕТА. КРИТИЧЕСКАЯ ОШИБКА");
        }
        for(;;) {
            try {
                sockaddr_in * client_addr = new sockaddr_in;
                socklen_t len = sizeof (sockaddr_in);
                int work_sock = accept(s, (sockaddr*)(client_addr), &len);
                if(work_sock <= 0) {
                    throw no_crit_err("Ошибка сокета");
                }
                l->writelog("Сокет создан");
                rc = recv(work_sock,buff.get(),buff_size,0);
                if(rc <= 0) {
                    close(work_sock);
                    throw no_crit_err("Ошибка получения ID");
                }
                l->writelog("ID от клиента получен");
                buff[rc]=0;
                std::string ID(buff.get(),rc);
                if(base.find(ID)==base.end()) {
                    close(work_sock);
                    throw no_crit_err("Неизвестное ID");
                }
                std::string salt_s = generate_salt();
                rc = send(work_sock,salt_s.c_str(),16,0);
                if(rc<=0) {
                    close(work_sock);
                    throw no_crit_err("Ошибка отправки соли");
                }
                rc = recv(work_sock,buff.get(),56,0);
                if(rc<=0) {
                    close(work_sock);
                    throw no_crit_err("Ошибка получения хэша");
                }
                l->writelog("Хэш получен");
                buff[rc]=0;
                std::string client_hash(buff.get(),rc);
                if(sha224(salt_s+base[ID])!=client_hash) {
                    close(work_sock);
                    throw no_crit_err("Ошибка авторизации");
                }
                rc = send(work_sock,"OK",2,0);
                if(rc<=0) {
                    close(work_sock);
                    throw no_crit_err("Ошибка отправки ОК");
                }
                int count;
                rc = recv(work_sock,&count,sizeof count,0);
                if(rc<=0) {
                    close(work_sock);
                    throw no_crit_err("Не получено количество векторов");
                }
                l->writelog("Количество векторов получено");
                for(int i =0; i<count; i++) {
                    uint32_t vector_len;
                    rc = recv(work_sock,&vector_len,4,0);
                    if(rc<=0) {
                        close(work_sock);
                        throw no_crit_err("Не получена длина векторов");
                    }
                    std::unique_ptr<float[]> vector_data(new float[vector_len]);
                    rc = recv(work_sock,vector_data.get(),vector_len*sizeof(float),0);
                    if(rc<=0) {
                        close(work_sock);
                        throw no_crit_err("Вектор не получен");
                    }
                    if (rc / sizeof(float) != vector_len) {
    					close(work_sock);
    					throw no_crit_err("Полученные данные имеют некорректный размер");
					}
                    std::vector<float> v(vector_data.get(),vector_data.get()+vector_len);
                    std::unique_ptr<calc> c(new calc(v));
                    auto res = c.get()->send_res();
                    rc = send(work_sock,&res,sizeof res,0);
                    if(rc <= 0) {
                        close(work_sock);
                        throw no_crit_err("Результат не отправлен");
                    }
                    l->writelog("Результат отправлен");
                }
            } catch(no_crit_err& e) {
                l->writelog(e.what());
            }
        }
    } catch(crit_err& e) {
        l->writelog(e.what());
    }
    return 0;
}
