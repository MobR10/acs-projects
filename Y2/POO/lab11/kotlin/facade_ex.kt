class Monster {
    fun spawn() {
        println("Monster spawns in swamp.")
    }
}

class Environment {
    fun generateMap() {
        println("Map is generating.")
    }
}

class Player {
    private val attackDmg = 10

    fun spawn() {
        println("Player spawns in the base.")
    }
}

class Game {
    private val monsters = Array(10) { Monster() }
    private val environment = Environment()
    private val player = Player()

    fun startGame() {
        environment.generateMap()
        for (monster in monsters) {
            monster.spawn()
        }
        player.spawn()
    }
}

fun main() {
    val game = Game()
    game.startGame()
}
