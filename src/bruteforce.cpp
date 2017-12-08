#include "bruteforce.h"

Bruteforce::Bruteforce(Datas d){
	dict = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789";
    dict_size = dict.length();

    this->hash_ = d.hash;
    this->nbCores = d.nbCores;
    this->size = d.size;
    this->verbose = d.verbose;

    this->begin_time = std::clock();
    list = initialize_list();
}

void Bruteforce::start(){
	if(this->size != 0){
		std::cout << "Enable processing for size:" << this->size << std::endl;
		generate(this->size);
	}else{
		int max_size = 100;
		for(int n = 1; n < max_size && !generate(n); n++);
	}
	std::cout << "Duration: " << float(std::clock() - this->begin_time) / CLOCKS_PER_SEC << "s" << std::endl;
}

std::list<std::string> Bruteforce::initialize_list(){
	std::list<std::string> list;
	for(int i = 0; i < this->dict.size(); i++){
		if(compare(std::string(1, this->dict[i]))){
			std::cout << "Password found:" << this->dict[i] << std::endl;
			list.clear();
			return list;
		}
		if(this->verbose) std::cout << "Tested: " << this->dict[i] << std::endl;
		list.push_back(std::string(1, this->dict[i]));
	}
	return list;
}

bool Bruteforce::compare(std::string str){
		return (this->hash_.compare(sha256(str)) == 0)?true:false;
}

bool Bruteforce::generate(int length) {
	if(this->list.empty()) return true;
	for(std::list<std::string>::iterator l= this->list.begin();std::string(*l).size() < length && l != this->list.end(); l++){
		for(int j = 0; j < this->dict.size(); j++){
			list.push_back((*l + this->dict[j]));
			if(compare(*l + this->dict[j])){
				std::cout << "Password found:" << (*l + this->dict[j]) << std::endl;
				return true;
			}
			if(this->verbose) std::cout << "Tested: " << (*l + this->dict[j]) << std::endl;
		}
		this->list.pop_front();
	}
	std::cout << "Password not found for size " << length << std::endl;
	return false;
}