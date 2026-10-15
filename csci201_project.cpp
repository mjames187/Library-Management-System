#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

enum class Genre { Fiction, NonFiction, Mystery, Science, Biography };

std::ostream& operator << (std::ostream& os, Genre g){
    switch(g){
        case Genre::Fiction:
            os << "Fiction";
            break;
        case Genre::NonFiction:
            os << "NonFiction";
            break;
        case Genre::Mystery:
            os << "Mystery";
            break;
        case Genre::Science:
            os << "Science";
            break;
        case Genre::Biography:
            os << "Biography";
            break;
    }

    return os;
}

enum class BookStatus { Available, CheckedOut };

std::ostream& operator << (std::ostream& os, BookStatus s){
    switch(s){
        case BookStatus::Available:
            os << "Available";
            break;
        case BookStatus::CheckedOut:
            os << "CheckedOut";
            break;
    }

    return os;
}

enum class TimeZone { AoE, ST, HT, AKT, PT, MT, CT, ET, AST, ChT, WAKT};

std::ostream& operator << (std::ostream& os, TimeZone z){
    switch(z){
        case TimeZone::AoE:
            os << "AoE";
            break;
         case TimeZone::ST:
            os << "ST";
            break;
         case TimeZone::HT:
            os << "HT";
            break;
         case TimeZone::AKT:
            os << "AKT";
            break;
         case TimeZone::PT:
            os << "PT";
            break;
         case TimeZone::MT:
            os << "MT";
            break;
         case TimeZone::CT:
            os << "CT";
            break;
         case TimeZone::ET:
            os << "ET";
            break;
         case TimeZone::AST:
            os << "AST";
            break;
         case TimeZone::ChT:
            os << "ChT";
            break;
         case TimeZone::WAKT:
            os << "WAKT";
            break;
    }

    return os;
}

enum class AM_PM { am, pm };

std::ostream& operator << (std::ostream& os, AM_PM t){
    switch(t){
        case AM_PM::am:
            os << "a.m.";
            break;
         case AM_PM::pm:
            os << "p.m.";
            break;
    }

    return os;
}

void textBuffer(){ //Used for separating text in the menu for the sake of readability.
    std::cout << "------------------------------" << std::endl;
}

class Book {
    protected:
        std::string title;
        std::string author;
        Genre genre;
        BookStatus status;
    public:
        Book(std::string t, std::string a, Genre g){
            title = t;
            author = a;
            genre = g;
            status = BookStatus::Available;
        }
        virtual ~Book() = default;
        virtual void displayInfo() const{
            std::cout << "Title: " << title << std::endl;
            std::cout << "Author: " << author << std::endl;
            std::cout << "Genre: " << genre << std::endl;
            std::cout << "Status: " << status << std::endl;
        }
        void setStatus(BookStatus s){
            status = s;
        }
        BookStatus getStatus() const{
            return status;
        }
        bool operator==(const Book& other) const{
            if(title==other.title && author==other.author && genre==other.genre && status==other.status){
                return true;
            }
            else{
                return false;
            }
        }
        friend std::ostream& operator<<(std::ostream& os, const Book& b){
            os << b.title;
            return os;
        }
        std::string getTitle(){
            return title;
        }
        std::string getAuthor(){
            return author;
        }
        Genre getGenre(){
            return genre;
        }
        virtual std::string getCategory(){
            return "N/A";
        }
        virtual std::string getSpecialNumber(){
            return "N/A";
        }
};

class EBook : public Book {
    protected:
        std::string category;
        double fileSizeMB;
    public:
        EBook(std::string t, std::string a, Genre g, double size) : Book(t,a,g){
            category = "EBook";
            fileSizeMB = size;
        }
        void displayInfo() const override{
            std::cout << "Title: " << title << std::endl;
            std::cout << "Author: " << author << std::endl;
            std::cout << "Genre: " << genre << std::endl;
            std::cout << "File Size: " << fileSizeMB << " mb" << std::endl;
            std::cout << "Status: " << status << std::endl;
        }
        std::string getCategory() override{
            return category;
        }
        std::string getSpecialNumber() override{
            return std::to_string(fileSizeMB);
        }
};

