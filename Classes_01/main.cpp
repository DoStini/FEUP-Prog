#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <set>

using std::string, std::cout, std::cin, std::stringstream, std::vector;

class Date{
public:
    Date();
    Date(unsigned int year, unsigned int month,unsigned int day);
    Date(string yearMonthDay); // yearMonthDaymust be in format "yyyy/mm/dd"
    void setYear(unsigned int year) ;
    void setMonth(unsigned int month);
    void setDay(unsigned int day) ;
    void setDate(unsigned int year, unsigned int month, unsigned int day);
    unsigned int getYear() const;
    unsigned int getMonth() const;
    unsigned int getDay() const;
    string getDate() const;  // returns the date in format "yyyy/mm/dd"
    void show() const;
private:
    unsigned int year;
    unsigned int month;
    unsigned int day;
};

Date::Date() {
    time_t now = time(NULL);
    struct tm local = *localtime(&now);

    int year, month, day;
    year = local.tm_year + 1900;
    month = local.tm_mon + 1;
    day = local.tm_mday;

    setDate(year, month, day);
}

Date::Date(unsigned int year, unsigned int month, unsigned int day) {
    setDate(year, month, day);
}

Date::Date(string yearMonthDay) {
    stringstream ss(yearMonthDay);
    unsigned int year, month, day;
    char sep;
    ss >> year >> sep >> month >> sep >> day;
    Date::setDate(year, month, day);
}


void Date::setYear(unsigned int year) {
    this->year = year;
}
void Date::setMonth(unsigned int month) {
    this->month = month;
}
void Date::setDay(unsigned int day) {
    this->day = day;
}
void Date::setDate(unsigned int year, unsigned int month, unsigned int day) {
    setYear(year);
    setMonth(month);
    setDay(day);
}

unsigned int Date::getYear() const {
    return this->year;
}
unsigned int Date::getMonth() const {
    return this->month;
}
unsigned int Date::getDay() const {
    return this->day;
}
string Date::getDate() const {
    stringstream ss;
    ss << Date::getYear() << '/' << Date::getMonth() << '/' << Date::getDay();
    return ss.str();
}

void Date::show() const {
    cout << Date::getDate() << std::endl;
}

int mainDate() {
    Date date1("1998/6/9");
    Date date2(2001,3,9);
    Date date3;
    date1.show();
    date2.show();
    date3.show();

    return 0;
}


// exercicio 4

class Client {
public:
    Client() = default;
    Client(string name, string street, string postalCode, string city, int number = NULL);
    string getClient();
    void setClient(string name, string street, string postalCode, string city, int number);
private:
    string name;
    string street;
    string number;
    string postalCode;
    string city;
};


Client::Client(string name, string street, string postalCode, string city, int number) {
    setClient(name, street, postalCode, city, number);
}

void Client::setClient(string name, string street, string postalCode,string city, int number) {
    this -> name = name;
    this -> street = street;
    stringstream ss("");
    if (number != NULL){
        ss << number;
    }
    else{
        ss << "s/n";
    }

    this -> number = ss.str();
    this -> postalCode = postalCode;
}

string Client::getClient(){
    stringstream ss;
    ss << name << std::endl << street << ", " << number << std::endl << postalCode << " " << city;
    return ss.str();
}

class Product{
public:
    Product() = default;
    Product(string description, double price){
        this -> description = description;
        this -> price = price;
    }
public:
    string getDesc(){
        return description;
    }
    double getPrice(){
        return price;
    }
private:
    string description;
    double price;
};

class Item {
public:
    Item(Product product, int qnt){
        this -> product = product;
        this -> qnt = qnt;
        this -> total = qnt * product.getPrice();
    }

    Product getProduct(){
        return product;
    }
    int getQnt(){
        return qnt;
    }
    double getTotal(){
        return total;
    }

private:
    Product product;
    int qnt;
    double total;
};

