//ClientProgram.cpp

#include "Two34Tree.h"
#include "Exception.h"
#include <string>
#include <fstream>
using namespace std;

int main()
{
	Two34Tree tree;
    Key newKey;
	
	while((not(newKey == -2)))
	{
		
		cin >> newKey;
		
		tree.insert(newKey);
		tree.display(cout, 'p');
		cout << "Bottom of loop" << endl;
	}
	
return 0;
}