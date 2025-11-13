
class Library(
    var libraryName: String,
    var location: String,
){
    var numberOfBooks: Int = 0
    var books: MutableList<Book> = mutableListOf()

    val name: String
    get() = libraryName
}

class Librarian(
    var librarianName: String,
    var age: Int,
    var salary: Double,
    var library: Library
){
    fun getBookByName(name: String): Book{
        for (i in library.books){
            if(i.bookName == name)
                return i
        }
        println("Nu a fost gasita cartea")
        return Book("N/A","N/A","N/A",0.0)
    }

    fun addBook( bookName: String, author: String, genre: String, price: Double){
        library.books.add(Book(bookName,author,genre,price))
        library.numberOfBooks++
    }

    fun printBooks(){
        for (i in 0 until library.numberOfBooks){
            if( i == library.numberOfBooks - 1)
                print("\"${library.books[i].bookName}\"")
            else 
                print("\"${library.books[i].bookName}\", ")
        }
    }
}

class Book(
    var bookName: String,
    var author: String,
    var genre: String,
    var price: Double
){
    
}

fun main(){
    var library: Library = Library("Biblioteca UNSTPB","Campus")
    var librarian: Librarian = Librarian("Maricica",55,2500.0,library)

    librarian.addBook("O scrisoare pierduta","I. L. Caragiale","Comedie",15.0)
    librarian.addBook("Ultima noapte de dragoste, intaia noapte de razboi","Camil Petrescu","Roman",50.0)
    librarian.addBook("Cartea nuntii", "G. Calinescu","Roman",50.0)

    println("Numele bibliotecii este ${library.name}")

    print("Cartile disponibile sunt: ")
    librarian.printBooks()
    println()
    println("Carte cautata: ${librarian.getBookByName("O scrisoare pierduta").bookName}")
}