class PrintedBook : public Book {
    protected:
        std::string category;
        int pageCount;
    public:
        PrintedBook(std::string t, std::string a, Genre g, int pages) : Book(t,a,g){
            category = "Printed";
            pageCount = pages;
        }
        void displayInfo() const override{
            std::cout << "Title: " << title << std::endl;
            std::cout << "Author: " << author << std::endl;
            std::cout << "Genre: " << genre << std::endl;
            std::cout << "Page Count: " << pageCount << std::endl;
            std::cout << "Status: " << status << std::endl;
        }
        std::string getCategory(){
            return category;
        }
        int getPages(){
            return pageCount;
        }
        std::string getSpecialNumber(){
            return std::to_string(pageCount);
        }
};

class Patron {
    protected:
        std::string name;
        int id;
        std::vector<Book*> borrowedBooks;
    public:
        Patron(std::string n, int i){
            name = n;
            id = i;
        }
        void borrowBook(Book* b){
            borrowedBooks.push_back(b);
        }
        void returnBook(Book* b){
            for(int i=0; i<borrowedBooks.size(); ++i){
                if(borrowedBooks.at(i) == b){
                    borrowedBooks.erase(std::next(begin(borrowedBooks), + i));
                    break;
                }
            }
        }
        void displayPatron() const{
            std::cout << "Name: " << name << std::endl;
            std::cout << "ID: " << id << std::endl;
            if(borrowedBooks.size()>=1){
                std::cout << "Borrowed Books:" << std::endl;
                for(int i = 0; i < borrowedBooks.size(); ++i){
                    std::cout << borrowedBooks.at(i)->getTitle() << std::endl;
                }
            }
        }
        bool operator==(const Patron& other) const{
            if(name==other.name && id==other.id){
                return true;
            }
            else{
                return false;
            }
        }
        friend std::ostream& operator<<(std::ostream& os, const Patron& p){
            os << p.name << "(ID: " << p.id << ")";
            return os;
        }
        std::string getName(){
            return name;
        }
        int getId() const{
            return id;
        }
        std::vector<Book*> getBorrowed(){
            return borrowedBooks;
        }
};

class Date {
    protected:
        std::string month;
        std::string day;
        int year;
    public:
        Date(std::string m, std::string d, int y){
            month = m;
            day = d;
            year = y;
        }
        std::string getMonth(){
            return month;
        }
        std::string getDay(){
            return day;
        }
        int getYear(){
            return year;
        }
        friend std::ostream& operator<<(std::ostream& os, const Date& d){
            os << d.month << "/" << d.day << "/" << d.year;
            return os;
        }
};

Date calculateDueDate(Date d){ //Converts user input into valid arguments to construct a Date object.
    int newMonth;
    int newDay;
    int newYear;
    int threshold;
    std::string outputDay;

    newMonth = stoi(d.getMonth());
    newDay = stoi(d.getDay()) + 28;
    newYear = d.getYear();
    if(d.getMonth()=="01"){
        threshold = 31;
    }
    else if(d.getMonth()=="02"){
        threshold = 28;
    }
    else if(d.getMonth()=="03"){
        threshold = 31;
    }
    else if(d.getMonth()=="04"){
        threshold = 30;
    }
    else if(d.getMonth()=="05"){
        threshold = 31;
    }
    else if(d.getMonth()=="06"){
        threshold = 30;
    }
    else if(d.getMonth()=="07"){
        threshold = 31;
    }
    else if(d.getMonth()=="08"){
        threshold = 31;
    }
    else if(d.getMonth()=="09"){
        threshold = 30;
    }
    else if(d.getMonth()=="10"){
        threshold = 31;
    }
    else if(d.getMonth()=="11"){
        threshold = 30;
    }
    else if(d.getMonth()=="12"){
        threshold = 31;
    }

    while(newDay > threshold){
        newMonth++;
        newDay-=threshold;
        if(newMonth > 12){
            newYear++;
            newMonth = 1;
        }
    }

    if(newDay<10){
        outputDay = "0" + std::to_string(newDay);
    }
    else{
        outputDay = std::to_string(newDay);
    }

    switch(newMonth){
        case 1:
            return Date("01",outputDay,newYear);
        case 2:
            return Date("02",outputDay,newYear);
        case 3:
            return Date("03",outputDay,newYear);
        case 4:
            return Date("04",outputDay,newYear);
        case 5:
            return Date("05",outputDay,newYear);
        case 6:
            return Date("06",outputDay,newYear);
        case 7:
            return Date("07",outputDay,newYear);
        case 8:
            return Date("08",outputDay,newYear);
        case 9:
            return Date("09",outputDay,newYear);
        case 10:
            return Date("10",outputDay,newYear);
        case 11:
            return Date("11",outputDay,newYear);
        case 12:
            return Date("12",outputDay,newYear);
    }
    return Date("01",outputDay,newYear);
}

