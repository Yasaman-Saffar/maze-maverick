#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
struct Maze
{
    string MapName;
    vector<vector<int>> map;
};

struct User {
    string username;
    int totalGames;
    int totalWins;
    time_t lastWinTime;
    int totalTime;
}Userinfo;
Maze createMap()
{

}
void loadmaze(int entry)
{
    Maze currentMaze;
    //opening the names file
    ifstream NamesFile;
    ifstream MapsFile;
    NamesFile.open("names.txt");
    MapsFile.open("Maps.txt");
    if(!NamesFile.is_open())
    {
    cerr << "I can't open the 'names' file." << endl;
    return;
    }
    if(!MapsFile.is_open())
    {
    cerr << "I can't open the 'Maps' file." << endl;
    return;
    }
   //making a list of names
   string line;
   vector<string> names;
   
   while(getline(NamesFile, line))
       names.push_back(line);
   if(names.empty())
   {
       cout << "No maps found in the file." <<endl;
       return;
   }
   cout << "list of the maps: "<< endl;
   for(int i=0; i<names.size(); i++)
       cout << i+1 << ". " << names[i] << endl;
    //asking user's choice
    cout << "Enter the number of your choice: ";
    while(true)
    {
        int chosen;
        cin >> chosen;
        if(chosen <= names.size() && chosen > 0)
        {
            bool foundName = false;
            string chosenN = names[chosen-1];
            Maze currentMaze;
            currentMaze.MapName = chosenN;
            //reading the map
            while(getline(MapsFile, line))
            {
                if(line == "+-----------------------------------+")
                break;
                if(!foundName)
                {
                    if(line.find(chosenN) != string::npos)
                    foundName = true;
                }
                if(foundName)
                {
                    vector<int> rows;
                    istringstream iss(line);
                    int num;
                    while (iss >> num) 
                        rows.push_back(num);
                    currentMaze.map.push_back(rows);
                }
            }
            break;
        }
        else
            cout << "Invalid choice." << endl << "Please enter another number (1-" << names.size() << ") : " ;
    }
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
        cerr << "I can't open the File.";
        return;
    }
   //reading the map
   Maze currentMaze;
   string line;
   int num;
    while(getline(CustMap, line)) 
    {
        if (line.find("Map Name:") != string::npos) 
            currentMaze.MapName = line.substr(line.find(":") + 2);
        istringstream iss(line);
        vector<int> row;
        while (iss >> num) 
            row.push_back(num);
        currentMaze.map.push_back(row);
    }
    //Checking for duplicated names
    ifstream NamesFile;
    NamesFile.open("names.txt");
    if(!NamesFile.is_open())
    {
        cerr << "I can't open the 'names' file.";
        return;
    }

    int lineCounter=0;
    while(getline(NamesFile, line))
    {
        lineCounter++;
        if(line.find(currentMaze.MapName) != string::npos)
        {
            cout << endl <<"This name already exists in the 'Maps' file." << endl << "Please change the name or enter another address" << endl << endl;
            goto address;
        }
    }

        NamesFile.close();
        CustMap.close();
        SaveMaze(currentMaze, lineCounter);
        /*if(entry == 3)
        if(entry == 5)*/
}

void SaveMaze(Maze& currentMaze, int lines)
{
   ofstream MapsFile;
   ofstream NamesFile;
   MapsFile.open("Maps.txt", ios::app);
   NamesFile.open("names.txt", ios::app);
   if(!MapsFile.is_open())
   {
        cerr << "I can't save this map to 'Maps.txt'!";
        return;
   }
   vector<vector<int>> map = currentMaze.map;
   MapsFile << setw(20) <<" Map Name: " << currentMaze.MapName <<endl;
   MapsFile << setw(20) <<" The Maze: "; 
   for(int i=0; i<map.size(); i++)
   {
       for(int j=0; j<map[i].size(); j++)
       {
       MapsFile << map[i][j] << " ";}
       MapsFile << endl;
   }
   MapsFile << "+-----------------------------------+" << endl;
   NamesFile << lines+1 << ". " << currentMaze.MapName << endl;
   MapsFile.close();
   NamesFile.close();
}
void DisplayMap(){}
void isWon(){}
void updateStatistics(){}
void History(){}
void Userinfo(){}
void menu()
{
    Maze currentMaze;
    cout << "This is an Easy game!" << endl << "Let's Begin!"<< endl << endl << 
    "1.Create a new Map" << endl <<
    "__Playground" << endl <<
    "2.Choose from existing Maps" << endl <<
    "3.Import a Custom Map" << endl <<
    "__Solve a Maze" << endl <<
    "4.Choose from existing Maps" << endl <<
    "5.Import a Custom Map" << endl <<
    "6.History" << endl <<
    "7.Users information" << endl <<
    "8.Exit" << endl;
    while(true)
    {
     cout << endl << "Enter the number of your choice(1-8): ";
     int entry;
     cin >> entry;
     try
     {
        if(cin.fail())
        {
            cin.clear();
            throw("Invalid choice.");
        }
     
     switch(entry)
     {
     case 1:
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
     break;
     /*case 7:
         cout << "Enter the name of the user:";
         string name;
         cin >> name;
         //use the vector*/
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
     catch(string str)
     {
        cerr << str << endl << "Please enter a valid option (1-8)." << endl;
     }
     }
}

int main()
{
    menu();
}