#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iomanip>

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


// EXERCICIO 10

struct Point{
    int x;
    int y;
};

struct Polygon{
    int nPoints;
    // vector<Point> points; c++
    Point *points;
};

void readPolygon(Polygon &poly){
    cout << "How many polygons?";
    cin >> poly.nPoints;
    poly.points = (Point *) malloc(sizeof(Point) * poly.nPoints);
    int x, y;
    for (int i = 0; i < poly.nPoints; ++i) {
        cout << "Introduce points (x y): ";
        cin >> x >> y;
        Point point;
        point.x = x; point.y = y;
        poly.points[i] = point;
        // poly.points.push_back(point);
    }
}

void clearPolygon(Polygon poly){
    free(poly.points);
}

double areaPolygon(Polygon poly){
    int sum = 0;
    for (int i = 0; i < poly.nPoints; ++i) {
        sum += poly.points[i].x * poly.points[(i+1)%poly.nPoints].y - poly.points[i].y * poly.points[(i+1)%poly.nPoints].x;
    }
    clearPolygon(poly);
    return abs((double) sum/2);
}

// EXERCICIO 11


void readNames(vector<string> &names, string fileName){
    ifstream f_in;
    f_in.open(fileName);

    if (!f_in.is_open()){
        cerr << "File not found!";
        exit(1);
    }

    string name;
    while (getline(f_in, name)){
        names.push_back(name);
    }
    f_in.close();
}

void writeNames(vector<string> names, string fileName){
    ofstream f_out;
    f_out.open(fileName);
    for (int i = 0; i < names.size(); ++i) {
        f_out << names[i] << endl;
    }
}

// EXERCISE 12

void encodeRLE(int argc, char *argv[]){
    if (argc != 3){
        cerr << "Wrong number of arguments";
        exit(1);
    }

    string fileName = argv[1];
    string outputName = argv[2];


    ifstream f_in;
    f_in.open(fileName, ios::binary);

    if (!f_in.is_open()){
        cerr << "File not found!";
        exit(1);

    }

    ofstream f_out;
    f_out.open(outputName, ios::binary);

    int dim1, dim2;
    f_in >> dim1 >> dim2;

    f_out << dim1 << " " << dim2 << " ";

    char c = 0;
    char prevC = 0;
    int counter = 1;
    f_in >> c;
    while (f_in.read((char *) &c, sizeof(char))){
        if (c != prevC && prevC != 0){
            cout << counter << prevC;
            f_out << counter << prevC;
            counter = 1;
            prevC = c;
            continue;
        }
        counter ++;
        prevC = c;
    }
    f_in.close();
    f_out.close();
}


void decodeRLE(int argc, char *argv[]){
    if (argc != 3){
        cerr << "Wrong number of arguments";
        exit(1);
    }

    string fileName = argv[1];
    string outputName = argv[2];


    ifstream f_in;
    f_in.open(fileName, ios::binary);

    if (!f_in.is_open()){
        cerr << "File not found!";
        exit(1);

    }

    ofstream f_out;
    f_out.open(outputName, ios::binary);

    int dim1, dim2;
    f_in >> dim1 >> dim2;

    f_out << dim1 << " " << dim2 << " ";

    int num;
    char c;

    f_in >> num;
    f_in >> c;

    while (f_in){
        for (int i = 0; i < num; ++i) {
            f_out << c;
        }
        f_in >> num;
        f_in >> c;
    }
    f_in.close();
    f_out.close();
}


// EXERCICIO 13

struct Bet{
    string name;
    vector<unsigned> mainNumbers;
    vector<unsigned> luckyStars;
};



