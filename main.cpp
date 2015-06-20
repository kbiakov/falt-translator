#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <exception>
#include <stdexcept>
#include "trans.h"

using namespace std;

int main() {
    cout << endl;
    cout << "Translated C-program: " << endl;
    cout << endl;
    // cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    cout << endl;

	progCpp programCpp;
	programCpp.open("example.txt");
	programCpp.translate();
	programCpp.save("example.cpp");
	// cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << endl;

    cout << "Translated Pascal-program: " << endl;
    cout << endl;
    // cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
    cout << endl;

	progPas programPas;
	programPas.open("example.txt");
	programPas.translate();
	programPas.save("example.pas");
	// cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	cout << endl;

	return 0;
}
