#include "bruteforce.h"

Bruteforce::Bruteforce(string hash){
	dict = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789";
    dict_size = dict.length();
    this->hash_ = hash;
}

void Bruteforce::start(){
	int max_size = 100;

	for(int n = 0; n < max_size; n++){
		char *str = (char*)malloc(n);
		generate(str, n);    
		free(str);
    }

}

void Bruteforce::generate(char *str, int i){
  if(i==-1){
    return;
  }
	for(int j = 0; j < dict_size; j++){
		str[i] = dict.at(j);
		if(compare(sha256(str))){
			cout << str << ": Passphrase found" << endl;
            exit(0);
		}else{
			cout << str << ": Failed" << endl;
			generate(str, i-1);
        }
	}
  }

bool Bruteforce::compare(string str){
	return (this->hash_ == str);
}


