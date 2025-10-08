import kotlin.random.Random

import kotlin.math.PI


fun main() {

    // Capitol: Hello world
    // Enunt exercitiu: Complete the code to make the program print "Mary is 20 years old" to standard output
    val name = "Mary"
    val age = 20
    println("Exercitiu capitol \"Hello world\":\n$name is $age years old")

    // Capitol: Basic types
    // Enunt exercitiu: Explicitly declare the correct type for each variable:
    val a: Int = 1000 
    val b: String = "log message"
    val c: Double = 3.14
    val d: Long = 100_000_000_000_000
    val e: Boolean = false
    val f: Char = '\n'

    print("\nExercitiu capitol \"Basic types\":\n$a, $b, $c, $d, $e, $f")

    // Capitol: Collections
    println("\nCapitol \"Collections\"")

    // Enunt exericitiu 1: You have a list of “green” numbers and a list of “red” numbers. Complete the code to print how many numbers there are in total.
    println("\nExercitiu 1:")
    val greenNumbers = listOf(1, 4, 23)
    val redNumbers = listOf(17, 2)
    // Write your code here
    println("Total numbers: ${greenNumbers.count() + redNumbers.count()}")

    // Enunt exericitiu 2: You have a set of protocols supported by your server. A user requests to use a particular protocol. 
    //Complete the program to check whether the requested protocol is supported or not (isSupported must be a Boolean value).
    val SUPPORTED = setOf("HTTP", "HTTPS", "FTP")
    val requested : String = "smtp"
    val isSupported : Boolean = requested.uppercase() in SUPPORTED // Write your code here 
    println("Excercitiu 2:\nSupport for $requested: $isSupported")

    // Enunt exericitiu 3: Define a map that relates integer numbers from 1 to 3 to their corresponding spelling. Use this map to spell the given number.
    val number2word : Map<Int, String> = mapOf(1 to "One", 2 to "Two", 3 to "Three") // Write your code here
    val n = 2
    println("Exercitiu 3:\n$n is spelt as '${number2word[n]}'")

    // Capitol: Control flow
    println("\nCapitol \"Control flow\"")

    // Enunt exercitiu 1: Create a simple game where you win if throwing two dice results in the same number. Use if to print You win :) if the dice match or You lose :( otherwise.

    val firstResult = Random.nextInt(6)
    val secondResult = Random.nextInt(6)
    print("\nExercitiu 1:\nFirst result: $firstResult\nSecond result: $secondResult.\nResult: ")
    if(firstResult == secondResult) {
        println("You win :)")
    } else {
        println("You lose :(")
    }

    // Enunt exercitiu 2: Using a when expression, update the following program so that it prints the corresponding actions when you input the names of game console buttons.
    val button = "A"
    print("\nExercitiu 2: actiunea butonului este ")
    println(
        when (button) {
            "A" -> "Yes"
            "B" -> "No"
            "X" -> "Menu"
            "Y" -> "Nothing"
            else -> "There is no such button"
        } 
    )

    // Exercitii capitol "Loops practice"
    println("\nExercitii capitol \"Loops practice\"")
    // Enunt exercitiu 1: You have a program that counts pizza slices until there's a whole pizza with 8 slices. Refactor this program in two ways:
    //Use a while loop.
    //Use a do-while loop.
    
    println("\nExercitiu 1:")

    println("Cu while loop:")
    var pizzaSlices = 0
    while (pizzaSlices < 7)
        {
            pizzaSlices++
            println("There's only $pizzaSlices slice/s of pizza :(")
        }
    pizzaSlices++
    println("There are $pizzaSlices slices of pizza. Hooray! We have a whole pizza.")

    println("Cu do while:")
    pizzaSlices = 0
    do{ 
        pizzaSlices++
        println("There's only $pizzaSlices slice/s of pizza :(")
    }while(pizzaSlices < 7)
    pizzaSlices++
    println("There are $pizzaSlices slices of pizza. Hooray! We have a whole pizza.")

    // Enunt exercitiu 2: Write a program that simulates the Fizz buzz game. Your task is to print numbers from 1 to 100 incrementally, 
    // replacing any number divisible by three with the word "fizz", and any number divisible by five with the word "buzz". 
    // Any number divisible by both 3 and 5 must be replaced with the word "fizzbuzz".

    println("\nExercitiu 2:")
    for(i in 1..100){
            if(i%3==0 && i%5==0)
                print("fizzbuzz")
            else if(i%3==0)
                print("fizz")
            else if(i%5==0)
                print("buzz")
            else 
                print(i)
            if( i < 100) print(", ")
            else println()
        }

    // Enunt exercitiu 3: You have a list of words. Use for and if to print only the words that start with the letter l.
    println("\nExercitiu 3:")

    val words = listOf("dinosaur", "limousine", "magazine", "language")

    for(i in 0..<words.count()){
        if(words[i][0] == 'l'){
            print(words[i])
            if(i<words.count()-1)
                print(", ")
            else print("\n")
        }
    }

    // Exercitii capitol "Functions"
    println("\nCapitol \"Functions\"")

    // Exercitii  "Functions practice"
    println("\nExercitii \"Functions practice:\"")

    // Enunt exercitiu 1: Write a function called circleArea that takes the radius of a circle in integer format as a parameter and outputs the area of that circle.
    println("\nExercitiu 1:")
    fun circleArea(radius: Int) = PI*radius*radius
    println(circleArea(2))

    // Enunt exercitiu 2: Rewrite the circleArea function from the previous exercise as a single-expression function.
    println("Exercitiul 2 e deja rezolvat la exercitiul 1 hehe")

    // Enunt exercitiu 3: You have a function that translates a time interval given in hours, minutes, and seconds into seconds.
    // In most cases, you need to pass only one or two function parameters while the rest are equal to 0.
    // Improve the function and the code that calls it by using default parameter values and named arguments so that the code is easier to read.

    println("\nExercitiul 3:")
    fun intervalInSeconds(hours: Int = 0, minutes: Int = 0, seconds: Int= 0) =
    ((hours * 60) + minutes) * 60 + seconds

    println(intervalInSeconds(hours=1, minutes = 20, seconds =  15))
    println(intervalInSeconds(minutes = 1, seconds = 25))
    println(intervalInSeconds(hours = 2))
    println(intervalInSeconds(minutes = 10))
    println(intervalInSeconds(hours = 1, seconds = 1))

    // Exercitii "Lambda expressions practice"

    println("\nExercitii \"Lambda expressions practice\"")

    // Enunt exercitiul 1: You have a list of actions supported by a web service, a common prefix for all requests, and an ID of a particular resource. 
    // To request an action title over the resource with ID: 5, you need to create the following URL: https://example.com/book-info/5/title.
    // Use a lambda expression to create a list of URLs from the list of actions.
    println("\nExercitiul 1:")
    val actions = listOf("title", "year", "author")
    val prefix = "https://example.com/book-info"
    val id = 5
    val urls = actions.map { action -> "$prefix/$id/$action" }
    println(urls)
    
    // Enunt exercitiul 2: Write a function that takes an Int value and an action (a function with type () -> Unit) which then repeats the action the given number of times.
    // Then use this function to print “Hello” 5 times.
    println("\nExercitiul 2:")

    fun repeatN(n: Int, action: () -> Unit) {
        for(i in 1..n){
            action()
        }
    }    

    repeatN(5){println("Hello")}

}