void translateBets(string fileName){

    vector<unsigned> winNumbers = {3, 13, 20, 39, 50};
    vector<unsigned> winStars   = {5, 12};

    ifstream fIn;
    fIn.open(fileName, ios::binary);

    ofstream  fOut;
    fOut.open(fileName + "_final");
    fOut << "KEY = ";
    for (int i = 0; i < winNumbers.size(); ++i) {
        fOut << winNumbers[i] << " ";
    }
    fOut << "- " << winStars[0] << " " << winStars[1] << endl;

    if (!fIn.is_open()){
        cerr << "File does not exist!";
        exit(1);
    }

    string name;
    stringstream ss;
    int num;

    int counterNums, counterStars, winNumsCtr, winStarsCtr;

    while (getline(fIn, name)){
        if (!isdigit(name[0])){
            fOut << name << endl;
        }
        else{
            winNumsCtr = 0; winStarsCtr = 0; counterStars = 0; counterNums = 0;
            if(fIn.fail()){
                break;
            }
            stringstream ss(name);

            while (1){
                ss >> num;
                if (ss.fail()){
                    ss.ignore(1000, '-');
                    ss.clear();
                    break;
                }
                counterNums ++;
                if(find(winNumbers.begin(), winNumbers.end(), num) != winNumbers.end()) winNumsCtr ++;
                fOut << setw(2) << num << " ";
            }

            fOut << "- ";
            while (ss >> num){
                counterStars ++;
                if(find(winStars.begin(), winStars.end(), num) != winStars.end()) winStarsCtr ++;
                fOut << setw(2) << num << " ";
            }
            fOut << "=> " << counterNums << " - " << counterStars  << " | " << winNumsCtr << " - " << winStarsCtr << endl;
        }
    }
    fIn.close();
    fOut.close();
}


// EXERCISE 14

struct PersonPhone{
    char name[80];
    unsigned int phoneNumber;
};


void initFile(string fileName){
    ofstream f;
    f.open("phones.bin", ios::binary);
    unsigned int numReg = 0;
    f.write((char *) &numReg, sizeof(unsigned int));
    f.close();
}


void addPerson(string fileName){

    fstream f;
    f.open("phones.bin", ios::in | ios::out| ios::binary);

    if (!f.is_open()){
        cerr << "FIle doest not exist!";
        exit(1);
    }

    PersonPhone person;
    string temp;
    cout << "Insert name: "; getline(cin, temp); strcpy(person.name,temp.c_str());
    cout << "Inser number: "; cin >> person.phoneNumber;
    cin.ignore(10, '\n');




    unsigned int numReg;
    f.read((char *) &numReg, sizeof(unsigned int));
    numReg++;
    f.seekg(0);
    f.write((char *) &numReg, sizeof(unsigned int));

    f.seekg(sizeof(unsigned int) + (numReg - 1)*sizeof(PersonPhone)); // Appends to the end of the file
    f.write((char *) &person, sizeof(PersonPhone));
    f.close();
}

void showPeople(string fileName){

    fstream f;
    f.open(fileName, ios::in | ios::out| ios::binary);

    if (f.fail()){
        cerr << "Failed to open file;";
        exit(1);
    }

    unsigned int numReg;
    f.read((char *) &numReg, sizeof(unsigned int));

    cout << "Number of registers: " << numReg << endl;

    PersonPhone person;
    int counter = 1;
    for (int i = 0; i < numReg; ++i) {
        f.read((char *) &person, sizeof(PersonPhone));
        cout << counter << " - " << person.name  << "'s number: " << person.phoneNumber << endl;
        counter++;
    }

    f.close();
}

void removePerson(string fileName){

    fstream f;
    f.open("phones.bin", ios::in | ios::out| ios::binary);

    if (!f.is_open()){
        cerr << "FIle doest not exist!";
        exit(1);
    }

    PersonPhone person;
    unsigned int numReg;
    unsigned int chosenReg;
    cout << "Inser register: "; cin >> chosenReg;
    cin.ignore(10, '\n');


    f.read((char *) &numReg, sizeof(unsigned int));
    numReg--;
    f.seekg(0);
    f.write((char *) &numReg, sizeof(unsigned int));

    f.seekg(sizeof(unsigned int) + (chosenReg)*sizeof(PersonPhone)); // Appends to the end of the file

    while (chosenReg <= numReg+1){  // NumReg+1 gets the original size
        f.read((char *) &person, sizeof(PersonPhone));
        f.seekg(sizeof(unsigned int) + (chosenReg-1)*sizeof(PersonPhone)); // Appends to the end of the file
        f.write((char *) &person, sizeof(PersonPhone));

        chosenReg++;
    }
    char temp = 0;
    f.write((char *) &temp, sizeof(PersonPhone));

    f.close();
}

int main(){

    initFile("phones.bin");

    cout << "How many people?";
    int num; cin >> num; cin.ignore(10, '\n');
    for (int i = 0; i < num; ++i) {
        addPerson("phones.bin");
    }

    string file = "phones.bin";
    showPeople(file);
    removePerson(file);
    showPeople(file);
}