class Invoice {
public:
    Invoice(Client &client, std::vector<Item> items){
        this -> client = client;
        this -> items = items;
        setTotal();
    }

    void setTotal(){
        double sum = 0.0;
        for (auto item: items) {
            sum += item.getTotal();
        }
        this -> total = sum;
    }

    void printInvoice(){
        cout << client.getClient() << '\n';
        cout << "Despacito\t\t\tPrice\t\tQnt\t\tTotal" << '\n';
        for (auto item: items) {
            cout << item.getProduct().getDesc() << "\t\t\t"<< item.getProduct().getPrice() << "\t\t" << item.getQnt() << "\t\t" << item.getTotal() << '\n';
        }
        cout << "Ammount Due: " << total << " euro." << std::endl;
    }

private:
    Client client;
    std::vector<Item> items;
    double total;
};

//Sort is from exercise 10

bool comp( Item &item1, Item &item2 ){
    return item1.getTotal() > item2.getTotal();
}

int test(){
    Client cliente("DEI-Feup", "Rua do Farias", "4415-523", "Porto");
    Product paper("paper", 0.99);
    Product pc("Computer", 999.90);
    Product printer("Printer", 149.90);
    std::vector<Item> items = {
            Item(paper, 100),
            Item(pc, 10),
            Item(printer, 1)
    };
    std::sort(items.begin(), items.end(), comp);
        Invoice invoice(cliente, items);
    invoice.printInvoice();

    return 0;
}


// Exercise 7
template<class T>
int compFunc(void *a, void *b){
    if (*  (T *)a > *(T *)b){
        return 1;
    }
    else if (*  (T *)a < *(T *)b){
        return -1;
    }
    else{
        return 0;
    }
}

template <class T>
vector<T> maxMin(vector<T> vec, size_t size){
    
    vector<T> out = {*vec.begin(), *(vec.end()-1)};
    return out;
};


class BetVec{
public:
    BetVec();
    void addScore(int score){
        score += score;
    };
    vector<int> *mainPtr(){ return &main;}
    vector<int> *starsPtr(){ return &stars;}
private:
    int score = 0;
    std::vector<int> main;
    std::vector<int> stars;
};

BetVec::BetVec(){
    for (int i = 1; i <= 50; ++i) main.push_back(i);
    for (int i = 1; i <= 12; ++i) stars.push_back(i);

    std::random_shuffle(main.begin(), main.end());
    std::random_shuffle(stars.begin(), stars.end());
    main.resize(5);
    stars.resize(2);
}

class BetSet{
public:
    BetSet();
private:
    std::set<int> main;
    std::set<int> stars;
};

BetSet::BetSet(){
    for (int i = 0; i < 5; ++i) main.insert(random()%50+1);
    for (int i = 0; i < 2; ++i) stars.insert(random()%12+1);
}



int testIntersection(){
    srandom(time(NULL));
    BetVec bet;
    std::vector<BetVec> bets;
    for (int i = 0; i < 5; ++i) {
        BetVec temp;
        bets.push_back(temp);
    }

    for (int j = 0; j < 5; ++j) {
        vector<int> main;
        vector<int> stars;
        std::set_intersection(bets[j].mainPtr()->begin(), bets[j].mainPtr()->end(), bet.mainPtr()->begin(), bet.mainPtr()->end(), std::inserter(main, main.end()));
    }

    random();
}



// Exercicio 8
template <typename T>
T maxVec(const std::vector<T> &vec){
    return *std::max_element(vec.begin(), vec.end());
}


template <class T>
class Vector
{
public:
    Vector();
    Vector(unsigned int size);
    Vector(unsigned int size, const T & initial);
    Vector(const Vector<T> & v);
    ~Vector();
    size_t size() const;
    bool empty() const;
    T & front();
    T & back();
    T & at(size_t index);
    void push_back(const T & value);
    void pop_back();
    void clear();
private:
    T * buffer;
    size_t bufferSize; // add an attribute 'size' if you find it useful
};

