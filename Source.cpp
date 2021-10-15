#include <iostream>

#include "ScriptParser.h"


using namespace std;




int main()
{
	ScriptParser parser("modeldata3.txt");


	parser.Parse();


	system("pause");
	return 0;
}