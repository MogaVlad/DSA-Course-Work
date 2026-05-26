
#include <iostream>
#include "../include/Matrix.h"
#include "../include/ExtendedTest.h"
#include "../include/ShortTest.h"

using namespace std;


int main() {
	testAll();
	testAllExtended();
	cout << "Test End" << endl;
	return 0;
}