class Time {
    protected:
        int hour;
        int minute;
        TimeZone timezone;
        AM_PM am_pm;
    public:
        Time(int h, int m, TimeZone z, AM_PM t){
            hour = h;
            minute = m;
            timezone = z;
            am_pm = t;
        }
        friend std::ostream& operator<<(std::ostream& os, const Time& t){
            os << t.hour << ":";
            if(t.minute<10){
                os << "0";
            }
            os << t.minute << " " << t.am_pm << " " << t.timezone;
            return os;
        }
};

Time parseTime(std::string h, std::string m, std::string z, std::string t){ //Converts user input into valid arguments to construct a Time object.
    TimeZone newTimeZone;
    AM_PM newAM_PM;
    if(z=="AoE"){
        newTimeZone = TimeZone::AoE;
    }
    else if(z=="ST" || z=="st"){
        newTimeZone = TimeZone::ST;
    }
    else if(z=="HT" || z=="ht"){
        newTimeZone = TimeZone::HT;
    }
    else if(z=="AKT" || z=="akt"){
        newTimeZone = TimeZone::AKT;
    }
    else if(z=="PT" || z=="pt"){
        newTimeZone = TimeZone::PT;
    }
    else if(z=="MT" || z=="mt"){
        newTimeZone = TimeZone::MT;
    }
    else if(z=="CT" || z=="ct"){
        newTimeZone = TimeZone::CT;
    }
    else if(z=="ET" || z=="et"){
        newTimeZone = TimeZone::ET;
    }
    else if(z=="AST" || z=="ast"){
        newTimeZone = TimeZone::AST;
    }
    else if(z=="ChT" || z=="CHT" || z=="cht"){
        newTimeZone = TimeZone::ChT;
    }
    else if(z=="WAKT" || z=="wakt"){
        newTimeZone = TimeZone::WAKT;
    }

    if(t=="a.m." || t=="A.M." || t=="AM" || t =="am"){
        newAM_PM = AM_PM::am;
    }
    else if(t=="p.m." || t=="P.M." || t=="PM" || t =="pm"){
        newAM_PM = AM_PM::pm;
    }

    return Time(stoi(h), stoi(m),newTimeZone,newAM_PM);
}

class Transaction {
    protected:
        int patronId;
        std::string bookTitle;
        Date date;
        Time time;
    public:
        Transaction(int pid, std::string bt, Date d, Time t) : date(d), time(t){
            patronId = pid;
            bookTitle = bt;
        }
        void displayTransaction() const{
            std::cout << "Patron " << patronId << " borrowed " << bookTitle << " on " << date << " at " << time << "." << std::endl;
            std::cout << bookTitle << " is due on " << calculateDueDate(date) << "." << std::endl;
        }
        int getId() const{
            return patronId;
        }
        std::string getTitle(){
            return bookTitle;
        }
        Date getDate(){
            return date;
        }
};

