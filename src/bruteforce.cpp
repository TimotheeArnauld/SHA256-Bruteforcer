#include "bruteforce.h"

bool compare(std::string str);

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
	if(!list.empty()){
		if(this->size != 0){
			std::cout << "Enable processing for size:" << this->size << std::endl;
			generate(list, this->size);
		}else{
			int nbCores = 4;
			int max_size = 100;
			std::list<std::string> tmp[nbCores];

			for(int n = 1; n < max_size; n++){
				int s = list.size();
				std::list<std::string>::iterator it = list.begin();
				for(int i = 0; i < nbCores; i++){
					std::advance(it, s / nbCores);
					if(i == nbCores - 1){
						tmp[i].splice(tmp[i].begin(), list);
					}else{
						tmp[i].splice(tmp[i].begin(), list, list.begin(), it);
					}
				}

				for(int i = 0; i < nbCores; i++){
					list.splice(list.end(), generate(tmp[i], n));
					tmp[i].clear();
				}
				std::cout << "Password not found for size " << n << std::endl;
			}
		}
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

std::list<std::string> Bruteforce::generate(std::list<std::string> list_, int length) {
	for(std::list<std::string>::iterator l= list_.begin();std::string(*l).size() < length && l != list_.end(); l++){
		for(int j = 0; j < this->dict.size(); j++){
			list_.push_back((*l + this->dict[j]));
			if(compare((*l + this->dict[j]))){
				std::cout << "Password found:" << (*l + this->dict[j]) << std::endl;
				std::cout << "Duration: " << float(std::clock() - this->begin_time) / CLOCKS_PER_SEC << "s" << std::endl;
				exit(0);
			}
			if(this->verbose) std::cout << "Tested: " << (*l + this->dict[j]) << std::endl;
		}
		list_.pop_front();
	}
	return list_;
}