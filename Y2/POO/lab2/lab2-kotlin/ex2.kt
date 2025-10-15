class Motorbike(
    var producer: String = "N/A",
    var model: String = "N/A",
    var engine: String = "N/A",
    var year: Int = -1,
    var price: Float = -1f
) {
    constructor(producer: String, model: String, engine: String) :
        this(producer, model, engine, -1, -1f) {}

    constructor(producer: String, model: String, engine: String, year: Int) :
        this(producer, model, engine, year, -1f) {}

    fun display(){
        println("Producer: $producer, model: $model, engine: $engine, year: $year, price: $price\n")
    }
}

fun main(){
    var motor1 = Motorbike() // constructor 1 (constructor primar)
    var motor2= Motorbike("Honda", "CB500F", "471 cc, parallel-twin, liquid-cooled, 47 hp") // constructor 2
    var motor3= Motorbike("BMW Motorrad", "R 1250 GS", "1,254 cc, flat-twin (boxer), liquid/air-cooled, 136 hp", 2023) // constructor 3
    var motor4= Motorbike("Yamaha", "YZF-R1", "998 cc, inline 4-cylinder, liquid-cooled, 200 hp", 2023, 1203.99f) // constructor 4 
    //  (oarecum constructor 4 e tot primar, ca daca defineam un constructor secundar cu toti parametrii, 
    //  primeam eroare de overload, dar e cod echivalent cu cel din cpp, unde am 4 constructori, deci sa zicem ca si aici sunt 4 constructori :) )
    // altfel mai adaugam un atribut si faceam inca un constructor... but you got the point

    println("Motor 1:")
    motor1.display()
    println("Motor 2:")
    motor2.display()
    println("Motor 3:")
    motor3.display()
    println("Motor 4:")
    motor4.display()
}
