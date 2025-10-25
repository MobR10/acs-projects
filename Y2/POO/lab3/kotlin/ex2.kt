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
6. Randomly generate the rest of the 6 digits of the CNP
NOTE: in Romania, the 2 digits following the day of birth are dependent on the county and then the last digit is determined by
a sequence of digits and the birth date. Basically, this algorithm doesn't copy the real deal,
therefore it is possible, though very unlikely, to generate 2 identical CNPs. 
====================================================
*/

import kotlin.random.Random
import java.time.Year
import kotlin.math.abs

class Student(private var lastName: String = "N/A",
    private var firstName: String = "N/A",
    private var facultyName: String= "Automatica si Calculatoare",
    private var facultyFoundedYear: Int = 1818){

        companion object{
            private var numberOfStudents: Int = 0

            fun getNumberOfStudents(): Int{
                return numberOfStudents
            }
        }
        
        private val id: Int = ++numberOfStudents
        private var birthYear: Int = 0
        private var CNP: String = ""

        init {
            
            // initialize a char array to build CNP
            var charCNP = CharArray(13)

            // get the current year and generate a random birthYear
            val currentYear = Year.now().value
            val fullYear = Random.nextInt(currentYear-110,currentYear-19+1)

            this.birthYear = fullYear

            // generate random sex
            charCNP[0] = when{
                fullYear < 2000 -> Random.nextInt(1,2+1)
                else -> Random.nextInt(5,6+1) 
            }.digitToChar()
        
        val yy = fullYear % 100
        charCNP[1]=(yy/10).digitToChar()
        charCNP[2]=(yy%10).digitToChar()

        // generate random month
        val mm = Random.nextInt(1,12+1)

        charCNP[3] = (mm / 10).digitToChar() 
        charCNP[4] = (mm % 10).digitToChar()

        var maxDays: Int
        
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

        val dd = Random.nextInt(1, maxDays+1)

        charCNP[5] = (dd / 10).digitToChar() 
        charCNP[6] = (dd % 10).digitToChar()

        // generare random a ultimelor 6 cife
        // nu e algoritmul real si nici nu ia in considerare situatiile putin probabile in care restul cnp-ului este identic,
        // adica cand sexul si data nasterii coincid
        charCNP[7] = Random.nextInt(0,9+1).digitToChar()
        charCNP[8] = Random.nextInt(0,9+1).digitToChar()
        charCNP[9] = Random.nextInt(0,9+1).digitToChar()
        charCNP[10] = Random.nextInt(0,9+1).digitToChar()   
        charCNP[11] = Random.nextInt(0,9+1).digitToChar() 
        charCNP[12] = Random.nextInt(0,9+1).digitToChar()

            this.CNP = charCNP.joinToString(separator="")
        }
        // --- Getters and Setters for Primary Constructor Properties ---

    // LastName (Setter uses 'value' keyword for the new value)
    fun getLastName(): String { return this.lastName }
    fun setLastName(value: String) { this.lastName = value }

    // FirstName
    fun getFirstName(): String { return this.firstName }
    fun setFirstName(value: String) { this.firstName = value }

    // Faculty
    fun getFacultyName(): String { return this.facultyName }
    fun setFacultyName(value: String) { this.facultyName = value }

    // Faculty Founded Year
    fun getFacultyFoundedYear(): Int { return this.facultyFoundedYear }
    fun setFacultyFoundedYear(value: Int) { 
            this.facultyFoundedYear = value
    }

    // --- Getters and Setters for Class Body Properties ---

    // birthYear (You already had the getter, added the setter)
    fun getBirthYear(): Int { return this.birthYear }
    fun setBirthYear(value: Int) { this.birthYear = value }

    // CNP
    fun getCNP(): String { return this.CNP }
    fun setCNP(value: String) { this.CNP = value }

    // Id
    fun getId(): Int {return this.id} 

    fun getGender(): String = when{
        this.CNP[0].digitToInt() % 2 == 0 -> "FEMININ"
        else -> "MASCULIN"
    }

    fun getAge() : Int = Year.now().value - this.birthYear

    fun getDifference() : Int = abs(this.facultyFoundedYear - this.birthYear)

    fun displayAttributes() {

        println("Student$id:\n")
        println("Nume: $lastName")
        println("Prenume: $firstName")
        println("CNP: $CNP")
        println("Sex: ${getGender()}")
        println("Varsta: ${getAge()}")
        println("Anul nasterii: ${getBirthYear()}")
        println("Numele facultatii: $facultyName")
        println("Anul fondarii facultatii: $facultyFoundedYear") 
        println("Diferenta dintre anul fondarii facultatii si anul nasterii: ${getDifference()}\n")
    }
}   


fun main(){
    
    var stud1 = Student()
    var stud2 = Student()
    var stud3 = Student()
    var stud4 = Student()
    var stud5 = Student()

    stud1.displayAttributes()
    stud2.displayAttributes()
    stud3.displayAttributes()
    stud4.displayAttributes()
    stud5.displayAttributes()
}   