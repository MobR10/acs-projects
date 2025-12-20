abstract class Component {
    open fun add(c: Component) {}
    abstract fun execute()
}

class UI : Component() {
    private val components = mutableListOf<Component>()

    override fun add(c: Component) {
        components.add(c)
    }

    override fun execute() {
        for (c in components) {
            c.execute()
        }
    }
}

class Button : Component() {
    override fun execute() {
        println("Button pressed.")
    }
}

class Label(private val text: String) : Component() {
    override fun execute() {
        println("Label text is: $text")
    }
}

class Window : Component() {
    private val components = mutableListOf<Component>()

    override fun add(c: Component) {
        components.add(c)
    }

    override fun execute() {
        for (c in components) {
            c.execute()
        }
    }
}

fun main() {
    val ui = UI()
    val window = Window()

    ui.add(window)

    window.add(Button())
    window.add(Label("Ce mai faci"))

    ui.execute()
}
