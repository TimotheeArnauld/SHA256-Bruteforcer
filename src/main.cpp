#include <string>
#include <iostream>
#include "sha256.h"  
#include "bruteforce.h"
 
using namespace std;

//Pour tester: ./bruteforcer e3b98a4da31a127d4bde6e43033f66ba274cab0eb7eb1c70ec41402bf6273dd8

int main(int argc, char *argv[]){
    if(argc != 2)
        cout << "" << endl;
    else{
        Bruteforce *bruteforce = new Bruteforce(argv[1]);
        bruteforce->start();
    }
    return 0;
}
