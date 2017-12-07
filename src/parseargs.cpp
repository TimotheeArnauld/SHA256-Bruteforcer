#include "parseargs.h"

ParseArgs::ParseArgs(int argc, char **argv){
	Flags f;
	while ((f.c = getopt (argc, argv, "vht:s:c:l:c:")) != -1){
		switch (f.c)
		{
			case 'v':
			f.vflag = 1;
			break;
			case 't':
			f.tvalue = optarg;
			break;
			case 's':
			f.svalue = optarg;
			break;
			case 'c':
			f.cvalue = optarg;
			break;
			case 'l':
			f.lvalue = optarg;
			break;
			case 'h':
			show_usage();
			break;
			case '?':
			if (optopt == 't' || optopt == 's' || optopt == 'c' || optopt == 'l'){
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
			}
			else if (isprint (optopt)){
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			}
			else{
				fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
			}
			default:
			abort ();
		}
	}
}

ParseArgs::~ParseArgs(){

}

void ParseArgs::show_usage(){
	std::cout << "hello world" << std::endl;
}