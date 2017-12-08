#include "parseargs.h"

ParseArgs::ParseArgs(int argc, char **argv){
	this->nargs = argc;
	this->vargs = argv;
}

ParseArgs::~ParseArgs(){

}

Datas ParseArgs::parse(){
	while ((this->f.c = getopt (nargs, vargs, "vht:s:c:l:c:")) != -1){
		switch (this->f.c)
		{
			case 'v':
			this->f.vflag = 1;
			break;
			case 't':
			this->f.tvalue = optarg;
			break;
			case 's':
			this->f.svalue = optarg;
			break;
			case 'c':
				std::cout << "The hash of " << optarg << " is: " << sha256(optarg) << std::endl;
				this->d.letsgo = false;
				return this->d;
			break;
			case 'l':
			this->f.lvalue = optarg;
			break;
			case 'h':
				show_usage();
				this->d.letsgo = false;
				return this->d;
			break;
			case '?':
			if (optopt == 't' || optopt == 's' || optopt == 'c' || optopt == 'l'){
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				std::cout << "-h to see usages" << std::endl;
			}
			else if (isprint (optopt)){
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				std::cout << "-h to see usages" << std::endl;
			}
			else{
				fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				std::cout << "-h to see usages" << std::endl;
			}
			default:
			abort ();
		}
	}
	for (int i = optind; i < nargs; i++){
		if(strlen(vargs[i]) == 64){
			this->d.hash = vargs[i];
			this->d.letsgo = true;
			return d;
		}else{
			printf ("Non-option argument %s\n", vargs[i]);
			std::cout << "-h to see usages" << std::endl;
		}
	}
	this->d.letsgo = false;
	return d;
}

void ParseArgs::show_usage(){
	std::cout << "SHA256-Bruteforcer usages:" << std::endl;
	std::cout << "-h: display usages" << std::endl;
	std::cout << "-c hello: give the SHA256 hash of 'hello'" << std::endl;
	std::cout << "SHA256_HASH: retrieve the passphrase" << std::endl;
}