class Library {
    protected:
        std::vector<Book*> books;
        std::vector<Patron> patrons;
        std::vector<Transaction> transactions;
    public:
        ~Library() = default;
        template <typename T>
        void parseBook(std::string g, std::string t, std::string a, std::string c, T n){ //Converts user input into valid arguments to construct a Book object.
            Genre newGenre;
            int location;
            newGenre = Genre::Fiction;
            location = 0;
            if(g=="NonFiction"){
                newGenre = Genre::NonFiction;
            }
            else if(g=="Mystery"){
                newGenre = Genre::Mystery;
            }
            else if(g=="Science"){
                newGenre = Genre::Science;
            }
            else if(g=="Biography"){
                newGenre = Genre::Biography;
            }
            if(c=="EBook"){
                Book* ptr = new EBook(t,a,newGenre,n);
                books.push_back(ptr);
            }
            else if(c=="Printed"){
                Book* ptr = new PrintedBook(t,a,newGenre,n);
                books.push_back(ptr);
            }
        }
        void loadData(){
            std::string line;
            std::string genre;
            std::string title;
            std::string author;
            std::string category;
            std::string specialNumber;
            std::string id;
            std::string name;

            std::ifstream file("books.txt");
            if (!file) throw std::runtime_error("Failed to open books file.");
            if (file.is_open()) {
                while (getline(file, line)) {
                    genre = line.substr(0,line.find(","));
                    line.erase(0,line.find(",")+1);
                    title = line.substr(0,line.find(","));
                    line.erase(0,line.find(",")+1);
                    author = line.substr(0,line.find(","));
                    line.erase(0,line.find(",")+1);
                    category = line.substr(0,line.find(","));
                    line.erase(0,line.find(",")+1);
                    specialNumber = line.substr(0,line.back());
                    line.erase(0,line.back());
                    if(category=="EBook"){
                        parseBook(genre,title,author,category,std::stod(specialNumber));
                    }
                    else if(category=="Printed"){
                        parseBook(genre,title,author,category,std::stoi(specialNumber));
                    }
                }
                file.close();
            }
            std::ifstream secFile("patrons.txt");
            if (!secFile) throw std::runtime_error("Failed to open patrons file.");
            if (secFile.is_open()) {
                while (getline(secFile, line)) {
                    id = line.substr(0,line.find(","));
                    line.erase(0,line.find(",")+1);
                    name = line.substr(0,line.back());
                    line.erase(0,line.back());
                    patrons.push_back(Patron(name,std::stoi(id)));
                }
                secFile.close();
            }
        }
        void saveData(){
            std::fstream File("books.txt");
            if (!File) throw std::runtime_error("Failed to save to books file.");
            if (File.is_open()){
                for(int i = 0; i < books.size(); ++i){
                    File << books.at(i)->getGenre() << "," << books.at(i)->getTitle() << "," << books.at(i)->getAuthor() << "," << books.at(i)->getCategory() << "," << books.at(i)->getSpecialNumber() << std::endl;
                }
                File.close();
            }
            std::fstream secFile("patrons.txt");
            if (!secFile) throw std::runtime_error("Failed to save to patrons file.");
            if (secFile.is_open()){
                for(int i = 0; i < patrons.size(); ++i){
                    secFile << patrons.at(i).getId() << "," << patrons.at(i).getName() << std::endl;
                }
                secFile.close();
            }
        }
        void addBook(Book* b){
            books.push_back(b);
        }
        void addPatron(const Patron& p){
            patrons.push_back(p);
        }
        void checkoutBook(int patronId, std::string title, Date date, Time time){ //Finds, confirms, and edits data in the books and patrons vectors to check out a book.
            try{
                for(int i = 0; i < books.size(); ++i){
                    if(books.at(i)->getTitle() == title){
                        for(int j = 0; j < patrons.size(); ++j){
                            if(patrons.at(j).getId() == patronId){
                                patrons.at(j).borrowBook(books.at(i));
                                books.at(i)->setStatus(BookStatus::CheckedOut);
                                transactions.push_back(Transaction(patronId, title, date, time));
                                transactions.back().displayTransaction();
                                textBuffer();
                                break;
                            }
                            else if(j==patrons.size()-1){
                                throw "Patron not found.";
                            }
                        }
                        break;
                    }
                    else if(i==books.size()-1){
                        throw "Book not found.";
                    }
                }
            }
            catch (const char* msg) {
                std::cout << "Error: " << msg << std::endl;
                textBuffer();
            }
        }

