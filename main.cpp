#include <filesystem>
namespace fs = std::filesystem;
#include <iostream>
#include <fstream>
#include <string>  
using namespace std;

// too lazy to comment this, just read and learn by yourself.
std::string getKeyword(){
    string line;
    string keyword;
    ifstream myfile ("keyword.txt");

    if (myfile.is_open())
    {
        while ( getline (myfile,line) ) 
        {
            keyword = line;
        }
    }
    else
    {
        cout << "Unable to open the keyword file";
        exit(0);
    }
    return keyword;
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
bool is_file_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

// here too
void writeFile(const string& name, const string& content, bool append = false) {
    ofstream outfile;
    if (append)
    {
        outfile.open(name, ios_base::app);
    }
    else
    {
        outfile.open(name);
    }
    outfile << content << endl;
}

int main() {
    fs::path path = fs::current_path(); // /!\ don't work on cmd
    string dbPath = path.u8string() + "\\db\\"; // setup the db path
    string line; // setup the line var
    string keyword = getKeyword(); // setup the keyword

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
                    writeFile("output.txt", line, true); // write the line to the output file
                }
            }

        dbfile.close();
        }

        else
        {
            cout << "Unable to open the db file"; 
        }
    }
    return 0;
}