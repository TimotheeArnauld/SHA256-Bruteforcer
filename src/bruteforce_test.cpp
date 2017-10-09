#include <cppunit/ui/text/TestRunner.h>
#include <iostream>
#include "bruteforce.h"

class BruteforceTest : public CppUnit::TestCase { 


  void should_find_same_hash(){
  	string hash1 = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";
  	Bruteforce *bruteforce = new Bruteforce(hash1);
  	CPPUNIT_ASSERT_EQUAL( bruteforce->compare(hash1), true );
  }
    

};

int main(int argc, char *argv[]){

	CppUnit::TextUi::TestRunner runner;
  	runner.addTest(BruteforceTest::should_find_same_hash() );
  	runner.run();
}