        void returnBook(int patronId, std::string title){ //Finds, confirms, and edits data in the books and patrons vectors to return a book.
            try{
                for(int i = 0; i < patrons.size(); ++i){
                    if(patrons.at(i).getId() == patronId){
                        if(patrons.at(i).getBorrowed().size()>=1){
                            for(int f = 0; f < patrons.at(i).getBorrowed().size(); ++f){
                                if(patrons.at(i).getBorrowed().at(f)->getTitle()==title){
                                    for(int j = 0; j < books.size(); ++j){
                                        if(books.at(j)->getTitle() == title){
                                            patrons.at(i).returnBook(books.at(j));
                                            books.at(j)->setStatus(BookStatus::Available);
                                            std::cout << "Patron " << patronId << " has returned " << title << "." << std::endl;
                                            break;
                                        }
                                    }
                                }
                                else if(f==patrons.at(i).getBorrowed().size()-1){
                                    throw "Patron has not borrowed the entered book.";
                                }
                            }
                        }
                        else{
                            throw "Patron has not borrowed any books.";
                        }
                        break;
                    }
                    else if(i==patrons.size()-1){
                        throw "Patron not found.";
                    }
                }
                textBuffer();
            }
            catch (const char* msg) {
                std::cout << "Error: " << msg << std::endl;
                textBuffer();
            }
        }

        void displayBooks() const{
            for(int i = 0; i < books.size(); ++i){
                books.at(i)->displayInfo();
                textBuffer();
            }
        }
        void displayPatrons() const{
            for(int i = 0; i < patrons.size(); ++i){
                patrons.at(i).displayPatron();
                textBuffer();
            }
        }

        std::vector<Book*> getBooks(){
            return books;
        }

        std::vector<Patron> getPatrons(){
            return patrons;
        }
};

