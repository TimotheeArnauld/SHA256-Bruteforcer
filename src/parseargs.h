#ifndef PARSEARGS_H
#define PARSEARGS_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

class ParseArgs{
private:
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
		int index;
	};

public:
	ParseArgs(int, char**);
	~ParseArgs();

	void show_usage();
};

#endif

