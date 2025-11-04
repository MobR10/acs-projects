

class Volume{

    fun calculateVolume(length: Int){
        println("Volumul cubului e: ${length*length*length}")
    }

    fun calculateVolume(radius: Float){
        println("Volumul sferei este: ${4 * 3.14 * radius * radius * radius / 3}")
    }

    fun calculateVolume(baseLength: Double, pyramidHeight: Double){
        println("Volumul piramidei este: ${baseLength * baseLength * pyramidHeight / 2}")
    }

    fun calculateVolume(){
        println("Introdu macar un parametru");
    }

}


fun main(){
    val calculator : Volume = Volume()

    calculator.calculateVolume()
    calculator.calculateVolume(3)
    calculator.calculateVolume(5.2f)
    calculator.calculateVolume(5.2,2.4)

    

}