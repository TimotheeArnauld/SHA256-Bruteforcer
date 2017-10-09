#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include "bruteforce.h"

class BruteforceTest : public CppUnit::TestFixture{ 
   public: void should_find_same_hash(){
  	string hash1 = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";
  	Bruteforce *bruteforce = new Bruteforce(hash1);
  	CPPUNIT_ASSERT( bruteforce->compare(hash1) == true );
  }
};

int main(int argc, char *argv[]){
	CppUnit::TestCaller<BruteforceTest> test( "should_find_same_hash", &BruteforceTest::should_find_same_hash);
	CppUnit::TestResult result;
	test.run(&result);
}