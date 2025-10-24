import kotlin.random.Random

class Student(private var lastName: String = "N/A",
    private var firstName: String = "N/A",
    private var faculty: String= "Automatica si Calculatoare",
    private var facultyFoundedYear: Int = 1818){
        companion object{
            private var numberOfStudents: Int = 0

            fun getNumberOfStudents(): Int{
                reutnr numberOfStudents
            }
        }
        private val id: Int = 0
        private var birthYear: Int = 0
        private var CNP: String = ""

        init {
            numberOfStudents++
            id = numberOfStudents


        }
        // --- Getters and Setters for Primary Constructor Properties ---

    // LastName (Setter uses 'value' keyword for the new value)
    fun getLastName(): String { return this.lastName }
    fun setLastName(value: String) { this.lastName = value }

    // FirstName
    fun getFirstName(): String { return this.firstName }
    fun setFirstName(value: String) { this.firstName = value }

    // Faculty
    fun getFaculty(): String { return this.faculty }
    fun setFaculty(value: String) { this.faculty = value }

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

}   


fun main(){
    
    var student : Student = Student()
    println(student.getBirthYear())
}   