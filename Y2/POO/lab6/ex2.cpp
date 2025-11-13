#include <iostream>
#include <string>

using namespace std;
/*
friend class
friend function
virtual function
*/
class Book{
    string bookName;
    string author;
    string genre;
    double price;

    public:
        Book(string bookName = "N/A",string author= "N/A",string genre= "N/A", double price = 200.0 ): 
        bookName(bookName),author(author),genre(genre),price(price){}
        
        string getBookName() const{
            return this->bookName;
        }
};

string getLibraryName();

class Library{

    string libraryName;
    string location;
    size_t numberOfBooks = 0;
    Book books[10];

    public:
    Library(string libraryName, string location): libraryName(libraryName), location(location){}

    friend class Librarian;

    friend string getLibraryName(Library library){
        return library.libraryName;
    }
};

class ILibrarian{
    public:

    virtual void addBook(Library& library, const string bookName,const string author,const string genre,const double price) = 0;
    virtual void printBooks(const Library& library) const = 0;
    virtual const Book* getBookByName(const Library& library,const string name) const = 0;

    virtual ~ILibrarian() = default;
};

class Librarian: public ILibrarian{
    string librarianName;
    int age;
    double salary;

    public:
    Librarian(string librarianName, int age, double salary): 
    librarianName(librarianName), age(age),salary(salary){}

    const Book* getBookByName(const Library& library,const string name) const override{
        for(size_t i=0;i<library.numberOfBooks;i++)
            {
                if(name == library.books[i].getBookName())
                    return &library.books[i];
            }
        return nullptr;
    }

    void addBook(Library& library,const string bookName, const string author,const  string genre,const double price) override{
        if(library.numberOfBooks < 10){
            library.books[(library.numberOfBooks)++] = Book(bookName,author,genre,price);
        }
        else cout<<"No more room in library!";
    }

    void printBooks(const Library& library) const override{ 
        for(size_t i=0;i < library.numberOfBooks; i ++ )
        if(i == library.numberOfBooks- 1)
            cout<<'\"'<<library.books[i].getBookName()<<'\"'<<endl;
        else
            cout<<'\"'<<library.books[i].getBookName()<<'\"'<<", ";
    }
    
};



int main(){

    Library library("Biblioteca UNSTPB","Campus");
    Librarian librarian("Maricica",55,2500);
    librarian.addBook(library,"O scrisoare pierduta","I. L. Caragiale","Comedie",15);
    librarian.addBook(library,"Ultima noapte de dragoste, intaia noapte de razboi","Camil Petrescu","Roman",50);
    librarian.addBook(library,"Cartea nuntii", "G. Calinescu","Roman",50);

    cout<<"Numele bibliotecii este: "<<getLibraryName(library)<<endl;
    cout<<"Cartile disponibile: ";
    librarian.printBooks(library);
    cout<<endl;
    cout<<"Carte cautata: "<<librarian.getBookByName(library,"O scrisoare pierduta")->getBookName();
}