open class Persoana(open var name: String){

        open fun printOccupation(){
            println("Persoana: Sunt somer :( ")
        }

        open fun haiInOras(){
            println("Persoana: Da, frate, dar tu platesti.")
        }
};

open class Angajat(override var name: String,open var salariu: Double): Persoana(name){

        override fun printOccupation() {
            println("Angajat: sunt un simplu angajat la o companie")
        }

        override fun haiInOras() {
            println("Angajat: Sigur, dar stai sa vad daca am destui bani!")
        }

        open fun printSalary(){
            println("Angajat: salariu este: ${this.salariu}")

        }
};

class Manager(override var name: String, override var salariu: Double): Angajat(name,salariu){

        override fun printOccupation() {
            println("Manager: sunt manager la o companie")
        }

        override fun haiInOras() {
            println("Manager, scuze, nu pot. Lucrez si in weekend...")
        }
};

class Programator(override var name: String,override var salariu: Double): Angajat(name,salariu){
        override fun printOccupation() {
                println("Programator: sunt programator la o companie")
            }

        override fun haiInOras() {
            println("Programator: sigur, fac cinste!")
        }

};

fun main(){

    val persoana: Persoana = Persoana("Bula")
    persoana.haiInOras();
    persoana.printOccupation();

    val angajatSimplu: Angajat = Angajat("gigel",2000.0)
    angajatSimplu.haiInOras();
    angajatSimplu.printOccupation();

    val manager: Manager = Manager("Chis", 5000.0)
    manager.haiInOras();
    manager.printOccupation();

    val programator: Programator =  Programator("Cosmin",3000.0)
    programator.haiInOras();
    programator.printOccupation();
}