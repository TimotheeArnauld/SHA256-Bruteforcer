#ifndef PARSEARGS_H
#define PARSEARGS_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <string>

#include "sha256.h"

struct Flags
{
	int vflag;
	int t;
	int s;
	int c;
	int l;
	char* tvalue;
	char* svalue;
	char* cvalue;
	char* lvalue;
};

struct Datas{
	int nbCores;
	std::string hash;
	bool letsgo;
};

class ParseArgs{
private:
	int nargs;
	char** vargs;
	Flags f;
	Datas d;

public:
	ParseArgs(int, char**);
	Datas parse();
	~ParseArgs();

	void show_usage();
};

#endif

