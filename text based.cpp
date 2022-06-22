#include <filesystem>
#include <windows.h>
namespace fs = std::filesystem;
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void wait() {
    // press any key to continue
    cout << "Press any key to continue...";
    cin.ignore();
    cin.get();
}

void menu() {
    cout << "\n                 / /                        / \n _. _   _     __/ /__   _   _  __.  __  _. /_ \n(__/_)_/_)_  (_/_/_)   /_)_</_(_/|_/ (_(__/ /_\n  /   /                                       \n '   '                                        " << endl;
}

// useless but why not, i'll maybe use it later
string readFileIntoString(const string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "An error occurred while opening the file : '" << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

// too lazy to comment this too
bool is_file_empty(std::ifstream& pFile) {
    return pFile.peek() == std::ifstream::traits_type::eof();
}

string getFileName(string const& path)
{
    return path.substr(path.find_last_of("/\\") + 1);
}

int main() {
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd,SW_SHOWMAXIMIZED);  
    menu();
    bool something = false;
    int i = 1;
    string separation = "------------";
    fs::path path = fs::current_path(); // /!\ don't work on cmd
    string dbPath = path.u8string() + "\\db\\"; // setup the db path
    string line; // setup the line var
    string keyword; // setup the keyword var
    cout << "Enter a keyword : ";
    cin >> keyword;
    cout << separation << endl;

    // for each file in the db directory
    for (const auto & entry : fs::directory_iterator(dbPath))
    {
        ifstream dbfile (entry.path()); // setup the file to be read
        if (dbfile.is_open()) // verify it can be opened (if it exist)
        {
            while ( getline (dbfile,line) ) // get all lines of the file
            {
                if (line.find(keyword) != string::npos) // if you find the keyword
                {
                    // write the line to the output file and show in the tui
                    something = true;
                    cout << "[" << i << "] - [" << getFileName(entry.path()) << "]\n" << line << endl;
                    cout << separation << endl;
                    i++;
                }
                else
                {
                    // if you don't find the keyword, do nothing
                }
            }

        dbfile.close();
        }

        else
        {
            cout << "Unable to open the db file"; 
        }
    }
    if (something == false)
    {
        cout << "No result found" << endl;
        cout << separation << endl;
        wait();
    }
    else 
    {
        wait();
    }
    return 0;
}