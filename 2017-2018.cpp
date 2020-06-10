#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>

// https://moodle.up.pt/pluginfile.php/106512/mod_resource/content/2/PROG_2017-2018_ExameNormal_v08.pdf

void toUpperStr( std::string& s )
{
    for (int x = 0; x < s.length(); x++){
        s[x] = std::toupper(s[x]);
    }
}

std::string transformLine( std::string s )
{
    char min = 'A';
    char max = 'z';
    toUpperStr(s);
    for (int i = 0; i < s.length(); i++){
        if (s[i] < min || s[i] > max) s[i] = ' ';
    }
    return s;
}

void decomposeLine( std::string line,  std::vector<std::string> &words)
{

    line = transformLine(line);
    std::stringstream ss(line);
    std::string temp;
    ss >> temp;
    while(!ss.eof()){
        words.push_back(temp);
        ss >> temp;
    }
}

void writeLines(){
    std::ifstream in;
    std::ofstream out;
    in.open("C:\\text.txt");
    out.open("words.txt");

    std::string tempStr;

    while(std::getline(in, tempStr)){
        if (in.eof()) break;
        std::vector<std::string> tempVec;
        decomposeLine(tempStr, tempVec);

        std::sort(tempVec.begin(), tempVec.end());

        for (int i = 0; i < tempVec.size(); i++){
            out << tempVec[i] << ' ';
        }
        out << '\n';
    }
    in.close();
    out.close();
}

// Alinea e: Na parte final do código, antes da escrita, teriamos de usar algum algoritmo da stl para remover items repetidos

// Outra hipotese seria fazer
/*
int i = 0;
while(i < tempVec.size() - 1){
    if (tempVec[i] == tempVec[i+1]){
        tempVec.erase(tempVec.begin() + i+1);
        continue;
    }
    i++;
}
 */

// 2a) Embora nenhuma delas tenha o default constructor, a classe board, no seu constructor tem pré definida os valores
// das variaveis, isto é, se não for dados nenuns argumentos ao chamar a classe, tomarao o valor de 10 e 10

/*
Board::Board(size_t numLines = 10, size_t numColumns = 10){
    for (int i = 0; i < numLines; i++){
        vector<int> temp(numColumns, -1);
        board.push_back(temp);
    }
}



bool Board::canPutShip(Position pos, char dir, size_t size)  {
    switch (dir)// TO DO
    {
        case 'H': // TO DO: test if ship with length 'size' can be put at 'pos', in horizontal direction
            if(pos.lin < 0 || pos.lin >= numColumns || pos.col < 0 || pos.col >= numLines) return false;

            for (int i = 0; i < size; i++){
                if (board[lin][col+i] != -1) return false;
            }
            return true;


        case 'V': // TO DO, just this line: test if ship ... can be put in vertical direction
            // DONE. This piece of code was correctly implemented but was carelessly erased …
    }
}
*/
/*
float average(const int grades[], int numStudents){
    int sum=0;
    for (int i = 0; i < numStudents; i++) {sum+=grades[i];}
    return ((float) sum) / numStudents;
}

void read(int *grades){
    int size;
    int grade;
    cin >> size;
    grades = (int *) malloc(size*sizeof(int));
    readGrades(grades, size)
}

*/
/*
void ex3b(){
    auto it = find(v.begin(), v.end(), "31");
    if (it != v.end()){ cout << "We found 31 at index " << it - v.begin();}
    else {cout << "Value 31 not found";}
}
*/

// Ex 3c
// Como o set é um data type de dados ordenados, os seus elementos têm de ser comparaveis, pelo que a struct position não o é


class FeupPerson {
public:
    FeupPerson(int id, std::string name, std::string address) {
        this->id = id;
        this->name = name;
        this->address = address;
    }
    int getId(){
        return id;
    }
    void changeAddress(std::string newAddress){
        address = newAddress;
    }

    virtual void showRecord() = 0;

private: //accessible inside the class and by all of its subclasses
    int id;
    std::string name;
    std::string address;
};

void FeupPerson::showRecord(){
    std::cout << id << ": " << name << ": " << address << std::endl;
}

class Student : public FeupPerson {
public:
    Student(int id, std::string name, std::string address, std::string
    course, int year) : FeupPerson(id, name, address){
        this->id = this->getId();
        this -> course = course;
        this -> year = year;
    }
    void changeCourse(int newCourse);
    void showRecord(){
        std::cout << this->getId() << ": " << course << ": " << year << std::endl;
    }
private:
    std::string course;
    int year, id;
};

int main() {
    FeupPerson *ptr;
    //ptr = new Student(5, "Nuno", "geijop", "inph", 2001);
    ptr = new FeupPerson(5, "Nuno", "geijop");
    ptr->showRecord();
}
