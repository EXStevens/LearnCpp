#include <iostream>
#include <limits>
#include <memory>

using namespace std;

struct fish {
    int length;
    int weight;
    char name[30];
};

int main() {
    char buffer[30];

    cout << "New fish item? (Y/N)\n";

    cin.getline(buffer, 30);
    
    if(buffer[0] != 'Y' && buffer[0] != 'y') {
        cout << "Press Enter to exit..." << endl;
        cin.get();
        return 0;
    }

    unique_ptr<fish> f1 = make_unique<fish>();

    cout << "Type Name: ______\b\b\b\b\b\b";
    cin.getline(f1->name, 30);
    cout << "Length (in): ______\b\b\b\b\b\b";
    cin.getline(buffer, 30);
    f1->length = atoi(buffer);
    cout << "Weight (lb): ______\b\b\b\b\b\b";
    cin.getline(buffer, 30);
    f1->weight = atoi(buffer);
    cout << "\nFish item created: " << f1->name << ", Length: " << f1->length << " in, Weight: " << f1->weight << " lb." << endl;
    cout << "Fish item stored at: " << f1.get() << " at heap." << endl << "And the pointer of it stores at: " << &f1 << " at stack." << endl;
    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}