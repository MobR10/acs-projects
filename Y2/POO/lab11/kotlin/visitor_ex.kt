import kotlin.math.*

interface Visitor{
    fun visit(circle: Circle): Double
    fun visit(triangle: Triangle): Double
}

interface Shape{
    fun accept(v: Visitor): Double
}

class Circle(
    var radius: Double
): Shape{
    override fun accept(v: Visitor): Double{
        return v.visit(this)
    }
}

class Triangle(
    var side1: Double,
    var side2: Double,
    var base: Double,
): Shape{
    override fun accept(v: Visitor): Double{
        return v.visit(this)
    }

    var height: Double = 0.0

    init{
        val a = side1
        val b = side2
        val c = base
        val s: Double = (a+ b+ c)/2
        val heronFormula: Double = sqrt(s*(s-a)*(s-b)*(s-c))
        height = 2* heronFormula / a
    }
}

class AreaCalculator: Visitor{

    override fun visit(circle: Circle): Double{
        return PI * circle.radius * circle.radius
    }

    override fun visit(triangle: Triangle): Double{
        return  triangle.base * triangle.height / 2
    }
}

class PerimeterCalculator: Visitor{
    override fun visit(circle: Circle): Double{
        return 2 * PI * circle.radius
    }

    override fun visit(triangle: Triangle): Double{
        return triangle.side1 + triangle.base + triangle.side2
    }    
}

fun main(){
    var shapes: MutableList<Shape> = mutableListOf(
        Circle(12.0),
        Triangle(3.0,4.0,5.0)
    )

   println("The area of the cirlce is: ${shapes[0].accept(AreaCalculator())}")

   println("The area of the triangle is: ${shapes[1].accept(AreaCalculator())}")


    println("The circumference of the circle is: ${shapes[0].accept(PerimeterCalculator())} ")

        println("The perimeter of the triangle is: ${shapes[1].accept(PerimeterCalculator())} ")

}