#include "parseargs.h"

ParseArgs::ParseArgs(int argc, char **argv){
	this->nargs = argc;
	this->vargs = argv;
	d.size = 0;
	d.nbCores = -1;
	d.verbose = false;
}

ParseArgs::~ParseArgs(){

}

Datas ParseArgs::parse(){
	while ((this->f.c = getopt (nargs, vargs, "vhs:c:c:")) != -1){
		switch (this->f.c)
		{
			case 'v':
			this->d.verbose = true;
			break;
			case 's':
			sscanf(optarg, "%d", &this->d.size);
			break;
			case 'c':
				std::cout << "The hash of " << optarg << " is: " << sha256(optarg) << std::endl;
				this->d.letsgo = false;
			break;
			case 'h':
				show_usage();
				this->d.letsgo = false;
			break;
			case '?':
			if (optopt == 't' || optopt == 's' || optopt == 'c' || optopt == 'l'){
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				std::cout << "-h to see usages" << std::endl;
				this->d.letsgo = false;
			}
			else if (isprint (optopt)){
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				std::cout << "-h to see usages" << std::endl;
				this->d.letsgo = false;
			}
			else{
				fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				std::cout << "-h to see usages" << std::endl;
				this->d.letsgo = false;
			}
			default:
			this->d.letsgo = false;
			abort ();
		}
	}
	for (int i = optind; i < nargs; i++){
		if(strlen(vargs[i]) == 64){
			this->d.hash = vargs[i];
			this->d.letsgo = true;
		}else if(strlen(vargs[i]) < 3){
			sscanf(vargs[i], "%d", &this->d.nbCores);
		}else{
			printf ("Non-option argument %s\n", vargs[i]);
			std::cout << "-h to see usages" << std::endl;
			this->d.letsgo = false;
		}
	}
	return d;
}

void ParseArgs::show_usage(){
	std::cout << "SHA256-Bruteforcer usages:" << std::endl;
	std::cout << "-h: display usages" << std::endl;
	std::cout << "-v SHA256_HASH: verbose mode" << std::endl;
	std::cout << "THREADS_NUMBER SHA256_HASH: launch on X threads" << std::endl;
	std::cout << "-c hello: give the SHA256 hash of 'hello'" << std::endl;
	std::cout << "SHA256_HASH: retrieve the passphrase" << std::endl;
}