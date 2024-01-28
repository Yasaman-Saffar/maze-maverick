#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include<thread> //baraye sleep
#include<chrono> //baraye sleep
#include<conio.h>//baraye seda
#include<windows.h>//baraye seda
#include <chrono> //for calculating duration

#ifdef _WIN32
    #define CLEAR "cls"//baraye windows
#else
    #define CLEAR "clear"//baraye linux
#endif
//baraye rangi shodan
#define RESET   "\033[0m"//az beyn bordane halate rangi 
#define BLUE    "\033[34m"//abi shodan
#define RED		"\033[31m"//germez shodan
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
    double lastWinTime;
    double totalTime;
}info;

void menu();
void BackToMenu();
void createMap();
void loadmaze(int);
void UploadMap(int);
bool isDupNames(string);
bool SaveMaze(Maze&);
bool createUser();
void updateStatistics(string, double);
void History();
void UserInfo();
void SolveMaze(Maze&);
void clearConsole(double);
void Game(Maze&);
void printTable(const vector<vector<int>>&, const vector<pair<int , int>>&);
bool movePlayer(int&, int&, char, vector<vector<int>>&, vector<pair<int, int>>&);

//menu part
void menu()
{
    cout << endl << endl <<"         ***Maze-Maverick***" << endl << "=====================================" << endl << "This is an Easy game!" << endl;
    cout << "Let's Begin!" << endl;
    while(true)
    {
    clearConsole(3);//clear the terminal after 3 seconds
    int entry;
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
}
void BackToMenu()
{
    int entry;
    cout << "---------------------" << endl << "1.Menu" << endl << "2.Exit" << endl << "enter your choice: ";
    getting:
    cin >> entry;
    if(entry == 1)
    {
        cout << "Heading to the menu...";
        return;
    }
    if(entry == 2)
    {
        cout << "Goodbye!";
        exit(0);
    }
    else
    {
        cout << "Invalid choice. Please enter 1 or 2: "; 
        goto getting;
    }
}
void createMap()
{
    clearConsole(0.2);
    cout << "~Create a new map" << endl;
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
    bool isSaved = SaveMaze(currentMaze);
    if(isSaved)
        cout << endl << "The new Map was successfully created and you can see it in 'Maps' Folder!" << endl;
    BackToMenu();
}
void loadmaze(int entry)
{
    clearConsole(0.2);
    if(entry == 2)
        cout << "~Playground => Choosing from existing Maps" << endl << endl;
    if(entry == 4)
        cout << "~Solve a maze => Choosing from existing Maps" << endl << endl;

    //opening the names file
    ifstream NamesFile;
    NamesFile.open("Maps/MapNames.txt");
    if(!NamesFile.is_open())
    {
    cerr << "I can't open the 'MapNames' file." << endl;
    BackToMenu();
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
       BackToMenu();
       return;
   }
   cout << "list of the maps: "<< endl;
   for(string each : names)
       cout << each << endl;
    //asking user's choice
    UserChoice:
    cout << "Enter the name of the Map: ";
    while(true)
    {
        string chosen;
        cin >> chosen;
        currentMaze.MapName = chosen;
        ifstream MapsFile;
        MapsFile.open("Maps/" + chosen + ".txt");

        if(!MapsFile.is_open())
        {
            cerr << "I can't open the '" << chosen <<"' file." << endl;
            goto UserChoice;
        }
        //reading the map
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
    //starting the game or solving
    if(entry == 2)
    {
        //getting user's name
        cout << "Who is Playing? ";
        cin >> info.username;
        Game(currentMaze);
    }
    if(entry == 4)
        SolveMaze(currentMaze);
}
void UploadMap(int entry)
{
    clearConsole(0.2);
    if(entry == 3)
        cout << "~Playground => Importing a Custom Map" << endl;
    if(entry == 5)
        cout << "~Solve a maze => Importing a Custom Map" << endl;

    //getting the address 
    address:
    cout << endl << "Please ensure that the file format matches the game map format." 
    << endl << "You can find a sample template in the 'Maps' folder for reference." 
    << endl << endl << "Enter the address of the File: ";
    string FileAdd;
    cin >> FileAdd;
    ifstream CustMap(FileAdd);
    if(!CustMap.is_open())
    { 
        cerr << "I can't open the custom File." << endl << "Please correct this address or provide a different one." << endl;
        goto address;
    }

   //checking if the file is empty or not
    if (CustMap.peek() == ifstream::traits_type::eof()) 
    {
        cout << "This file is empty. Please enter another address." << endl;
        goto address;
    }

   //reading the map
   string line;
   int num, whichLine = 1, row=0, col=0;
   vector<vector<int>> map;
   while(getline(CustMap, line)) 
   {
        if(line.find("Map Name:") != string::npos) 
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
    bool isSaved = SaveMaze(currentMaze);
    if(!isSaved)
        {
            BackToMenu();
            return;
        }
    if(entry == 3)
    {
        //getting user's name
        cout << "Who is Playing? ";
        cin >> info.username;
        Game(currentMaze);
    }
    if(entry == 5)
        SolveMaze(currentMaze);
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
            found = line.substr(line.find(".") + 1);
            if(found == name)
            {
                cout << endl <<"This name already exists in the 'Maps' file." << endl << "Please provide a different name." << endl << endl;
                NamesFile.close();
                return false;
            }
        }
    }
    return true;
}
bool SaveMaze(Maze& currentMaze)
{
   //opening files
   ofstream MapFile;
   ofstream NamesFile;
   string mapName = currentMaze.MapName;
   MapFile.open("Maps/" + mapName + ".txt");
   NamesFile.open("Maps/MapNames.txt", ios::app);
   if(!(NamesFile.is_open() && MapFile.is_open()))
   {
        cerr << "An issue occurred while saving this map." << endl;
        return false;
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
   return true;
}
bool createUser()
{
    //opening files
    ofstream outputUser("Users/" + info.username + ".txt");
    ofstream UserNames("Users/Usernames.txt", ios::app);
    if(!UserNames.is_open())
    {
        cerr << "An issue occurred while creating a new User.";
        BackToMenu();
        return false;
    }
    //assigning 0
    info.lastWinTime = 0;
    info.totalGames = 0;
    info.totalTime = 0;
    info.totalWins = 0;
    outputUser << "Name: " << info.username << endl << 
    "------------------------------------" << endl <<
    "The number of total games: " << info.totalGames << endl <<  
    "..." << endl <<
    "The number of total wins: " << info.totalGames << endl <<
    "..." << endl <<
    "The last win duration: " << info.lastWinTime << " minutes" << endl <<
    "..." << endl <<
    "The total time: " << info.totalTime << " minutes"; 
    outputUser.close();
    //outputting names
    UserNames << info.username << endl;
    UserNames.close();
    return true;
}
void updateStatistics(string result, double duration)
{
    ifstream UserNames("Users/Usernames.txt");
    string name;
    int i=0;
    if (UserNames.peek() == ifstream::traits_type::eof()) 
    {
        bool isCreated = createUser();
        if(!isCreated)
            return;
    }
    while (getline(UserNames, name))
    {
        if(name == info.username)
            i += 1;
    }
    if(i == 0)
        createUser();
    UserNames.close();
    
    ifstream User("Users/" + info.username + ".txt");
    ofstream histFile("History.txt", ios::app);
    if(!(User.is_open() && histFile.is_open()))
    {
        cerr << "I can't open the files to update the Statistics.";
        BackToMenu();
        return;
    }
    //saving the user information in the structure
    string line;
    while (getline(User, line))
    {
        if(line.find("games:") != string::npos)
            info.totalGames = stoi(line.substr(line.find(":") + 2));
        if(line.find("total wins") != string::npos)
            info.totalWins = stoi(line.substr(line.find(":") + 2));
        if(line.find("win duration") != string::npos)
            info.lastWinTime = stod(line.substr(line.find(":") + 2));
        if(line.find("total duration") != string::npos)
            info.totalTime = stod(line.substr(line.find(":") + 2));       
    }

    //Updating user information
    info.totalGames +=  1;
    info.totalTime += duration;
    if(result == "Won")
    {
        info.lastWinTime = duration;
        info.totalWins += 1;
    }
    
    User.close();

    //Outputting the new information
    ofstream outputUser("Users/" + info.username + ".txt");
    outputUser << "Name: " << info.username << endl << 
    "------------------------------------" << endl <<
    "The number of total games: " << info.totalGames << endl <<  
    "..." << endl <<
    "The number of total wins: " << info.totalWins << endl <<
    "..." << endl <<
    "The last win duration: " << fixed << setprecision(2) << info.lastWinTime << " minutes" << endl <<
    "..." << endl <<
    "The total duration: " << fixed << setprecision(2) << info.totalTime << " minutes" << endl <<
    "..." << endl; 
    outputUser.close();

    //Updating the History
    auto t = std::time(nullptr);// the date
    auto tm = *std::localtime(&t);
    histFile.seekp(0, ios::beg);
    histFile << "The Date of solving this Maze: " << put_time(&tm, "%d-%m-%Y") << endl <<
    "Name of the Player: " << info.username << endl <<
    "Name of the Map: " << currentMaze.MapName << endl <<
    "Spent time: " << fixed << setprecision(2) << duration << endl <<
    "Result of the game: " << result << endl <<
    "=============================================" << endl;
    histFile.close();
}
void History()
{
    clearConsole(0.2);
    cout << "~History" << endl << endl;
    ifstream histFile("History.txt");
    string line;
    if(!histFile.is_open())
    {
        cerr << "An issue occurred while showing the results." <<endl;
        BackToMenu();
        return;
    }
    //check if the file is empty or not
    if (histFile.peek() == ifstream::traits_type::eof()) 
    {
        cout << "There is no history yet." << endl;
        BackToMenu();
        return;
    }
    //outputting histories
    
    cout << "The result if the last 10 games(oldest to newest):"<< endl << endl;
    
    vector<string> lastTenRes;

    while (getline(histFile, line))
    {
        if (lastTenRes.size() >= 60)
            lastTenRes.erase(lastTenRes.begin());
        lastTenRes.push_back(line); 
    }
    int size = lastTenRes.size();
    for(int i=0; i<size; i++)
        cout << lastTenRes[i] << endl;
    
    BackToMenu();
}
void UserInfo()
{
    clearConsole(0.2);
    cout << "~User Information" << endl << endl;
    string name, line;
    cout << "Enter the name of the user: ";
    cin >> name;
    ifstream user("Users/" + name + ".txt");
    if(!user.is_open())
    {
        cerr << "I can't open the '" << name << "' file." << endl;
        BackToMenu();
        return;
    }
    while(getline(user, line))
        cout << line << endl;
    BackToMenu();
}
//game part
void SolveMaze(Maze& currentMaze)
{
    //namayeshe hale 1000 to
    cout << endl << "The answer of the '"<< currentMaze.MapName << "' Maze: " << endl;
    int numRows = currentMaze.rows, numCols = currentMaze.cols;
    vector<vector<int>> map = currentMaze.map;
    for (int i = 0 ; i < numRows ; ++i) 
  	{
     	for (int j = 0 ; j < numCols ; ++j)
    	{
    		if(i == numRows - 1)
    			cout << BLUE << setw(4) << map[i][j] << "\t";
    		else if(j == 0)
    			cout << BLUE << setw(4) << map[i][j] << "\t";
            else
            	cout << RESET << setw(4) << map[i][j] << "\t";
        }
        cout << endl;
    }
    cout << RESET;
    BackToMenu();
}
void clearConsole(double seconds)//tabe  baraye taiine modat zamane pak shodane terminal
{
	std :: this_thread::sleep_for(std::chrono::duration<double>(seconds));
	system(CLEAR);
}
void Game(Maze& currentMaze)
{
    int numRows = currentMaze.rows;
    int numCols = currentMaze.cols;

    int pathLength = numRows + numCols - 1;//tole masir = x + y - 1
    int playerRow = 0;//khane shro
    int playerCol = 0;//khane shoro
	vector<pair<int , int>>path;
	path.push_back({playerRow , playerCol});
	vector<vector<int>> gameTable = currentMaze.map; 
    gameTable = currentMaze.map;

    clock_t start, end;
    start = clock();// strarting the chronometer

    while(true) 
	{
        printTable(gameTable,path);

        char move;
        cout << "Enter your move :" << endl;
        cout << "w : up , a : left , s : down , d : right" << endl;
        cin >> move;

        if(movePlayer(playerRow, playerCol, move, gameTable , path)) //agar true bood
		{
            if(! (playerRow == numRows - 1 && playerCol == numCols - 1))
            {
                cout << "your location is: [" << playerRow<<"] [" << playerCol <<"]" << " = " << gameTable[playerRow] [playerCol] << endl;
            }
			if(playerRow == numRows - 1 && playerCol == numCols - 1 && gameTable[numRows - 1][numCols - 1] == 0)//aghar be khane akhar resid va khane akhar barabar ba 0 bood
        	{
                end = clock(); //stopping the chronometer
                double duration = double(end - start)/60000; //calculaing the duration 
        		int sumOfpath = 0;
				for(int i = 0 ; i < path.size() ; i++)
				{
					sumOfpath += gameTable[path[i].first][path[i].second];
				}
				sumOfpath = sumOfpath - gameTable[numRows - 1][numCols - 1];//jame khane haye toole masire karbar

				if(path.size() == pathLength && sumOfpath == gameTable[numRows - 1][numCols -1])//agar jame khane ha barabar ba khane akhar bood va tole masir barabar ba x + y - 1 bood
                {
                	cout <<"*****************************" << endl;
                	cout <<"*Congratulations! You Won :)*" << endl;
                	cout <<"*****************************" << endl;
                    updateStatistics("Won", duration);
                    BackToMenu();
				}
                else
                {
                	cout <<"***********************" << endl;
                	cout <<"*I'm sorry. you lost!* " << endl;
                	cout <<"***********************" << endl;
                    updateStatistics("Lost", duration);
                    BackToMenu();
				}
                
               break;
			}
			
            else if(playerRow == numRows - 1 && playerCol == numCols - 1) //agar be khane akhar resid va khane akhar 0 nabood
			{
                end = clock(); //stopping the chronometer
                double duration = double(end - start)/60000; //calculaing the duration 
				int sumOfpath = 0;
				for(int i = 0 ; i < path.size() ; i++)
				{
					sumOfpath += gameTable[path[i].first][path[i].second];
				}
				sumOfpath = sumOfpath - gameTable[numRows - 1][numCols - 1];//jame khane haye toole masire karbar
				
				if(path.size() == pathLength && sumOfpath == gameTable[numRows - 1][numCols -1])//agar jame khane ha barabar ba khane akhar bood va tole masir barabar ba x + y - 1 bood
				{
					cout << "*****************************" << endl;
                	cout << "*Congratulations! You Won :)*" << endl;
                	cout << "*****************************" << endl;
                    updateStatistics("Won", duration);
                    BackToMenu();
				}
                else
                {
                	cout << "***********************" << endl;
                	cout << "*I'm sorry. you lost!* " << endl;
                	cout << "***********************" << endl;
                    updateStatistics("Lost", duration);
                    BackToMenu();
				}
               break;
            }
        } 
        
		else//agar false bood
		{
			cout << RED << "Inviled move. Try again" << RESET;
			Beep(500 , 800);//tolide seda ba 500 hertz va be modate 800 milisaniye
		}
           clearConsole(0.7);//update va pak kardane terminal har 0.7 saniye yek bar
    }
}
void printTable(const vector<vector<int>>& table, const vector<pair<int , int>>& path) //tabe namayeshe jadval 
{
    int numRows = currentMaze.rows;
    int numCols = currentMaze.cols;

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
                cout << BLUE << setw(4) << table[i][j] << "\t" << RESET;
            else if(i == numRows - 1 && j == numCols - 1)//namayeshe khane akhar be range ghermez
            	cout << RED << setw(4) << table[i][j] << RESET ;
			else
                cout << setw(4) << table[i][j] << "\t";

        }
        cout << endl;
    }
}
bool movePlayer(int& row, int& col, char direction, vector<vector<int>>& table , vector<pair<int , int>>& path) 
{
    int numRows = currentMaze.rows;
    int numCols = currentMaze.cols;

    int newRow = row;
    int newCol = col;
	
	if(direction == 'w')//up
		newRow--;
	else if(direction == 'a')//left
		newCol--;
	else if(direction == 's')//down
		newRow++;
	else if(direction == 'd')//right
		newCol++;
	else//vared kardane harfi digar
	{
		Beep(500 , 800);//tolide seda ba 500 hertz va be modate 800 milisaniye
        cout << RED << "your move is wrong! Please choose letter among w , s , d , a." << RESET << endl;
	}
	
	
    if(newRow < 0 || newCol < 0 || newRow >= numRows || newCol >= numCols || table[newRow][newCol] == 0)//agar az mahdoode jadval kharej shod
    	return false;

    if(newRow == numRows - 1 && newCol == numCols - 1 && table[numRows - 1][numCols - 1] == 0)//aghar khane akhar barabar ba 0 bood an ra mane dar nazar nagirad 
    {
    	row = newRow;
        col = newCol;
        path.push_back({row , col});//ezafe kardane khane be masire karbar
        return true;
	}
    else if(newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols && table[newRow][newCol] != 0) 
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
    menu();
}