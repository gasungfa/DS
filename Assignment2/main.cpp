#include "Manager.h"

using namespace std;

int main() {
	Manager manager(3,5); //first value is threshold of fpgrowth, second value is order of bptree 
	manager.run("./command.txt");
	return 0;
}
