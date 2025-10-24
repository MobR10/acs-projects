//  Să se realizeze o clasă Student. Această clasă trebuie să aibă următoarele atribute: nume, prenume, CNP,
//  anul nașterii toate de tipul private, dar și numele facultății și anul înființării acesteia (tot private).
// Creați o funcție care să genereze automat CNP-uri. Explicați algoritmul din spate.
// Creați metodele de get și set pentru Student. 0.5p
// Creați o metodă care să întoarcă sexul studentului în funcție de CNP. 0.5p
// Creați o metodă care să întoarcă vârsta studentului. 0.5p
// Creați o metodă care să întoarcă diferența de ani dintre anul înființării facultății și data nașterii studentului. 0.5. p
// Utilizați this Pointer. 0.5p  Testați codul creând mai mulți studenți.

#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

class Random
{
private:
    // The random number engine
    mt19937 generator;

public:
    Random()
    {
        random_device randomDevice;
        generator.seed(randomDevice());
    }

    /**
     * @brief Generates a random integer between 0 (inclusive) and bound (exclusive).
     * @param bound The exclusive upper limit. Must be positive.
     * @return A random integer in the range [0, bound - 1].
     */

    int nextInt(int min, int max)
    {
        if (min > max)
            {
                cerr<<"MIN value is larger than max";
                return -1;
            }
        uniform_int_distribution<> distribution(min, max);
        return distribution(generator);
    }

    int nextIntFromArray(const int* data, size_t size) {
        if (size == 0) {
            cerr << "RUNTIME ERROR: Cannot select from an array with size 0." << endl;
            return 0;
        }
        
        // Generate a random index in the range [0, size - 1].
        std::uniform_int_distribution<size_t> distribution(0, size - 1);
        size_t randomIndex = distribution(generator);
        
        return data[randomIndex];
    }
};
class Student
{
    static int numberOfStudents;
    int id;
    string lastName, firstName, facultyName;
    char CNP[14];
    int birthYear, facultyFoundedYear;
    Random generator;

public:
    Student(string lastName="N/A", string firstName="N/A", string facultyName="Automatica si Calculatoare",int facultyFoundedYear = 1818){
         
        this->lastName = lastName;
        this->firstName = firstName;

        Student::numberOfStudents ++;
        this->id = Student::numberOfStudents;

        this->facultyFoundedYear = facultyFoundedYear;
        this->facultyName = facultyName;

        int fullYear = generator.nextInt(Student::getCurrentYear()-110, Student::getCurrentYear()-19); 

        this->birthYear = fullYear;

        CNP[0] = (fullYear < 2000) ? (generator.nextInt(1, 2) + '0') : (generator.nextInt(5,6) + '0');
        int yy = fullYear % 100;

        CNP[1] = (yy / 10) + '0'; 
        CNP[2] = (yy % 10) + '0'; 

        int mm = generator.nextInt(1, 12);

        CNP[3] = (mm / 10) + '0'; 
        CNP[4] = (mm % 10) + '0'; 

        int maxDays;
        
        if( mm % 2 == 0)
        {
            if(mm == 8) // august e exceptie de luna para cu 31 de zile
                {
                    maxDays=31;
                }
            else if (mm == 2){
                if((fullYear % 4 == 0) && (fullYear % 100 != 0 || fullYear % 400 == 0)) // daca e an bisect
                    maxDays = 29;
                else maxDays = 28;
            }
            else maxDays = 30;
        }
        else maxDays = 31;

        int dd = generator.nextInt(1, maxDays);

        CNP[5] = (dd / 10) + '0'; 
        CNP[6] = (dd % 10) + '0'; 

        // generare random a ultimelor 6 cife
        // nu e algoritmul real si nici nu ia in considerare situatiile putin probabile in care restul cnp-ului este identic,
        // adica cand sexul si data nasterii coincid
        CNP[7] = generator.nextInt(0,9) + '0';
        CNP[8] = generator.nextInt(0,9) + '0';
        CNP[9] = generator.nextInt(0,9) + '0';
        CNP[10] = generator.nextInt(0,9) + '0';  
        CNP[11] = generator.nextInt(0,9) + '0';
        CNP[12] = generator.nextInt(0,9) + '0';

        CNP[13] = '\0';
    }

    string getGender()
    {

        return this->CNP[0]%2 == 0 ? "FEMININ" : "MASCULIN";
    }

    int getAge()
    {
        
        return Student::getCurrentYear() - this->birthYear;
    }

    int getDifference()
    {
        return this->facultyFoundedYear - this->getAge();
    }

    // getters
    string getLastName()
    {
        return this->lastName;
    }

    string getFirstName()
    {
        return this->firstName;
    }

    char* getCNP()
    {
        return this->CNP;
    }

    string getFacultyName()
    {
        return this->facultyName;
    }

    int getBirthYear()
    {
        return this->birthYear;
    }

    int getFacultyFoundedYear()
    {
        return this->facultyFoundedYear;
    }
    
    // setters
    void setCNP(const char* newCNP){
        strcpy(this->CNP,newCNP);
    }

    void setLastName(const string newLastName){
        this->lastName = newLastName;
    }
    void setFirstName(const string newFirstName){
        this->firstName = newFirstName;
    }

    void setFacultyName(string newFacultyName){
        this->facultyName = newFacultyName;
    }
    void setBirthYear(int newBirthYear){
        this->birthYear = newBirthYear;
    }
    void setFacultyFounderYear(int newFacultyFoundedYear){
        this->facultyFoundedYear = newFacultyFoundedYear;
    }

    void displayAttributes(){
        cout<<"Student"<<this->id<<":\n";
        cout<<"Nume: "<<this->lastName<<endl;
        cout<<"Prenume: "<<this->firstName<<endl;
        cout<<"CNP: "<<this->CNP<<endl;
        cout<<"Sex: "<<this->getGender()<<endl;
        cout<<"Varsta: "<< this->getAge()<<endl;
        cout<<"Anul nasterii: "<<this->getBirthYear()<<endl;
        cout<<"Numele facultatii: "<<this->facultyName<<endl;
        cout<<"Anul fondarii facultatii: "<<this->facultyFoundedYear<<endl<<endl; 
    }
    
    static int getCurrentYear() { // generat de gemini 
    // 1. Get the current time (number of seconds since the Epoch)
    time_t currentTime = time(nullptr);

    // 2. Convert the time_t value to a structure (struct tm) representing
    //    the local time.
    tm* localTime = localtime(&currentTime);

    // 3. Access the tm_year member and adjust it.
    //    tm_year is years since 1900.
    if (localTime) {
        return localTime->tm_year + 1900;
    } else {
        // Return 0 or handle error if localtime fails (rare, but good practice)
        return 0; 
    }
}
    
};  

int Student::numberOfStudents = 0;

int main()
{
    Student stud1,stud2,stud3,stud4,stud5;
    stud1.displayAttributes();
    stud2.displayAttributes();
    stud3.displayAttributes();
    stud4.displayAttributes();
    stud5.displayAttributes();
    

}