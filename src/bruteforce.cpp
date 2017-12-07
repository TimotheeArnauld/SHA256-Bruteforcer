#include "bruteforce.h"

Bruteforce::Bruteforce(std::string hash){
	dict = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789";
    dict_size = dict.length();
    this->hash_ = hash;
    this->begin_time = std::clock();
}

void Bruteforce::start(){
	int max_size = 100;
	for(int n = 1; n < max_size && !generate(n); n++);
	std::cout << "Duration: " << float(std::clock() - this->begin_time) / CLOCKS_PER_SEC << "s" << std::endl;
}

std::list<std::string> Bruteforce::initialize_list(){
	std::list<std::string> list;
	for(int i = 0; i < this->dict.size(); i++)
		list.push_back(std::string(1, this->dict[i]));
	return list;
}

bool Bruteforce::compare(std::string str){
		return (this->hash_.compare(sha256(str)) == 0)?true:false;
}

bool Bruteforce::generate(int length) {
	std::list<std::string> list = initialize_list();
	for(std::list<std::string>::iterator l= list.begin();std::string(*l).size() < length && l != list.end(); l++){
		for(int j = 0; j < this->dict.size(); j++){
			list.push_back((*l + this->dict[j]));
			if(compare(*l + this->dict[j])){
				std::cout << "Password found:" << (*l + this->dict[j]) << std::endl;
				return true;
			}
		}
		list.pop_front();
	}
	std::cout << "Password not found for size " << length << std::endl;
	return false;
}