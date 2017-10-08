#include "bruteforce.h"

Bruteforce::Bruteforce(string hash){
	dict = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789";
    dict_size = dict.length();
    this->hash_ = hash;
}

void Bruteforce::start(){
	for(int i = 0; i < max_size; i++){
		generate("", i);    
    }

}

void Bruteforce::generate(string str, int max){
	for(int j = 0; j < dict_size; j++){
		str = dict[j];
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