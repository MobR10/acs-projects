/*
    Realizați o clasă Beer, care să conțină atributele type și origin (ambele string și să fie protected).
Clasa trebuie să aibă:
- Un constructor default
- Un constructor care va inițializa toți parametrii
- Metode de get pentru cei doi parametrii
    Din clasa Beer derivați alte 3 clase printr-o moștenire private. Fiecare va avea un tip diferit de etichetă pe sticlă
Tipul A: etichetă pătrată (private length)
Tipul B: etichetă rotundă și transparentă (private radius)
Tipul C: în formă de triunghi dreptunghic (private base și height)
Fiecare clasă va avea constructori default și constructori cu parametrii care să seteze fiecare atribut.
Fiecare clasă trebuie să aibă o metodă de a întoarce aria etichetei, a tipului și a originii.
*/

import kotlin.math.PI

open class Beer(open protected var type: String = "default" ,
open protected var origin: String= "default"){


    val beerType: String
        get() = this.type

    val beerOrigin: String
        get() = this.origin
    
    open fun displayAttributes(){
        print("Type: ${type}\nOrigin: ${origin}\n")
    }

}

class TypeA(override var type: String = "default",
override var origin: String = "default",
private var length: Double = 0.0): Beer(type, origin){

    fun getArea(): Double{
        return length*length
    }

    override fun displayAttributes(){
        super.displayAttributes()
        println("Length: ${length}\nArea: ${getArea()}\n")
    }
}

class TypeB(override var type: String = "default",
override var origin: String = "default",
private var radius: Double = 0.0): Beer(type, origin){

    fun getArea(): Double{
        return radius*radius*PI
    }
    override fun displayAttributes(){
        super.displayAttributes()
        println("Radius: ${radius}\nArea: ${getArea()}\n")
    }
}



class TypeC(override var type: String = "default",
override var origin: String = "default",
private var base: Double = 0.0,
private var height: Double = 0.0): Beer(type, origin){

    fun getArea(): Double{
        return base * height / 2
    }

    override fun displayAttributes(){
        super.displayAttributes()
        println("Base: ${base}\nHeight: ${height}\nArea: ${getArea()}\n")
    }
}

fun main(){
    var bere: Beer = Beer(type="Mazare",origin="Romania")
    bere.displayAttributes()
    println()
    
    var bereA: TypeA = TypeA(type="Ciucalata",origin="Portugalia",length=13.2)
    bereA.displayAttributes()

    var bereB: TypeB = TypeB(type="Rozmarin",origin="Republica Moldova",radius=12.4)
    bereB.displayAttributes()

    var bereC: TypeC = TypeC(type="Lemn",origin="Japonia",base=3.4,height=9.3)
    bereC.displayAttributes()
}