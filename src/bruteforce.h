#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <string>
#include <iostream>
#include <list>
#include <ctime>
#include "sha256.h"

class Bruteforce{
    private:
        std::string dict;
        int dict_size;
        static const int max_size = 1;
        std::string hash_;
        std::clock_t begin_time;

    public:
        Bruteforce(std::string hash);
        ~Bruteforce();
  
        void start();
        bool generate(int);
        bool compare(std::string str);
        std::list<std::string> initialize_list();
};

#endif

