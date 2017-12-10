#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <string>
#include <iostream>
#include <list>
#include <ctime>

#include "sha256.h"
#include "parseargs.h"

class Bruteforce{
    private:
        std::list<std::string> list;
        std::string dict;
        int dict_size;

        std::string hash_;
        int size;
        int nbCores;
        bool verbose;

        std::clock_t begin_time;
        bool found;

    public:
        Bruteforce(Datas d);
        ~Bruteforce();
  
        void start();
        std::list<std::string> generate(std::list<std::string>, int);
        bool compare(std::string);
        std::list<std::string> initialize_list();
};

#endif

