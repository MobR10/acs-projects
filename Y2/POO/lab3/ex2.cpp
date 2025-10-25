//  Să se realizeze o clasă Student. Această clasă trebuie să aibă următoarele atribute: nume, prenume, CNP,
//  anul nașterii toate de tipul private, dar și numele facultății și anul înființării acesteia (tot private).
// Creați o funcție care să genereze automat CNP-uri. Explicați algoritmul din spate.
// Creați metodele de get și set pentru Student. 0.5p
// Creați o metodă care să întoarcă sexul studentului în funcție de CNP. 0.5p
// Creați o metodă care să întoarcă vârsta studentului. 0.5p
// Creați o metodă care să întoarcă diferența de ani dintre anul înființării facultății și data nașterii studentului. 0.5. p
// Utilizați this Pointer. 0.5p  Testați codul creând mai mulți studenți.

/*
=====================================================
            CNP ALGORITHM EXPLANATION:
I have used random library to choose pseudo-random generated numbers for ALL the digits of the CNP
Steps:
1. Choose random birth year such that the person is at least 19 years old but not older than 110 years, using ctime library
to get the current year.
2. Determine the sex based on the birth year range, because for individuals born in 1900-1999, the sex is 1 for male and 2 for female,
but for individuals born between 2000 and 2099, the sex digit is 5 for male and 6 for female.
3. Generate a random month
4. Based on the month, determine the maximum number of days in that month
5. Generate a random day in that month
6. Choose a random county from the list
7. Generate the next 3 digits randomly
8. Determine the control digit
NOTE: in Romania, the 2 digits following the day of birth are dependent on the county and then the last digit is determined based on the first 12
====================================================
*/

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
            cerr << "MIN value is larger than max";
            return -1;
        }
        uniform_int_distribution<> distribution(min, max);
        return distribution(generator);
    }

    int nextIntFromArray(const int *data, size_t size)
    {
        if (size == 0)
        {
            cerr << "RUNTIME ERROR: Cannot select from an array with size 0." << endl;
            return 0;
        }

        // Generate a random index in the range [0, size - 1].
        uniform_int_distribution<size_t> distribution(0, size - 1);
        size_t randomIndex = distribution(generator);

        return data[randomIndex];
    }
};

int calculeazaCifraDeControl_char(const char *cnp_primele_12)
    {
        // 1. Constanta de control K (ca sir de caractere)
        const char *constanta_K = "279146358279";
        const int LUNGIME = 12;

        // Verifică dacă șirul primit are exact 12 caractere
        if (cnp_primele_12 == nullptr || strlen(cnp_primele_12) != LUNGIME)
        {
            return -1; // Semnalează o eroare
        }

        long long suma = 0;

        // 2. Parcurge și înmulțește fiecare cifră
        for (int i = 0; i < LUNGIME; ++i)
        {
            // Conversia caracterului cifră ('0' la '9') în valoarea sa întreagă (0 la 9)
            int cnp_cifra = cnp_primele_12[i] - '0';
            int k_cifra = constanta_K[i] - '0';

            // Verifică dacă input-ul CNP conține doar cifre
            if (cnp_cifra < 0 || cnp_cifra > 9)
            {
                return -1; // Caracter invalid în CNP
            }

            // 3. Adună rezultatul înmulțirii la suma totală
            suma += (long long)cnp_cifra * k_cifra;
        }

        // 4. Împarte la 11 și ia restul
        int rest = suma % 11;

        // 5. Determină cifra de control finală (C)
        if (rest < 10)
        {
            return rest;
        }
        else
        {
            // Cazul în care restul este 10, Cifra de control este 1
            return 1;
        }
    }
class Student
{
    static int numberOfStudents;
    int id;
    string lastName, firstName, facultyName;
    char CNP[14];
    int birthYear, facultyFoundedYear;
    Random generator;
    int counties[49] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,          // 01-10: Alba - Buzău
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, // 11-20: Caraș-Severin - Hunedoara
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30, // 21-30: Ialomița - Satu Mare
        31, 32, 33, 34, 35, 36, 37, 38, 39,     // 31-39: Sălaj - Vrancea

        40,                     // București (vechi)
        41, 42, 43, 44, 45, 46, // Sectoarele București (1-6)

        51, // Călărași
        52, // Giurgiu

        70 // Cod Unic (pentru CNP-urile noi)

    };