int main(){
    
    Library library; //The library this program is working with.
    std::string centralInput; //Master input that navigates to the sub-menus.
    std::string subInput; //Navigates sub-menus.
    std::string pidInput; //Patron ID input.
    std::string searchQuery; //Book search input.
    std::string titleInput; //Book title input.
    std::string month; //Date/time inputs.
    std::string day;
    std::string year;
    std::string hour;
    std::string minute;
    std::string timezone;
    std::string am_pm;
    std::string title; //Book creation inputs.
    std::string author;
    std::string genre;
    std::string category;
    std::string specialNumber;
    int max; //Used to find the next unused ID when registering a patron.
    std::string name; //Patron name input.
    centralInput = "0";

    library.loadData();
    
    std::cout << "Welcome to the Library Management System." << std::endl;
    std::cout << "Type and enter a number to select a course of action." << std::endl;
    textBuffer();

    while(centralInput!="-1"){ //Loop returns to main menu unless -1 is entered at this point.
        subInput = "0";
        std::cout << "Main Menu" << std:: endl;
        std::cout << "(1) View books and patrons" << std::endl;
        std::cout << "(2) Check out or return books" << std::endl;
        std::cout << "(3) Add new books or patrons" << std::endl;
        std::cout << "(-1) Exit program" << std:: endl;
        getline(std::cin,centralInput);
        textBuffer();

        if(centralInput=="1"){
            while(subInput!="4"){ //Until the main menu is returned to, the user can use this menu's options as many times as desired.
                std::cout << "(1) View books" << std::endl;
                std::cout << "(2) Search books" << std::endl;
                std::cout << "(3) View patrons" << std::endl;
                std::cout << "(4) Main Menu" << std:: endl;
                getline(std::cin,subInput);
                textBuffer();
                if(subInput=="1"){
                    library.displayBooks();
                }
                else if(subInput=="2"){ //Locates substrings based on the input placed in searchQuery.
                    std::cout << "(1) Search by title" << std::endl;
                    std::cout << "(2) Search by author" << std::endl;
                    getline(std::cin,subInput);
                    textBuffer();
                    std::cout << "Enter search query: ";
                    getline(std::cin,searchQuery);
                    for(int i = 0;i < library.getBooks().size(); ++i){
                        if(subInput=="1"){
                            if(library.getBooks().at(i)->getTitle().find(searchQuery)!=std::string::npos){
                                library.getBooks().at(i)->displayInfo();
                                textBuffer();
                            }
                        }
                        else if(subInput=="2"){
                            if(library.getBooks().at(i)->getAuthor().find(searchQuery)!=std::string::npos){
                                library.getBooks().at(i)->displayInfo();
                                textBuffer();
                            }
                        }
                    }
                }
                else if(subInput=="3"){
                    library.displayPatrons();
                }
            }
        }

        if(centralInput=="2"){
            while(subInput!="3"){ //Until the main menu is returned to, the user can use this menu's options as many times as desired.
                subInput = "0";
                std::cout << "(1) Check out a book" << std::endl;
                std::cout << "(2) Return a book" << std::endl;
                std::cout << "(3) Main Menu" << std::endl;
                getline(std::cin,subInput);
                textBuffer();
                if(subInput=="1"){ //A long series of inputs that are validated at each step.
                    std::cout << "Patron ID: ";
                    getline(std::cin,pidInput);
                    std::cout << std::endl;
                    std::cout << "Book Title: ";
                    getline(std::cin, titleInput);
                    std::cout << std::endl;
                    std::cout << "Enter date (MM/DD/YYYY)" << std::endl;
                    std::cout << std::endl;
                    std::cout << "Month: ";
                    try{
                        getline(std::cin, month);
                        std::cout << std::endl;
                        for(int i = 0;i < month.size(); ++i){
                            if(!isdigit(month.at(i))){
                                throw "Invalid month entered.";
                            }
                        }
                        if(stoi(month)<10 && month!="01" && month!="02" && month!="03" && month!="04" && month!="05" && month!="06" && month!="07" && month!="08" && month!="09"){
                            throw "Invalid month entered.";
                        }
                        if(stoi(month)<1 || stoi(month)>12){
                            throw "Invalid month entered.";
                        }
                        std::cout << "Day: ";
                        getline(std::cin, day);
                        for(int i = 0;i < day.size(); ++i){
                            if(!isdigit(day.at(i))){
                                throw "Invalid day entered.";
                            }
                        }
                        if(stoi(day)<10 && day!="01" && day!="02" && day!="03" && day!="04" && day!="05" && day!="06" && day!="07" && day!="08" && day!="09"){
                            throw "Invalid day entered.";
                        }
                        if(stoi(day)<1){
                            throw "Invalid day entered.";
                        }
                        std::cout << std::endl;
                        std::cout << "Year: ";
                        getline(std::cin, year);
                        std::cout << std::endl;
                        for(int i = 0;i < year.size(); ++i){
                            if(!isdigit(year.at(i))){
                                throw "Invalid year entered.";
                            }
                        }
                        std::cout << "Enter time" << std::endl;
                        std::cout << std::endl;
                        std::cout << "Timezone: ";
                        getline(std::cin, timezone);
                        if(timezone!="AoE" && timezone!="aoe" && timezone!="ST" && timezone!= "st" && timezone!="HT" && timezone!="ht" && timezone!="AKT" && timezone!="akt" && timezone!="PT" && timezone!="pt" && timezone!="MT" && timezone!= "mt" && timezone!="CT" && timezone!="ct" && timezone!="ET" && timezone!="et" && timezone!="AST" && timezone!="ast" && timezone!="ChT" && timezone!="cht" && timezone!="WAKT" && timezone!="wakt"){
                            throw "Invalid timezone entered.";
                        }
                        std::cout << std::endl;
                        std::cout << "Hour: ";
                        getline(std::cin, hour);
                        std::cout << std::endl;
                        for(int i = 0;i < hour.size(); ++i){
                            if(!isdigit(hour.at(i))){
                                throw "Invalid hour entered.";
                            }
                        }
                        if(stoi(hour)<1 || stoi(hour)>12){
                            throw "Invalid hour entered.";
                        }
                        std::cout << "Minute: ";
                        getline(std::cin, minute);
                        std::cout << std::endl;
                        for(int i = 0;i < minute.size(); ++i){
                            if(!isdigit(minute.at(i))){
                                throw "Invalid minute entered.";
                            }
                        }
                        if(stoi(minute)<10 && minute!="00" && minute!="01" && minute!="02" && minute!="03" && minute!="04" && minute!="05" && minute!="06" && minute!="07" && minute!="08" && minute!="09"){
                            throw "Invalid minute entered.";
                        }
                        if(stoi(minute)<0 || stoi(minute)>59){
                            throw "Invalid minute entered.";
                        }
                        std::cout << "a.m./p.m.: ";
                        getline(std::cin, am_pm);
                        if(am_pm!="a.m." && am_pm!="A.M." && am_pm!="am" && am_pm!="AM" && am_pm!="p.m." && am_pm!="P.M." && am_pm!="pm" && am_pm!="PM"){
                            throw "Invalid a.m./p.m. entered.";
                        }
                        std::cout << std::endl;
                        library.checkoutBook(stoi(pidInput),titleInput,Date(month,day,stoi(year)),parseTime(hour,minute,timezone,am_pm));
                    }
                    catch (const char* msg) {
                        std::cout << "Error: " << msg << std::endl;
                        textBuffer();
                    }
                }
                if(subInput=="2"){
                    try{
                        std::cout << "Patron ID: ";
                        getline(std::cin,pidInput);
                        std::cout << std::endl;
                        for(int i = 0;i < pidInput.size(); ++i){
                            if(!isdigit(pidInput.at(i))){
                                throw "Invalid patron ID entered.";
                            }
                        }
                        std::cout << "Book Title: ";
                        getline(std::cin, titleInput);
                        std::cout << std::endl;
                        library.returnBook(stoi(pidInput),titleInput);
                    }
                    catch (const char* msg) {
                        std::cout << "Error: " << msg << std::endl;
                        textBuffer();
                    }
                }
            }
        }

        if(centralInput=="3"){
            while(subInput!="3"){ //Until the main menu is returned to, the user can use this menu's options as many times as desired.
                std::cout << "(1) Add new book" << std::endl;
                std::cout << "(2) Add new patron" << std::endl;
                std::cout << "(3) Main Menu" << std::endl;
                getline(std::cin,subInput);
                textBuffer();
                if(subInput=="1"){ //A section structured the same as the one that handles checking out a book. This one handles book creation.
                    std::cout << "Enter title: ";
                    getline(std::cin,title);
                    std::cout << std::endl;
                    std::cout << "Enter author: ";
                    getline(std::cin,author);
                    std::cout << std::endl;
                    std::cout << "Enter genre: ";
                    try{
                        getline(std::cin,genre);
                        if(genre!="Fiction" && genre!="NonFiction" && genre!="Mystery" && genre!="Science" && genre!="Biography"){
                            throw "Invalid genre entered.";
                        }
                        std::cout << std::endl;
                        std::cout << "Enter category (\"EBook\" or \"Printed\"): ";
                        getline(std::cin,category);
                        std::cout << std::endl;
                    
                        if(category=="EBook"){
                            std::cout << "Enter file size in mb (number only): ";
                            getline(std::cin,specialNumber);
                            std::cout << std::endl;
                            library.parseBook(genre,title,author,category,stod(specialNumber));
                            std::cout << "Book added successfully." << std::endl;
                            textBuffer();
                            library.saveData();
                        }
                        else if(category=="Printed"){
                            std::cout << "Enter page count: ";
                            getline(std::cin,specialNumber);
                            std::cout << std::endl;
                            for(int i = 0; i < specialNumber.size(); ++i){
                                if(!isdigit(specialNumber.at(i))){
                                    throw "Invalid page count entered.";
                                    break;
                                }
                            }
                            library.parseBook(genre,title,author,category,stoi(specialNumber));
                            std::cout << "Book added successfully." << std::endl;
                            textBuffer();
                            library.saveData();
                        }
                        else{
                            throw "Invalid category entered.";
                        }
                    }
                    catch (const char* msg) {
                        std::cout << "Error: " << msg << std::endl;
                        textBuffer();
                    }
                }
                if(subInput=="2"){ //Finds the next empty ID and assigns the inputted name to that ID.
                    max = 0;
                    for(int i = 0; i < library.getPatrons().size(); ++i){
                        if(max < library.getPatrons().at(i).getId()){
                            max = library.getPatrons().at(i).getId();
                        }
                    }
                    max++;
                    std::cout << "Creating patron with ID " << max << std::endl;
                    std::cout << "Enter patron's name: ";
                    getline(std::cin,name);
                    std::cout << std::endl;
                    library.addPatron(Patron(name, max));
                    std::cout << "Registered " << name << " to patron ID " << max << "." << std::endl;
                    textBuffer();
                    library.saveData();
                }
            }
        }
    
    
    }

    //Upon -1 being entered, the loop will be exited and lead here, the program will close.
    std::cout << "Closing Library Management System..." << std::endl;
    return 0;
}