

interface ILogger{
    fun logMessage(msg: String)
}

abstract class Dispozitiv(){
    var numeDispozitiv: String ="N/A"
    abstract fun esteConectat(): Boolean
}

class Imprimanta(): ILogger, Dispozitiv(){
    override fun esteConectat(): Boolean{
        return true
    }

    override fun logMessage(msg: String){
        println("Mesaj: $msg")
    }
}
fun main(){

    var imprimanta: Imprimanta = Imprimanta()

    imprimanta.logMessage("Salut")
    println(imprimanta.esteConectat())

}