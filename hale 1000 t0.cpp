#include <iostream>
#include <vector>
#include<ctime>
#include<cstdlib>
#include<windows.h>

using namespace std;
#define BLUE_TEXT "\033[1;34m"
#define DEFAULT_COLOR "\033[0m"
void generatePath(int rows, int cols)
{
  	//sakhtane mavane 
  	srand(time(0));
    vector<vector<int>> table(rows, vector<int>(cols , 5));
    int sum = 0;
    //por kardane khanehaye masir
    for(int i = 0 ; i < rows ; i++)
    {
    	int RandNumber = rand() % 7 - 3;
		while(RandNumber == 0)
			RandNumber = rand() % 7 - 3;
		table[i][0] = RandNumber;
		sum = sum + table[i][0];
	}
    for(int j = 1 ; j < cols - 1 ; j++)
	{		
		int RandomNumber = rand() % 7 - 3;
		while(RandomNumber == 0)
			RandomNumber = rand() % 7 - 3;
		table[rows - 1][j] = RandomNumber;
		sum = sum + table[rows - 1][j];
	}
	table[rows - 1][cols - 1] = sum;
	
	
	//sakhte mane ba 0
    int zeros = rand() % 4 + 2;
    for(int i = 0 ; i < zeros ; i++)
  	{
    	int zeroX = rand() % rows;
    	int zeroY = rand() % cols;
    	while(zeroX == rows - 1 || zeroY == 0)
    	{
    		zeroX = rand() % rows;
    		zeroY = rand() % cols;
		}
    		table[zeroX][zeroY] = 0;
  	}
  	
  	//por kardane khanehaye digar be soorate random
    for(int i = 0 ; i < rows - 1  ; i++)
  	{
    	for(int j = 1 ; j < cols ; j++)
    	{
    		if(table[i][j] != 0)
    		{
      			int RandNumber = rand() % 7 - 3;
      			while(RandNumber == 0)
        			RandNumber = rand() % 7 - 3;  
        		table[i][j] = RandNumber;
    		}
    	}
    
  	}
    cout << "jadval : " << endl;
    for (int i = 0; i < rows; ++i) 
  	{
     	for (int j = 0; j < cols; ++j)
    	{
    		if(i == rows - 1)
    			cout << BLUE_TEXT << table[i][j] << " ";
    		else if(j == 0)
    			cout << BLUE_TEXT << table[i][j] << " ";
            else
            	cout << DEFAULT_COLOR << table[i][j] << " ";
        }
        cout << endl;
    }
    
  	
}
#define BLUE_TEXT "\033[1;34m"
#define DEFAULT_COLOR "\033[0m"
int main() 
{
    int rows , cols;
    cin >> rows >> cols;	
	generatePath(rows , cols);
	
    return 0;
}
