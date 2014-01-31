#include <iostream>

using namespace std;

#include "division.h"

int main(int argc, const char* argv[])
{
	int first, second;	
	
	
	cout << "Pass two integers" << endl;
	cout << "Nominator: ";
	cin >> first;
	cout << "Denominator: ";
	cin >> second;	
	
	cout << "Result: " << Division::divide(first, second) << endl;
	return 0;
}

