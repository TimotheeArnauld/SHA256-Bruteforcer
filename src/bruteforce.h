#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <string>
#include <iostream>
#include "sha256.h"

using namespace std;

class Bruteforce{
    private:
        string dict;
        int dict_size;
        static const int max_size = 1;
        string hash_;

    public:
        Bruteforce(string hash);
        ~Bruteforce();
  
        void start();
        void generate(char *, int);
        bool compare(string str);
};

#endif

