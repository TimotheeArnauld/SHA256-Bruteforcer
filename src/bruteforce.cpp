#include "bruteforce.h"

Bruteforce::Bruteforce(Datas d){
    dict = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789";
    dict_size = dict.length();

    this->hash_ = d.hash;
    this->nbCores = d.nbCores;
    this->verbose = d.verbose;

    this->begin_time = std::clock();
    list = initialize_list();
}

void Bruteforce::start(){
    std::atomic_bool isFound;
    isFound = false;
    //int nbCores = std::thread::hardware_concurrency() - 1;
    int nbCores = 1;
    int max_size = 100;
    bool areAllJoined = false;

    if(!list.empty()){
        isFound = false;
        for(int n = 1; n < max_size; n++){
            if(!isFound){
                std::vector<std::thread> threads;
                threads.reserve(nbCores);
                int s = list.size();
                std::list<std::string> tmp[nbCores];
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
                    threads.push_back(std::thread([&, n, i](){
                        generate(&tmp[i], n, isFound);
                    }));
                    if(threads.at(i).joinable()){
                            /*std::cout << "SIZE BEFORE " << threads.size() << std::endl;
                            std::cout << "THREAD NUMBER " << i << std::endl;*/
                            threads.at(i).join();
                            list.splice(list.end(), tmp[i], tmp[i].begin(), tmp[i].end());
                            areAllJoined = true;
                            threads.erase(threads.begin() + i);
                            //std::cout << "SIZE AFTER " << threads.size() << std::endl;
                        }else{
                            areAllJoined = false;
                        }
                }


                /*while(!areAllJoined){
                    for(int i = 0; i < threads.size(); i++){
                        if(threads.at(i).joinable()){
                            std::cout << "SIZE BEFORE " << threads.size() << std::endl;
                            std::cout << "THREAD NUMBER " << i << std::endl;
                            threads.at(i).join();
                            list.splice(list.end(), tmp[i], tmp[i].begin(), tmp[i].end());
                            areAllJoined = true;
                            threads.erase(threads.begin() + i);
                            std::cout << "SIZE AFTER " << threads.size() << std::endl;
                        }else{
                            areAllJoined = false;
                        }
                    }
                }*/
                //threads.clear();
            }
            std::cout << "Password not found for size " << n << std::endl;
        }
    }
    return;
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

void Bruteforce::generate(std::list<std::string> *list, int length, std::atomic_bool &isFound) {
    for(std::list<std::string>::iterator l= list->begin();std::string(*l).size() < length && l != list->end() && !isFound; l++){
        for(int j = 0; j < this->dict.size() && !isFound; j++){
            list->push_back((*l + this->dict[j]));
            if(compare((*l + this->dict[j]))){
                std::cout << "Password found:" << (*l + this->dict[j]) << std::endl;
                std::cout << "Duration: " << float(std::clock() - this->begin_time) / CLOCKS_PER_SEC << "s" << std::endl;
                isFound = true;
                exit(0);
            }
            if(this->verbose) std::cout << "Tested: " << (*l + this->dict[j]) << std::endl;
        }
        list->pop_front();
    }
}