template <class T>
Vector<T>::Vector() {
    buffer = (T *) malloc(0);
    bufferSize = 0;
}
template <class T>
Vector<T>::Vector(unsigned int size) {
    bufferSize = size* sizeof(T);
    buffer = (T *) calloc(bufferSize, 0);
}
template <class T>
Vector<T>::Vector(unsigned int size, const T & initial) {
    bufferSize = size * sizeof(T);
    buffer = (T *) calloc(bufferSize, initial);
}
template <class T>
Vector<T>::Vector(const Vector<T> & v) {
    bufferSize = v.size()  * sizeof(T);
    buffer = (T *) malloc(bufferSize);
    for (int i = 0; i < bufferSize; ++i) {
        buffer[i] = v[i];
    }
}
template <class T>
Vector<T>::~Vector() {
    free(buffer);
}
template <class T>
size_t Vector<T>::size() const {
    return bufferSize/sizeof(T);
}
template <class T>
bool Vector<T>::empty() const{
    return bufferSize == 0;
}
template <class T>
void Vector<T>::push_back(const T &value) {
    bufferSize += sizeof(T);
    buffer = (T *) realloc(buffer, bufferSize);
    buffer[bufferSize / sizeof(T)-1] = value;
}
template <class T>
void Vector<T>::pop_back() {
    bufferSize -= sizeof(T);
    buffer = (T *) realloc(buffer, bufferSize);
}


// exercise 9

bool cmp(std::string s1, std::string s2){
    return s1 > s2;
}

void removeDup1(std::vector<std::string> &words){
    std::sort(words.begin(), words.end());

    int i = 0;
    while ( i < words.size()){
        if (i != 0 && words[i] == words[i-1]){
            words.erase(words.begin() + i);
            continue;
        }
        i++;
    }
}
void removeDup2(std::vector<std::string> &words){
    std::sort(words.begin(), words.end());
    auto last = std::unique(words.begin(), words.end());
    words.erase(last, words.end());
}




// Exericio 15
bool operator==(const Date &left, const Date &right){
    left.getDate() == right.getDate();
}

bool operator!=(const Date &left, const Date &right){
    left.getDate() != right.getDate();
}

bool operator>=(const Date &left, const Date &right){
    if (left.getYear() > right.getYear()) return true;
    if (left.getYear() < right.getYear()) return false;
    if (left.getMonth() > right.getMonth()) return true;
    if (left.getMonth() < right.getMonth()) return false;
    return left.getDay() >= right.getDay();
}

std::istream& operator >> (std::istream &input, const Date &date){
    input >> date.getDate();
    return input;
}

std::ostream& operator << (std::ostream &output, const Date &date){
    output << date.getDay() << "/";
    return output;
}




// Exercicio 16


class inRange{
public:
    inRange(){
        min = INT32_MIN;
        max = INT32_MAX;
    }
    inRange(int min){
        this->min = min;
        max = INT32_MAX;
    }
    inRange(int min, int max){
        this->min = min;
        this->max = max;
    }

    bool operator()(int num){
        return num < min || num > max;
    }

private:
    int min;
    int max;
};


void test16(){
    vector<int> a = {-1,-5,7,9,10,-21, 50, 21, -48};
    vector<int> b = {-1,-5,7,9,10,-21, 50, 21, -48};
    vector<int> c = {-1,-5,7,9,10,-21, 50, 21, -48};
    inRange comp1(5);
    inRange comp2(-5, 20);
    auto newIt = std::remove_if(a.begin(), a.end(), [](int num){return num < 0;});
    a.erase(newIt, a.end());
    auto newIt2 = std::remove_if(b.begin(), b.end(), comp1);
    b.erase(newIt2, b.end());
    auto newIt3 = std::remove_if(c.begin(), c.end(), comp2);
    c.erase(newIt3, c.end());
    cout << 2;
}

int main(){
    test16();
    return 0;
}
