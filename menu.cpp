#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <windows.h>
using namespace std;

struct Maze
{
    string MapName;
    int rows;
    int cols;
    vector<vector<int>> map;
}currentMaze;
struct User {
    string username;
    int totalGames;
    int totalWins;
    time_t lastWinTime;
    int totalTime;
}info;

void SolveMaze( Maze& currentMaze);
void SaveMaze(Maze& currentMaze);
bool isDupNames(string name);
void Game(Maze& currentMaze);

void createMap()
{
    cout << "~ Create a new map" << endl;
    int rows, cols;
    cout << endl << "Enter the number of Rows: ";
    cin >> rows;
    currentMaze.rows = rows;
    cout << "Enter the number of Columns: ";
    cin >> cols;
    currentMaze.cols = cols;
    //Checking for duplicated names
    bool isD = false;
    while(!isD)
    {
    cout << "Enter the name of the Map: ";
    cin >> currentMaze.MapName;
    isD = isDupNames(currentMaze.MapName);
    }

    //making the map
    srand(time(0));
	vector<vector<int>>map(rows, vector<int>(cols));
	int numZero = rand() % 4 + 2;//tedade mavane be soorate random
	
	//porkardane khaneha be soorate random az -3 ta 3 be joz 0
	for(int i = 0 ; i < rows ; i++)
	{
		for(int j = 0 ; j < cols ; j++)
		{
			int randNum = rand() % 7 - 3;
			while(randNum == 0)
				randNum = rand() % 7 - 3;
			map[i][j] = randNum;
		}
	}
	//porkaradane khaneha be soorate random ba 0 as 2 ta 5 ta
	for(int i = 0 ; i < numZero ; i++)
	{
		int zeroRow , zeroCol;
		do{
			zeroRow = rand() % rows;
			zeroCol = rand() % cols;
		}while(zeroRow == rows - 1 || zeroCol == 0);
		map[zeroRow][zeroCol] = 0;
	}
	//barabar ghararadadane khane akhar be majmoee khanehaye sotoone aval va radife akhar
	int sum = 0 ;
	for(int i = 0 ; i < rows ; i++)
	{
		sum += map[i][0];
	}
	for(int j = 1 ; j < cols - 1 ; j++)
	{
		sum += map[rows - 1][j];
	}
	map[rows - 1][cols - 1] = sum;

    //saving the map in 'Maps' file
    currentMaze.map = map;
    SaveMaze(currentMaze);
    cout << endl << "The new Map was successfully created and you can see it in 'Maps' Folder!" << endl;
}
void loadmaze(int entry)
{
    //opening the names file
    ifstream NamesFile;
    NamesFile.open("Maps/MapNames.txt");
    if(!NamesFile.is_open())
    {
    cerr << "I can't open the 'MapNames' file." << endl;
    return;
    }
   //making a list of names
   string line;
   vector<string> names;
   while(getline(NamesFile, line))
       names.push_back(line);
   if(names.empty())
   {
       cout << "No maps found in the Folder." <<endl;
       return;
   }
   cout << "list of the maps: "<< endl;
   for(string each : names)
       cout << each << endl;
    //asking user's choice
    cout << "Enter the name of the Map: ";
    while(true)
    {
        string chosen;
        cin >> chosen;
        ifstream MapsFile;
        MapsFile.open("Maps/" + chosen + ".txt");

        if(!MapsFile.is_open())
        {
            cerr << "I can't open the '" << chosen <<"' file." << endl;
            return;
        }
            //reading the map
            currentMaze.MapName = chosen;
            int whichLine = 1, row=0, col=0;
            vector<vector<int>> map;
            while(getline(MapsFile, line))
            {
                if(whichLine == 6)
                {
                    vector<int> rows;
                    istringstream intn(line);
                    int num;
                    while (intn >> num)
                    {
                        rows.push_back(num);
                        row += 1;
                    }
                    map.push_back(rows);
                    col += 1;
                    whichLine = 5;
                }
                if(line == "=====================")
                {
                    currentMaze.cols = row/(col-1);
                    currentMaze.rows = col-1;
                }
                whichLine += 1;
            }
            currentMaze.map = map;
            break;
    }
    cout << "Who is Playing? ";
    cin >> info.username;
    if(entry == 2)
        Game(currentMaze);
    if(entry == 4)
        SolveMaze(currentMaze);
}
void UploadMap(int entry)
{
    //getting the address 
    address:
    cout << "Enter the address of the File: ";
    string FileAdd;
    cin >> FileAdd;
    ifstream CustMap(FileAdd);
    if(!CustMap.is_open())
    {
        cerr << "I can't open the File." << endl;
        return;
    }
   //reading the map
   string line;
   int num, whichLine = 1, row=0, col=0;
   vector<vector<int>> map;
    while(getline(CustMap, line)) 
    {
        if (line.find("Map Name:") != string::npos) 
        {
            currentMaze.MapName = line.substr(line.find(":") + 2);
            //Checking for duplicated names
            bool isD = isDupNames(currentMaze.MapName);
            if(!isD)
                goto address;
        }
        if(whichLine == 6)
        {
            istringstream iss(line);
            vector<int> rows;
            while (iss >> num) 
            {
                rows.push_back(num);
                row += 1;
            }
            map.push_back(rows);
            col += 1;
            whichLine = 5;
        }
        if(line == "=====================")
        {
            currentMaze.rows = col-1;
            currentMaze.cols = row/(col-1);
        }
        whichLine += 1;
    }
    currentMaze.map = map;
    CustMap.close();
    //save the Maze in Maps folder
    SaveMaze(currentMaze);
    //getting user's name
    cout << "Who is Playing? ";
    cin >> info.username;
    //starting the game or solving
    if(entry == 3)
        Game(currentMaze);
    if(entry == 5)
        SolveMaze(currentMaze);
    return;
}
bool isDupNames(string name)
{
    ifstream NamesFile;
    NamesFile.open("Maps/MapNames.txt");
    string line, found;
    while(getline(NamesFile, line))
    {
        if(line.find(name) != string::npos)
        {
            found = line.substr(line.find(".")+1);
            if(found == name)
            {
                cout << endl <<"This name already exists in the 'Maps' file." << endl << "Please change the name." << endl << endl;
                NamesFile.close();
                return false;
            }
        }
    }
    return true;
}
void SaveMaze(Maze& currentMaze)
{
   //opening files
   ofstream MapFile;
   ofstream NamesFile;
   string mapName = currentMaze.MapName;
   MapFile.open("Maps/" + mapName + ".txt");
   NamesFile.open("Maps/MapNames.txt", ios::app);
   if(!(NamesFile.is_open() && MapFile.is_open()))
   {
        cerr << "Something went wrong.";
        return;
   }
   //outputting the map and name
   vector<vector<int>> map = currentMaze.map;
   MapFile << endl <<" Map Name: " << currentMaze.MapName <<endl << endl;
   MapFile <<" The Maze: " << endl << endl; 
   int rows = currentMaze.rows;
   int cols = currentMaze.cols;
   for(int i=0; i<rows; i++)
   {
        for(int j=0; j<cols; j++)
            MapFile  << setw(4) << map[i][j];
       MapFile << endl;
   }
   MapFile << "=====================";
   NamesFile << "." << currentMaze.MapName << endl;
   MapFile.close();
   NamesFile.close();
}
void updateStatistics(string result, time_t duration)
{
    ifstream User("Users/" + info.username + ".txt");
    ofstream histFile("History.txt", ios::app);
    if(!(User.is_open() && histFile.is_open()))
    {
        cerr << "I can't open the files to update the Statistics.";
        return;
    }
    //saving the user information in the structure
    string line;
    while (getline(User, line))
    {
        if(line.find("total games:") != string::npos)
            info.totalGames = stoi(line.substr(line.find(":") + 2));
        if(line.find("total wins") != string::npos)
            info.totalWins = stoi(line.substr(line.find(":") + 2));
        if(line.find("win time") != string::npos)
            info.lastWinTime = stoi(line.substr(line.find(":") + 2));
        if(line.find("total time") != string::npos)
            info.totalTime = stoi(line.substr(line.find(":") + 2));       
    }

    //Updating user information
    info.totalGames = info.totalGames + 1;
    info.lastWinTime = info.lastWinTime + duration;
    if(result == "Won")
        info.lastWinTime = duration;
    
    User.close();

    //Outputting the new information
    ofstream outputUser("Users/" + info.username + ".txt");
    outputUser << "Name: " << info.username << endl << 
    "------------------------------------" << endl <<
    "The number of total games: " << info.totalGames << endl <<  
    "..." << endl <<
    "The number of total wins: " << info.totalGames << endl <<
    "..." << endl <<
    "The last win duration: " << info.lastWinTime << " minutes" << endl <<
    "..." << endl <<
    "The total time:" << info.totalTime << " minutes"; 
    outputUser.close();

    //Updating the History
    char c[9];//date
	_strdate_s(c);
    histFile.seekp(0, ios::beg);
    histFile << "The Date of solving this Maze: " << c << endl <<
    "Name of the Player: " << info.username << endl <<
    "Name of the Map: " << currentMaze.MapName << endl <<
    "Spent time: " << duration << endl <<
    "Result of the game: " << result << endl <<
    "=============================================";
    histFile.close();
}
void History()
{
    ifstream histFile("History.txt");
    string line;
    int counter = 1;
    vector<string> eachHist(6);

    //check if the file is empty or not
    if (histFile.peek() == ifstream::traits_type::eof()) 
    {
        cout << "There is no history yet." << endl;
        return;
    }
    //outputting the last 10 histories
    while(getline(histFile, line))
    {
        if(counter <= 10)
        {
            if(line == "=============================================")
            {
                eachHist.push_back(line);
                cout << "The result if the last 10 game: " << endl;
                for(int i=0; i<7; i++)
                    cout << eachHist[i] << endl;
                counter += 1;
            }
            else
                eachHist.push_back(line);
        }
        else
            break;
    }
}
void UserInfo()
{
    string name, line;
    cout << "Enter the name of the user: ";
    cin >> name;
    ifstream user("Users/" + name + ".txt");
    if(!user.is_open())
    {
        cerr << "I can't open '" << name << "' file." << endl;
        return;
    }
    while(getline(user, line))
        cout << line << endl;
}
void menu()
{
    cout <<"Welcome to Maze-Maverick!" << endl << "This is an Easy game!" << endl;
    cout << "Let's Begin!" << endl;
    while(true)
    {
    int entry;
    cout << "---------------------" << endl << "1.Menu" << endl << "2.Exit" << endl << "enter your choice: ";
    cin >> entry;
    if(entry)
    {
    cout << endl << "+------------------------------+"<< 
     endl <<"|          ___"<< "\033[1;2mMenu\033[0m"<<"___          |" <<
     endl << "+------------------------------+" <<
     endl << "|      1.Create a new Map      |" << endl << "|------------------------------|"<< endl <<
    "|          "<<"\033[1;2mPlayground\033[0m"<<"          | " << endl <<
    "|  2.Choose from existing Maps |" << endl << 
    "|     3.Import a Custom Map    |" << endl << "|------------------------------|"<< endl <<
    "|         "<<"\033[1;2mSolve a Maze\033[0m"<<"         |" << endl <<
    "|  4.Choose from existing Map  |" << endl <<
    "|     5.Import a Custom Map    |" << endl << "|------------------------------|"<< endl <<
    "|          6.History           |" << endl << "|------------------------------|"<< endl <<
    "|     7.Users information      |" << endl << "|------------------------------|"<< endl <<
    "|            8.Exit            |" << endl << "+------------------------------+" << endl;


     cout << endl << "Enter the number of your choice from menu (1-8): ";
     cin >> entry;
     cout << endl;
     switch(entry)
     {
     case 1://Create a new map
         createMap();
     break;
     case 2://Maps 
         loadmaze(2);
     break;
     case 3://Another Map Adress
        UploadMap(3);
     break;
     case 4:
        loadmaze(4);
     break;
     case 5:
        UploadMap(5);
     break;
     case 6:
        History();
     break;
     case 7:
        UserInfo();
     break;
     case 8:
        cout << "Goodbye!";
        exit(0);
     break;
     default:
        cout << "Invalid choice." << endl << "Please enter a valid option (1-8)." << endl;
     break;
     }
     }
     else
        exit(0);
    }
}

int main()
{
    menu();
}