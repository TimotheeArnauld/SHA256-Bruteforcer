#include <string>
#include <iostream>

#include "bruteforce.h"
#include "parseargs.h"

int main(int argc, char *argv[]){
	ParseArgs *parseargs = new ParseArgs(argc, argv);
	Datas d = parseargs->parse();

	if(d.letsgo){
		Bruteforce *bruteforce = new Bruteforce(d);
		bruteforce->start();
	}

    return 0;
}
