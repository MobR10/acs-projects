import java.time.LocalDateTime
import java.time.format.DateTimeFormatter

class Clock {

    init {

        val date = LocalDateTime.now()

        println("Astazi este "+
        when(date.dayOfWeek.toString()){
            "MONDAY" -> "Luni"
            "TUESDAY" -> "Marti"
            "WEDNESDAY" -> "Miercuri"
            "Thursday" -> "Joi"
            "Friday" -> "Vineri"
            "Saturday" -> "Sambata"
            else -> "Duminica"
        }+", ora ${date.hour}. Mai sunt ${24-date.hour} ore ramase astazi."
        )
    }
}

fun main() {
    val clock = Clock()
}
