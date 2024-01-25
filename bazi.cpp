#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>//baraye rand
#include <limits>
#include<thread> //baraye sleep
#include<chrono> //baraye sleep

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

using namespace std;

//baraye rangi shodan
#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define RED		"\033[31m"

void clearConsole(double seconds)//tabe  baraye taiine modat zamane pak shodane terminal
{
	std :: this_thread::sleep_for(std::chrono::duration<double>(seconds));
	system(CLEAR);
}
void TableCreation(vector<vector<int>>& table)//tabe shakhte jadval
{
    srand(time(0));

    int numRows = table.size();
    int numCols = table[0].size();
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
}

void printTable(const vector<vector<int>>& table, const vector<pair<int , int>>& path) //tabe namayeshe jadval 
{
    int numRows = table.size();
    int numCols = table[0].size();

    for(int i = 0 ; i < numRows ; i++) 
	{
        for(int j = 0 ; j < numCols ; j++) 
		{
			bool isPath = false;
			for(const auto& point : path)
			{
            	if(point.first ==  i && point.second == j)
            	{
            		isPath = true;
            		break;
				}
			}
			if(isPath)//namayeshe khane haye masire karbar be range abi
                cout << BLUE << table[i][j] << "\t" << RESET;
            else if(i == numRows - 1 && j == numCols - 1)//namayeshe khane akhar be range ghermez
            	cout << RED << table[i][j] << RESET ;
			else
                cout << table[i][j] << "\t";

        }
        cout << endl;
    }
}

bool movePlayer(int& row, int& col, char direction, vector<vector<int>>& table , vector<pair<int , int>>& path) 
{
    int numRows = table.size();
    int numCols = table[0].size();

    int newRow = row;
    int newCol = col;

    switch(direction) 
	{
        case 'w':
            if (row > 0) 
                --newRow;
            break; 
            
        case 's':
            if (row < numRows - 1)
                ++newRow;
            break;
            
        case 'a':
            if (col > 0) 
                --newCol;
            break;
            
        case 'd':
            if (col < numCols - 1)
                ++newCol;
            break;
            
        default :
        	cout << "your move is wrong!Pleas letter among w , s , d , a." << endl;
    }
    if(newRow >= 0 && newRow < numRows && newCol >= 0 ; newCol < numCols && table[newRow][newCol] != 0) 
	{
        row = newRow;
        col = newCol;
        path.push_back({row , col});//ezafe kardane khane be masire karbar
        return true;
    }

    return false;
}

int main() 
{
    int numRows, numCols;

    cout << "Enter the number of rows: ";//gereftane tedade satr
    cin >> numRows;

    cout << "Enter the number of columns: ";//gereftane tedade sotoon
    cin >> numCols;
    
   
    int pathLength = numRows + numCols - 1;//tole masir = x + y - 1

    vector<vector<int>> gameTable(numRows, vector<int>(numCols));
    
    TableCreation(gameTable);

    int playerRow = 0;//khane shro
    int playerCol = 0;//khane shoro
	vector<pair<int , int>>path;
	path.push_back({playerRow , playerCol});
	
    while(true) 
	{
        printTable(gameTable,path);

        char move;
        cout << "Enter your move :" << endl;
        cout << "w : up , a : left , s : down , d : right" << endl;
        cin >> move;

        if(movePlayer(playerRow, playerCol, move, gameTable , path)) //agar true bood
		{
            if(playerRow == numRows - 1 && playerCol == numCols - 1) //agar be khane akhar resid
			{
				int sumOfpath = 0;
				for(int i = 0 ; i < path.size() ; i++)
				{
					sumOfpath += gameTable[path[i].first][path[i].second];
				}
				sumOfpath = sumOfpath - gameTable[numRows - 1][numCols - 1];//jame khane haye toole masire karbar
				if(path.size() == pathLength && sumOfpath == gameTable[numRows - 1][numCols -1])//agar jame khane ha barabar ba khane akhar bood va tole masir barabar ba x + y - 1 bood
                	cout << "Congratulations! You Win :)" << endl;
                else
                	cout << "I'm sorry . you lost!" << endl;
                
               break;
            }
        } 
		else//agar false bood
            cout << "Invalid move. Try again." << endl;
           clearConsole(0.7);//update va pak kardane terminal har 0.7 saniye yek bar
    }

    return 0;
}