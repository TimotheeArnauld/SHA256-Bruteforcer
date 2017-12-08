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
        std::string dict;
        int dict_size;

        std::string hash_;
        int size;
        int nbCores;

        std::clock_t begin_time;

    public:
        Bruteforce(Datas d);
        ~Bruteforce();
  
        void start();
        bool generate(int);
        bool compare(std::string str);
        std::list<std::string> initialize_list();
};

#endif

