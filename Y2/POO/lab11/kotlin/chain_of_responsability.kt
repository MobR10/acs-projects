open class Handler {
    protected var next: Handler? = null

    open fun setNext(handler: Handler): Handler {
        this.next = handler
        return handler
    }

    open fun handle(request: String) {
        next?.handle(request)
    }
}

class CEO : Handler() {
    override fun handle(request: String) {
        if (request == "CEO")
            println("CEO can solve this issue")
        else {
            super.handle(request)
        }
    }
}

class Manager : Handler() {
    override fun handle(request: String) {
        if (request == "manager")
            println("Manager can solve this issue")
        else {
            super.handle(request)
        }
    }
}

class Programmer : Handler() {
    override fun handle(request: String) {
        if (request == "programmer")
            println("Programmer can solve this issue")
        else {
            super.handle(request)
        }
    }
}

fun main() {
    val h1 = CEO()
    val h3 = Programmer()
    val h2 = Manager()

    h1.setNext(h2)
    h2.setNext(h3)

    h1.handle("programmer")
}
