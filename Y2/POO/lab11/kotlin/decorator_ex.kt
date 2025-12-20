abstract class Shaorma {
    abstract fun getDescription(): String
    abstract fun getCost(): Double
}

class EmptyShaorma : Shaorma() {
    override fun getDescription(): String {
        return "Empty Shaorma"
    }

    override fun getCost(): Double {
        return 0.0
    }
}

open class ShaormaDecorator(protected val decoratedShaorma: Shaorma) : Shaorma() {
    override fun getDescription(): String {
        return decoratedShaorma.getDescription()
    }

    override fun getCost(): Double {
        return decoratedShaorma.getCost()
    }
}

class PuiDecorator(decoratedShaorma: Shaorma) : ShaormaDecorator(decoratedShaorma) {
    override fun getDescription(): String {
        return decoratedShaorma.getDescription() + ", Pui"
    }

    override fun getCost(): Double {
        return decoratedShaorma.getCost() + 5
    }
}

class VitaDecorator(decoratedShaorma: Shaorma) : ShaormaDecorator(decoratedShaorma) {
    override fun getDescription(): String {
        return decoratedShaorma.getDescription() + ", Vita"
    }

    override fun getCost(): Double {
        return decoratedShaorma.getCost() + 9
    }
}

class VarzaDecorator(decoratedShaorma: Shaorma) : ShaormaDecorator(decoratedShaorma) {
    override fun getDescription(): String {
        return decoratedShaorma.getDescription() + ", Varza"
    }

    override fun getCost(): Double {
        return decoratedShaorma.getCost() + 3
    }
}

class KetchupDecorator(decoratedShaorma: Shaorma) : ShaormaDecorator(decoratedShaorma) {
    override fun getDescription(): String {
        return decoratedShaorma.getDescription() + ", Ketchup"
    }

    override fun getCost(): Double {
        return decoratedShaorma.getCost() + 9
    }
}

class CastravetiDecorator(decoratedShaorma: Shaorma) : ShaormaDecorator(decoratedShaorma) {
    override fun getDescription(): String {
        return decoratedShaorma.getDescription() + ", Castraveti"
    }

    override fun getCost(): Double {
        return decoratedShaorma.getCost() + 9
    }
}

fun main() {
    val empty = EmptyShaorma()
    println("Description: ${empty.getDescription()}")
    println("Cost: $${empty.getCost()}")

    val shaormaCuVita = VitaDecorator(VarzaDecorator(EmptyShaorma()))
    println("\nDescription: ${shaormaCuVita.getDescription()}")
    println("Cost: $${shaormaCuVita.getCost()}")

    val shaormaCuDeToate = VitaDecorator(
        VarzaDecorator(
            PuiDecorator(
                CastravetiDecorator(
                    KetchupDecorator(EmptyShaorma())
                )
            )
        )
    )
    println("\nDescription: ${shaormaCuDeToate.getDescription()}")
    println("Cost: $${shaormaCuDeToate.getCost()}")
}