public:
    Student(string lastName = "N/A", string firstName = "N/A", string facultyName = "Automatica si Calculatoare", int facultyFoundedYear = 1818)
    {

        this->lastName = lastName;
        this->firstName = firstName;

        Student::numberOfStudents++;
        this->id = Student::numberOfStudents;

        this->facultyFoundedYear = facultyFoundedYear;
        this->facultyName = facultyName;

        int fullYear = generator.nextInt(Student::getCurrentYear() - 110, Student::getCurrentYear() - 19);

        this->birthYear = fullYear;

        // generate random sex
        CNP[0] = (fullYear < 2000) ? (generator.nextInt(1, 2) + '0') : (generator.nextInt(5, 6) + '0');
        int yy = fullYear % 100;

        CNP[1] = (yy / 10) + '0';
        CNP[2] = (yy % 10) + '0';

        int mm = generator.nextInt(1, 12);

        CNP[3] = (mm / 10) + '0';
        CNP[4] = (mm % 10) + '0';

        int maxDays;

        if (mm % 2 == 0)
        {
            if (mm == 8) // august e exceptie de luna para cu 31 de zile
            {
                maxDays = 31;
            }
            else if (mm == 2)
            {
                if ((fullYear % 4 == 0) && (fullYear % 100 != 0 || fullYear % 400 == 0)) // daca e an bisect
                    maxDays = 29;
                else
                    maxDays = 28;
            }
            else
                maxDays = 30;
        }
        else
            maxDays = 31;

        int dd = generator.nextInt(1, maxDays);

        CNP[5] = (dd / 10) + '0';
        CNP[6] = (dd % 10) + '0';

        // choose random county
        int jj = generator.nextIntFromArray(this->counties, 49);
        CNP[7] = jj / 10 + '0';
        CNP[8] = jj % 10 + '0';

        // next 3 digits are random
        CNP[9] = generator.nextInt(0, 9) + '0';
        CNP[10] = generator.nextInt(0, 9) + '0';
        CNP[11] = generator.nextInt(0, 9) + '0';

        // control digit
        char first12[13]="";
        strncpy(first12,CNP,12);
        CNP[12] = calculeazaCifraDeControl_char(first12) + '0';

        CNP[13] = '\0';
    }

    string getGender() const
    {

        return this->CNP[0] % 2 == 0 ? "FEMININ" : "MASCULIN";
    }

    int getAge() const
    {

        return Student::getCurrentYear() - this->birthYear;
    }

    int getDifference() const
    {
        return abs(this->facultyFoundedYear - this->birthYear);
    }

    // getters
    string getLastName() const
    {
        return this->lastName;
    }

    string getFirstName() const
    {
        return this->firstName;
    }

    const char *getCNP() const
    {
        return this->CNP;
    }

    string getFacultyName() const
    {
        return this->facultyName;
    }

    int getBirthYear() const
    {
        return this->birthYear;
    }

    int getFacultyFoundedYear() const
    {
        return this->facultyFoundedYear;
    }

    // setters
    void setCNP(const char *newCNP)
    {
        strcpy(this->CNP, newCNP);
    }

    void setLastName(const string newLastName)
    {
        this->lastName = newLastName;
    }
    void setFirstName(const string newFirstName)
    {
        this->firstName = newFirstName;
    }

    void setFacultyName(string newFacultyName)
    {
        this->facultyName = newFacultyName;
    }
    void setBirthYear(int newBirthYear)
    {
        this->birthYear = newBirthYear;
    }
    void setFacultyFounderYear(int newFacultyFoundedYear)
    {
        this->facultyFoundedYear = newFacultyFoundedYear;
    }

    void displayAttributes()
    {
        cout << "Student" << this->id << ":\n";
        cout << "Nume: " << this->lastName << endl;
        cout << "Prenume: " << this->firstName << endl;
        cout << "CNP: " << this->CNP << endl;
        cout << "Sex: " << this->getGender() << endl;
        cout << "Varsta: " << this->getAge() << endl;
        cout << "Anul nasterii: " << this->getBirthYear() << endl;
        cout << "Numele facultatii: " << this->facultyName << endl;
        cout << "Anul fondarii facultatii: " << this->facultyFoundedYear << endl
             << endl;
    }

    static int getCurrentYear()
    { // generat de gemini
        // 1. Get the current time (number of seconds since the Epoch)
        time_t currentTime = time(nullptr);

        // 2. Convert the time_t value to a structure (struct tm) representing
        //    the local time.
        tm *localTime = localtime(&currentTime);

        // 3. Access the tm_year member and adjust it.
        //    tm_year is years since 1900.
        if (localTime)
        {
            return localTime->tm_year + 1900;
        }
        else
        {
            // Return 0 or handle error if localtime fails (rare, but good practice)
            return 0;
        }
    }

};

int Student::numberOfStudents = 0;

int main()
{
    Student stud1, stud2, stud3, stud4, stud5;
    stud1.displayAttributes();
    stud2.displayAttributes();
    stud3.displayAttributes();
    stud4.displayAttributes();
    stud5.displayAttributes();
}