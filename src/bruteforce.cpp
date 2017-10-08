#include "bruteforce.h"

Bruteforce::Bruteforce(string hash){
	dict = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789";
    dict_size = dict.length();
    this->hash_ = hash;
    int max_size = 100;
}

void Bruteforce::start(){
	for(int i = 0; i < max_size; i++){
		char *str = (char*)malloc(i);
		generate(str, i);    
		free(str);
    }

}

void Bruteforce::generate(char *str, int max){
	for(int j = 0; j < dict_size; j++){
		str[0] = dict.at(j);
		if(compare(sha256(str))){
			cout << str << ": Passphrase found" << endl;
            exit(0);
		}else{
			cout << str << ": Failed" << endl;
        }
	}
}

bool Bruteforce::compare(string str){
	return (this->hash_ == str);
}