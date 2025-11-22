import java.io.File
import kotlin.random.Random

const val UPB = 1
const val MEDICINA = 2
const val FILE_NAME = "studenti.csv"


class MyRandom {
    private val rng = Random(System.currentTimeMillis())

    fun get(): Int = rng.nextInt(UPB, MEDICINA + 1)
}

abstract class Student(
    val id: String,
    val age: Int,
    val studyHoursPerDay: Float,
    val socialMediaHours: Float,
    val partTimeJob: String
) {
    fun printInfo() {
        println(
            "
            Student id: $id
            Age: $age
            Study hours per day: $studyHoursPerDay
            Social media hours: $socialMediaHours
            Has part time job: $partTimeJob
        ".trimIndent()
        )
    }

    abstract fun printOccupation()
}

class StudentPolitehnica(
    id: String,
    age: Int,
    studyHoursPerDay: Float,
    socialMediaHours: Float,
    partTimeJob: String
) : Student(id, age, studyHoursPerDay, socialMediaHours, partTimeJob) {

    override fun printOccupation() {
        println("I am building a robot!")
    }
}

class StudentMedicina(
    id: String,
    age: Int,
    studyHoursPerDay: Float,
    socialMediaHours: Float,
    partTimeJob: String
) : Student(id, age, studyHoursPerDay, socialMediaHours, partTimeJob) {

    override fun printOccupation() {
        println("I am making a vaccine!")
    }
}

class Importer {

    private val generator = MyRandom()

    fun readCSV(
        fileName: String,
        studentiPoli: MutableList<StudentPolitehnica>,
        studentiMedicina: MutableList<StudentMedicina>
    ) {
        val file = File(fileName)
        if (!file.exists()) {
            println("Nu s-a putut deschide fisierul")
            return
        }

        val lines = file.readLines()
        // skip header
        for (i in 1 until lines.size) {
            val cols = lines[i].split(",")

            val id = cols[0]
            val age = cols[1].toInt()
            val studyHours = cols[3].toFloat()
            val socialHours = cols[4].toFloat()
            val partTimeJob = cols[6]

            val choice = generator.get()

            if (choice == UPB) {
                studentiPoli += StudentPolitehnica(
                    id, age, studyHours, socialHours, partTimeJob
                )
            } else {
                studentiMedicina += StudentMedicina(
                    id, age, studyHours, socialHours, partTimeJob
                )
            }
        }
    }
}

fun getMeanAgeMedicina(students: List<StudentMedicina>): Float =
    students.sumOf { it.age.toDouble() }.toFloat() / students.size

fun getMeanStudyPoli(students: List<StudentPolitehnica>): Float =
    students.sumOf { it.studyHoursPerDay.toDouble() }.toFloat() / students.size

fun getMeanSocialPoli(students: List<StudentPolitehnica>): Float =
    students.sumOf { it.socialMediaHours.toDouble() }.toFloat() / students.size

fun getNumberOfStudentsWithJob(
    poli: List<StudentPolitehnica>,
    medi: List<StudentMedicina>
): Int {
    val part1 = poli.count { it.partTimeJob == "Yes" }
    val part2 = medi.count { it.partTimeJob == "Yes" }
    return part1 + part2
}


fun main() {

    val importer = Importer()

    val studentiPOLI = mutableListOf<StudentPolitehnica>()
    val studentiMedicina = mutableListOf<StudentMedicina>()

    var input: String
    while (true) {
        print("Introdu numele fisierului csv (hint: $FILE_NAME): ")
        input = readln()

        try {
            if (input != FILE_NAME)
                throw Exception("Numele fisierului este introdus gresit! Mai incearca:")
            break
        } catch (e: Exception) {
            println(e.message)
        }
    }

    importer.readCSV(input, studentiPOLI, studentiMedicina)

    println("POLI STUDENTS: ${studentiPOLI.size}")
    println("Medi students: ${studentiMedicina.size}")

    if (studentiMedicina.isNotEmpty())
        println("MEAN AGE MEDICINA: ${getMeanAgeMedicina(studentiMedicina)}")

    if (studentiPOLI.isNotEmpty()) {
        println("Mean study hours per day POLI: ${getMeanStudyPoli(studentiPOLI)}")
        println("Mean social hours per day POLI: ${getMeanSocialPoli(studentiPOLI)}")
    }

    println("Number of students with part time job: ${
        getNumberOfStudentsWithJob(studentiPOLI, studentiMedicina)
    }")

    if (studentiPOLI.isNotEmpty()) {
        print("Occupation of poli student: ")
        studentiPOLI[0].printOccupation()
    }

    if (studentiMedicina.isNotEmpty()) {
        print("Occupation of medicine student: ")
        studentiMedicina[0].printOccupation()
    }
}