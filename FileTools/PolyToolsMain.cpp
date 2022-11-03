#include <iostream>
#include "FileTools.h"
using namespace std;
using namespace POLY_TOOLS;

int main() {
	fs::path test("./test");

	Traverse printAll(Action::PRINT, "./");
	cout << "./ ";
	printAll.DepthFirstRecursive("./");

	return 0;
}
