#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// EXERCICIO 1

int modulo(int a, int b) {
    const int result = a % b;
    return result >= 0 ? result : result + b;
}

char encryptChar(char c, int key){
    // a is 97, z is 122
    // a is 65, z is 90

    int dLim, uLim;

    if ((int) c >= (int) 'a' && (int) c <= int('z')){
        dLim = (int) 'a';
        uLim = (int) 'z';
    }
    else if ((int) c >= (int) 'A' && (int) c <= int('Z')){
        dLim = (int) 'A';
        uLim = (int) 'Z';
    }
    else{
        return c;
    }


    char newChar = (char) (modulo((int) c -dLim + key, uLim - dLim + 1) + dLim);

    return newChar;
}

string encryptString(string  s,  int  key){
    string out = "";
    for (int i = 0; i < s.size(); ++i) {
        out += encryptChar(s[i], key);
    }
    return out;
}

void encryptString(char s[], int size, int key){
    for (int i = 0; i < size; ++i) {
        char a = s[i];
        char newChar = encryptChar(s[i], key);
        s[i] = newChar;
        cout << s[i];
    }
}


// EXERCICIO 2


void bubbleSort(vector<string> &v, char order){
    bool done = false;
    int iter = 1;
    while (!done || iter != v.size()){
        for (int i = 0; i < v.size() - iter; ++i) {
            done = true;
            if ((v[i] > v[i+1] && order == 'a') || (v[i] < v[i+1] && order == 'd')) {
                string temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
                done = false;
            }
        }
        iter++;
    }
}

vector<string> readNames (){
    int size;
    vector<string> final;
    cout << "Enter the number of entries: ";
    cin >> size;
    cin.ignore(1, '\n');

    for (int i = 1; i <= size; ++i) {
        cout << "Entry " << i << " ";
        string in;
        getline(cin, in);
        final.push_back(in);
    }
    return final;
}

// EXERCICIO 3




// EXERCICIO 4

bool sequenceSearch(const string &s, int nc, char c){
    char last = NULL;
    int counter = 1;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == last && last == c){
            counter++;
            if (counter == nc) return true;
        }
        else{
            counter = 1;
        }
        last = s[i];
    }
    return false;
}

bool sequenceSe(const string &s, int nc, char c){
    char finder[nc];
    for (int i = 0; i < nc; ++i) {
        finder[i] = c;
    }
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == c){
            if ( s.find(finder, i,nc) ){
                return true;
            }
            else{
                return false;
            }
        }
    return false;
    }
}


// EXERCISE 5



string normalizeName(const string &name){
    vector <string> forbidden = {"DE", "DO", "DA", "DOS", "DAS", "E"};
    stringstream ss;
    stringstream copy;
    ss.str(name);

    while (ss){
        string s;
        ss >> s;
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        if (find(forbidden.begin(), forbidden.end(), s) == forbidden.end()){
            copy << s << " ";
        }
    }
    return copy.str();
}


// EXERCISE 7


struct Date {
    unsigned int year, month, day;
};

void readDate(Date *a){
    int y, m, d;
    char temp;
    cin >> y >> temp >> m >> d;
    a->year = y;
    a->day = d;
    a->month = m;
}

void writeDate(const Date *d){
    cout << d->year << "/" << d->month << "/" << d->day;
}


// EXERCISE 9

struct Address{
    string street;
    int doorNum;
    string city;
};

struct Person{
    string name, gender;
    int age;
    Address address;
};

void readPeople(vector<Person> &ppl){
    cout << "How many entries: ";
    int entries;
    cin >> entries;

    for (int i = 0; i < entries; ++i) {
        ppl.push_back(Person());
        cout << "Name: ";
        cin >> ppl[i].name;
        cout << "Age: ";
        cin >> ppl[i].age;
        cout << "Gender: ";
        cin >> ppl[i].gender;
        cout << "Street: ";
        cin >> ppl[i].address.street;
        cout << "Door number: ";
        cin >> ppl[i].address.doorNum;
        cout << "City: ";
        cin >> ppl[i].address.city;
    }
}

void showPeople(const vector<Person> ppl){
    for (Person person: ppl){
        cout << person.name << endl;
        cout << '\t' << person.age << endl;
        cout << '\t' << person.address.city << endl;
    }
}

void findCity(const vector<Person> ppl){
    // loop and compare with given city by input
}


int main() {
    vector<Person> people;
    readPeople(people);
    showPeople(people);
    return 0;
}
