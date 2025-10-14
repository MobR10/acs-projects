//  a) Să se implementeze o clasă Sibling. Atributele din interiorul clasei
//  vor fi cele de nume,  prenume și vârstă, toate alocate prin intermediul pointerilor.
//  Pentru această clasă trebuie să aveți și un copy constructor.
//  Creați un obiect sibling1. Creați un obiect sibling2 cu ajutorul copy constructorului
//  și faceți update la prenume și vârstă. Afișați atributele fiecărui obiect. 2p
//
//  b) Folosiți un LLM (precum Gemini sau ChatGPT) cu următorul prompt (în engleză, pentru rezultate mai bune):
//  "Write a C++ class named Student. It should have a std::string for the name and a
//  dynamic array of floats to store grades. Include a constructor that takes the name and
//  the number of grades, and a destructor to clean up the memory."
//  Creați un obiect Student, numit student1, cu câteva note.
//  Creați un al doilea obiect Student, student2, copiindu-l pe primul: Student student2 = student1.
//  Modificați o notă pentru student2. Afișați notele pentru ambii studenți, student1 și student2.
//  Explicați outputul și reparați codul în caz că nu funcționează cum trebuie.

#include <iostream>
#include <string>
#include <cstring>

using namespace std;
// a)
class Sibling
{

public:
    char *nume, *prenume;
    int *varsta;

    Sibling(const char *nume,const char *prenume, int varsta)
    {
        this->nume = new char[strlen(nume)+1];
        strcpy(this->nume,nume);
        this->prenume = new char[strlen(prenume)+1];
        strcpy(this->prenume,prenume);
        this->varsta = new int;
        *(this->varsta) = varsta;

        cout<<"Creat Sibling"<<endl;
    }

    Sibling(const Sibling &siblingObj)
    {
        this->nume = new char[strlen(siblingObj.nume) + 1];
        strcpy(this->nume, siblingObj.nume);

        this->prenume = new char[strlen(siblingObj.prenume) + 1];
        strcpy(this->prenume, siblingObj.prenume);

        this->varsta = new int;
        *this->varsta = *(siblingObj.varsta);
        
        cout<<"Copiat Sibling"<<endl;
    }

    ~Sibling()
    {
        delete[] this->nume;
        delete[] this->prenume;
        delete this->varsta;
    }
};

 // Punctul b
class Student {
private:
    string name;
    float* grades;
    int numGrades;

public:
    // Constructor
    Student(const string& name, int numGrades) {
        this->name = name;
        this->numGrades = numGrades;
        this->grades = new float[numGrades]; // dynamically allocate
    }

    // Copy constructor (important to avoid shallow copy!)
    Student(const Student& studentObj) {
        name = studentObj.name;
        numGrades = studentObj.numGrades;
        grades = new float[numGrades];
        for (int i = 0; i < numGrades; i++) {
            grades[i] = studentObj.grades[i];
        }
    }

    // Destructor
    ~Student() {
        delete[] grades;
    }

    // Function to set a grade
    void setGrade(int index, float value) {
        if (index >= 0 && index < numGrades)
            grades[index] = value;
    }

    // Function to display grades
    void showGrades() const {
        cout << "Grades for " << name << ": ";
        for (int i = 0; i < numGrades; i++)
            cout << grades[i] << " ";
        cout << endl;
    }
};


int main()
{
    // Punctul a)

    cout<<"Punctul a)"<<endl;
    Sibling sibling1("Ion","Popescu",25);
    Sibling sibling2 = sibling1;

    cout<<"Atribute inainte de update"<<endl;
    cout << "Sibling1: "<< sibling1.nume <<", "<< sibling1.prenume <<", "<< *sibling1.varsta << endl;
    cout << "Sibling2: "<< sibling2.nume <<", "<< sibling2.prenume <<", "<< *sibling2.varsta <<endl;

    strcpy(sibling2.nume,"ALT NUME");
    strcpy(sibling2.prenume,"ALT PRENUME");
    *sibling2.varsta = 50; 
    cout<<endl<<"Atribute dupa update"<<endl;
    cout << "Sibling1: "<< sibling1.nume <<", " << sibling1.prenume <<", "<< *sibling1.varsta << endl;
    cout << "Sibling2: "<< sibling2.nume <<", "<< sibling2.prenume <<", "<< *sibling2.varsta;

    cout<<endl<<"Punctul b)"<<endl;
    // Punctul b)
    Student student1("Gigel", 3);
    student1.setGrade(0, 8.5);
    student1.setGrade(1, 9.0);
    student1.setGrade(2, 7.5);

    // Copy student1 into student2
    Student student2 = student1;

    // Modify one of student2's grades
    student2.setGrade(1, 999.0);

    // Display grades for both
    student1.showGrades();
    student2.showGrades();

}