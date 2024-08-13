// 13/08/2024 Koneko Prod.
//
// For this module only:
// This code is public domain. No change sufficient enough to constitute a
// significant or original work has been made, and thus it remains as such.
//
//
// DESCRIPTION:
//
// Implementation of POSIX opendir for Visual C++.
// Derived from the MinGW C Library Extensions Source (released to the
//  public domain).
//

// * Includes
#include <iostream>
#include "hz.hpp"
// * Namespaces and classes
using namespace std;
Display disp;
Config cc;	

int main()
{  
	// * Main works
	disp.GetInfoDisplay();
	system("pause");
	cout << " Wait";
	Sleep(500);
	for (int i{ 0 }; i < 3; i++) {
		Sleep(500);
		cout << ".";
	}
	cout << endl;

	disp.CreateDisplaySettings();
	cc.CheckVideo();
	cout << " Create the config";

	// * Timer
	Sleep(200);
	for (int i{ 0 }; i < 3 ; i++) {
		Sleep(400);
		cout << ".";
	}
	cout << endl << " Complete." << endl;;

	cc.CreateConfig();

	system("pause");
	return EXIT_FAILURE;
}
