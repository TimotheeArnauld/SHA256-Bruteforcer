#include "bruteforce.h"

bool compare(std::string str);

Bruteforce::Bruteforce(Datas d){
	dict = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789";

    this->hash_ = d.hash;
    this->nbCores = d.nbCores;
    this->size = d.size;
    this->verbose = d.verbose;
}

void Bruteforce::start(){
	int max_size = 100;
	int nbThreads;

	std::atomic_bool isFound;
	isFound = false;
	if(this->nbCores != -1)
		nbThreads = this->nbCores;
	else 
		nbThreads = 5;

	std::thread threads[nbThreads];
	clock_gettime(CLOCK_MONOTONIC, &begin);

	for(int i = 1; !isFound && i < max_size; i++){
		int j = 0;
		for(int k = 0; j <  nbThreads; k += (dict.size() / nbThreads)){
			if(j == nbThreads - 1){
				threads[j] = std::thread(&Bruteforce::generate, this, i, std::ref(isFound), k, dict.size());
			}else{
				threads[j] = std::thread(&Bruteforce::generate, this, i, std::ref(isFound), k, k + (dict.size() / nbThreads) - 1);
			}
			
			j++;
		}
		for(int n = 0; n < nbThreads; n++){
			if(isFound){
				threads[n].detach();
			}else{
				threads[n].join();
			}
		}
		if(verbose && !isFound)
			std::cout << "No password for size: " << i << std::endl;
	}

	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - begin.tv_sec);
	elapsed += (finish.tv_nsec - begin.tv_nsec) / 1000000000.0;

	if(verbose){
		std::cout << "Duration: " << elapsed << "s" << std::endl;
	}
}

void Bruteforce::initialize_list(){
	std::list<std::string> list;
	for(int i = 0; i < this->dict.size(); i++){
		if(compare(std::string(1, this->dict[i]))){
			std::cout << this->dict[i] << std::endl;
			list.clear();
		}
		list.push_back(std::string(1, this->dict[i]));
	}
}

bool Bruteforce::compare(std::string str){
	return (this->hash_.compare(sha256(str)) == 0);
}

void Bruteforce::generate(int length, std::atomic_bool &isFound, int begin, int end) {
	if(!isFound){
		std::string str(length, dict.at(0));
		str.at(0) = dict.at(begin);
		recursive_generate(str, length, isFound, 0, end);
	}
}

void Bruteforce::recursive_generate(std::string str, int length, std::atomic_bool &isFound, int begin, int end){
	if(isFound) return;
  	bool finished = false;
  	bool flag = false;

  	if(compare(str)){
		std::cout << str << std::endl;
		isFound = true;
	}

	while(!isFound && !finished){
		for(unsigned int index = length - 1; !finished; index--){
			if(flag){
				if(index == -1){
					finished = true;
					continue;
				}
				if(str.at(index) == dict.at(end - 1)){
					flag = true;
					continue;
				}else{
					str.at(index) = dict.at(dict.find(str.at(index)) + 1 + begin);
					str.erase(str.begin() + index + 1, str.end());
					str.append(length - index - 1, dict.at(begin));
					index = length;
				}
			}else{
				if(str.at(index) == dict.at(end - 1)){
					flag = true;
					continue;
				}else{
					str.at(index) = dict.at(dict.find(str.at(index)) + 1 + begin);
					index = length;
				}
			}
			if(compare(str)){
				mutex.lock();
				std::cout << str << std::endl;
				isFound = true;
				mutex.unlock();
				return;
			}
		}
	}  	
}