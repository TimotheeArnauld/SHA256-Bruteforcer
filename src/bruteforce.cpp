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
	for(int i = 0; i < this->dict.size(); i++)
		list.push_back(std::string(1, this->dict[i]));
	if(compare()){
		list.clear();
		return list;
	}
	return list;
}

bool Bruteforce::compare(){
	for(std::list<std::string>::iterator l = this->list.begin(); l != this->list.end(); l++){
		if(this->verbose)
			std::cout << "Tested: " << *l << std::endl;
		if(this->hash_.compare(sha256(*l)) == 0){
			std::cout << "Password found:" << (*l) << std::endl;
			return true;
		}
	}
	return false;
}

bool Bruteforce::generate(int length) {
	if(this->list.empty()) return true;
	for(std::list<std::string>::iterator l = this->list.begin();std::string(*l).size() < length && l != this->list.end(); l++){
		for(int j = 0; j < this->dict.size(); j++){
			list.push_back((*l + this->dict[j]));
		}
		this->list.pop_front();
	}
	if(compare()) return true;
	std::cout << "Password not found for size " << length << std::endl;
	return false;
}