#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <memory>
#include <limits>
#include <cstdlib>
#include <cerrno>
#include <cstring>

using namespace std;

fstream working;
string filename;
int status;
enum {Op_No, Op_New, Op_Existing};

int startup();
int fileInit(string fn, int stat);
void showFstreamError(const fstream& ofs, const string& filename);

int main() {
    int t0;
    do {
        t0 = startup();
    } while (t0 != 0);

    if(fileInit(filename, status) != 0) {
        cerr << "File initialization failed." << endl;
        return 1;
    }




    return 0;
}

int startup() {

    cout << "In a mood of editing? (0 for no, 1 for new, 2 for existing)" << endl;
    unique_ptr<char> response = make_unique<char>();
    *response = cin.get();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (isdigit(*response) ? *response - '0' : *response) {
        case Op_No:
            cout << "You chose not to edit." << endl;
            cout << "Exiting the program." << endl;
            exit(0);
        case Op_New:
            cout << "You chose to create a new file." << endl;
            status = Op_New;
            break;
        case Op_Existing:
            cout << "You chose to edit an existing file." << endl;
            status = Op_Existing;
            break;
        default:
            cerr << "Invalid choice." << endl;
            return 1;
    }
    
    do {
        cout << "Enter the name of the text file to work on: ";
        getline(cin, filename);
        if (filename.empty() && filename.size() < 5 && !(filename.substr(filename.size() - 1 - 3) == ".txt")) {
            cerr << "Filename cannot be empty and must be ended in \".txt\" Please try again." << endl;
        }

    } while (filename.empty() && filename.size() < 5 && !(filename.substr(filename.size() - 1 - 3) == ".txt"));
    
    return 0;
}

int fileInit(string fn, int stat) {
    if (stat == Op_New) {
        fstream newFile(fn);
        if (!newFile.is_open()) {
            cerr << "Error creating new file." << endl;
            showFstreamError(newFile, fn);
            return 1;
        }
        working.open(fn);
        if (!working.is_open()) {
            cerr << "Error opening file for writing." << endl;
            showFstreamError(working, fn);
            return 1;
        }
        cout << "New file created: " << fn << endl;
    } else if (stat == Op_Existing) {
        working.open(fn, ios::in | ios::out);
        if (!working.is_open()) {
            cerr << "Error opening file for reading/writing." << endl;
            showFstreamError(working, fn);
            return 1;
        }
        cout << "Existing file opened: " << fn << endl;
    }
    
    return 0;
}

void showFstreamError(const fstream& fs, const string& filename) {
    cerr << "Error opening or writing to file: " << filename << endl;

    if (errno != 0) {
        cerr << "System error: " << strerror(errno) << endl;
    }

    if (fs.fail()) {
        cerr << "Stream status: failbit set (operation failed)." << endl;
    }

    if (fs.bad()) {
        cerr << "Stream status: badbit set (serious I/O error)." << endl;
    }

    if (fs.eof()) {
        cerr << "Stream status: eofbit set (unexpected end of file)." << endl;
    }
}