#include <iostream>
#include <vector>
#include<ctime>
#include<cstdlib>
#include<windows.h>

using namespace std;
//baraye rangi shodan
#define RESET   "\033[0m"
#define BLUE    "\033[34m"
void generatePath(int numRows, int numCols)
{
  	srand(time(0));
	vector<vector<int>> table(numRows, vector<int>(numCols));

    numRows = table.size();
    numCols = table[0].size();
	int numZero = rand() % 4 + 2;//tedade mavane be soorate random
	
	//porkardane khaneha be soorate random az -3 ta 3 be joz 0
	for(int i = 0 ; i < numRows ; i++)
	{
		for(int j = 0 ; j < numCols ; j++)
		{
			int Randomnumber = rand() % 7 - 3;
			while(Randomnumber == 0)
				Randomnumber = rand() % 7 - 3;
			table[i][j] = Randomnumber;
		}
	}
	
	//porkaradane khaneha be soorate random ba 0 as 2 ta 5 ta
	for(int i = 0 ; i < numZero ; i++)
	{
		int zeroRow , zeroCol;
		do{
			zeroRow = rand() % numRows;
			zeroCol = rand() % numCols;
		}while(zeroRow == numRows - 1 || zeroCol == 0);
		table[zeroRow][zeroCol] = 0;
	}
	
	//barabar ghararadadane khane akhar be majmoee khanehaye sotoone aval va radife akhar
	int sum = 0 ;
	for(int i = 0 ; i < numRows ; i++)
	{
		sum += table[i][0];
	}
	for(int j = 1 ; j < numCols - 1 ; j++)
	{
		sum += table[numRows - 1][j];
	}
	table[numRows - 1][numCols - 1] = sum;
	
	//namayeshe jale 1000 to
    cout << "Displaying the answer of game: " << endl;
    for (int i = 0 ; i < numRows ; ++i) 
  	{
     	for (int j = 0 ; j < numCols ; ++j)
    	{
    		if(i == numRows - 1)
    			cout << BLUE << table[i][j] << "\t";
    		else if(j == 0)
    			cout << BLUE << table[i][j] << "\t";
            else
            	cout << RESET << table[i][j] << "\t";
        }
        cout << endl;
    }
    cout << RESET;
    
  	
}
int main() 
{
     int numRows, numCols;

    cout << "Enter the number of rows: ";//gereftane tedade satr
    cin >> numRows;

    cout << "Enter the number of columns: ";//gereftane tedade sotoon
    cin >> numCols;	
    
	generatePath(numRows , numCols);
	
    return 0;
}
