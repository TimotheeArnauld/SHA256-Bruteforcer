#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <string>
#include <iostream>
#include <list>
#include <ctime>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>

#include "sha256.h"
#include "parseargs.h"

class Bruteforce{
    private:
        std::string dict;

        std::string hash_;
        int size;
        int nbCores;
        bool verbose;
        std::mutex mutex;

        struct timespec begin, finish;
        double elapsed;

    public:
        Bruteforce(Datas d);
        ~Bruteforce();
  
        void start();
        void generate(int, std::atomic_bool& isFound, int, int);
        bool compare(std::string);
        void initialize_list();
        void recursive_generate(std::string, int, std::atomic_bool& isFound, int, int);
};

#endif
