#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct Maze
{
    string MapName;
    int Row;
    int Col;
    vector<vector<int>> map;
};

struct User {
    string username;
    int totalGames;
    int totalWins;
    time_t lastWinTime;
    int totalTime;
}Userinfo;

void loadmaze(ifstream& MapsFile)
{
   string line;
   vector<Maze> maps;
   Maze eachMap;
   while(getline(MapsFile, line))
   {
    if(line.find("Map Name:") != string::npos)
    eachMap.MapName = line.substr(line.find(":"), line.size()-1);
    maps.push_back(eachMap);
   }
   cout << "list of the maps: "<< endl;
   for(int i=0; i<maps.size(); i++)
       cout << i+1 << ". "<< maps[i].MapName << endl;
    cout << "Enter the number of your choice: ";
    int chosen;
    cin >> chosen;
    Maze Currentmaze = maps[chosen-1];
    //call the display func
}

Maze CreateMap(ifstream& CustMap)
{
   Maze maze;
   int displayRow = maze.Row;
   int displayCols = maze.Col;
   string line;
   int row, cols;
   CustMap >> row >> cols;
    while (getline(CustMap, line)) 
    {
        if (line.find("Map Name:") != string::npos) 
            maze.MapName = line.substr(line.find(":") + 2);
        if (line.find("The number of Rows:") != string::npos) 
            maze.Row = row;
        if (line.find("The number of Columns:") != string::npos)
            maze.Col = cols;
    }
        ofstream MapsFile;
        MapsFile.open("Maps.txt");
        if(!MapsFile.is_open())
        {
         cerr << "I can't save this map to 'Maps.txt'!";
         exit(0);
        }
        SaveMaze(MapsFile, maze);
   return maze;
}

void SaveMaze(ofstream& MapsFile, Maze& maze)
{
   MapsFile << "Map Name:" << maze.MapName << endl;
   MapsFile << "The number of Rows:" << maze.Row << endl;
   MapsFile << "The number of Columns:" << maze.Col << endl;
   MapsFile << "_________________________________________" << endl;
}
void DisplayMap(){}
void isWon(){}
void updateStatistics(){}
void menu()
{
    cout << "This is an Easy game!" << endl << "Let's Begin!"<< endl << 
    "...Playground" << endl <<
     "  1.Choose from existing Maps" << endl <<
     "  2.Import a Custom Map" << endl <<
    "...Solve a Maze" << endl <<
     "  3.Choose from existing Maps" << endl <<
     "  4.Import a Custom Map" << endl <<
     "  5.History" << endl <<
     "  6.Users information" << endl <<
     "  7.Exit" << endl << endl;
     while(true)
     {
     "Enter the number of your choice: ";

     vector<User> users;
     int entry;
     cin >> entry;
     switch(entry)
     {
     case 1://ExistingMap
         ifstream MapsFile;
         MapsFile.open("Maps.txt");
         if(!MapsFile.is_open())
         {
            cerr << "I can't open the File!";
            break;
         }
         loadmaze(MapsFile);
         MapsFile.close();
     break;
     case 2://AnotherMapFile
         cout << "Enter the address of the File: ";
         string FileAdd;
         cin >> FileAdd;
         ifstream CustMap(FileAdd);
         ofstream MapsFile;
         if(!CustMap.is_open())
         {
            cerr << "I can't open the File!";
            break;;
         }
         CreateMap(CustMap);
         CustMap.close();
     break;
     case 3:
     break;
     case 4:
     break;
     case 5:
     break;
     case 6:
         cout << "Enter the name of the user:";
         string name;
         cin >> name;
         //use the vector
     break;
     case 7:
        cout << "Goodbye!";
        exit(0);
     break;
     default:
        cout << "Your choice isn't in the menu." << endl << "Please enter a valid option (1-7)." << endl << endl;
     break;
     }
     }
}

int main()
{
   
}