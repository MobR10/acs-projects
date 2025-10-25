/*  
    Se va  crea o clasă ContBancar care modelează un scenariu real.
    Construiti o clasă robustă care gestionează conturi bancare, separând datele specifice fiecărui
    cont de cele comune tuturor conturilor. 
    Cerințe:
    -> Clasa ContBancar: Va avea datele membre private: string titularCont & double sold
    -> Constructorul: Va primi titularul și soldul inițial pentru a crea un nou cont.
    -> Metode de Acces (Getters): getTitular(): Returnează numele titularului & getSold(): Returnează soldul curent. 
    Important: Ambele metode trebuie marcate ca const. De ce? Pentru că ele doar "citesc" starea contului, nu o modifică.
    Este o promisiune de siguranță.
    -> Metode pentru Tranzacții: depune(double suma): Adaugă suma specificată la sold & 
    retrage(double suma): Scade suma din sold, dar doar dacă există fonduri suficiente.
    Dacă nu, afișează un mesaj de eroare și soldul rămâne neschimbat.
    -> Date Partajate (Membru static): Toate conturile dintr-o bancă au aceeași dobândă. 
    Vom modela acest lucru cu un membru private static double rataDobanda.
    -> Acțiuni la Nivel de Clasă (Metode static): Adaugă o metodă public static void seteazaRataDobanda(double rataNoua).
    Această metodă va fi folosită de "bancă" pentru a schimba dobânda pentru toate conturile existente și viitoare.
    Se va apela direct pe clasă: ContBancar::seteazaRataDobanda(...). Adaugă o metodă non-statică numită aplicaDobanda().
    Aceasta calculează dobânda pentru contul curent (sold * rataDobanda) și o adaugă la sold.
*/

class ContBancar(
    private var titularCont: String,
    private var sold: Double
){
    companion object {
        private var rataDobanda : Double = 0.0

        fun seteazaRataDobanda(rataNoua: Double) {
            rataDobanda = rataNoua
            println("Rata Dobanda actualizata la ${rataDobanda}.")
        }
    }

    fun aplicaDobanda(){
        this.sold += this.sold * ContBancar.rataDobanda
        println("S-a aplicat rata dobanda la soldul contului de titular ${this.titularCont}")
    }

    fun retrage(suma: Double){
        when {
            suma > this.sold -> println("Eroare retragere suma de $suma din contul lui ${this.titularCont}. Sold < suma de retras.")
            else -> {
                this.sold -= suma
                println("Succes retragere suma de $suma din contul lui ${this.titularCont}.")
            }
        }
    }

    fun depune(suma: Double) {
        this.sold += suma
        println("Succes depunere suma de $suma in contul lui ${this.titularCont}.")
    }

    //  getters
    fun getTitularCont(): String { return this.titularCont}
    fun getSold(): Double { return this.sold}

    //  setters
    fun setTitularCont(value: String) {
        this.titularCont = value
    }

    fun setSold(value: Double){
        this.sold = value
    }

}

fun main(){
    var cont1 = ContBancar(titularCont= "Stefan Tipatescu",sold = 21.4)
    var cont2 = ContBancar(titularCont= "Zoe Trahanache",sold = 68.99)

    println("Cont1:\nTitular cont: ${cont1.getTitularCont()}\nSold initial: ${cont1.getSold()}")
    println("Cont2:\nTitular cont: ${cont2.getTitularCont()}\nSold initial: ${cont2.getSold()}")
    println()  

    cont1.depune(20.0);

    println("Cont1 sold: ${cont1.getSold()}")
    cont1.retrage(50.23);

    cont2.retrage(30.89);

    println("Cont2 sold: ${cont2.getSold()}")
    println()

    ContBancar.seteazaRataDobanda(0.07);

    cont1.aplicaDobanda();
    cont2.aplicaDobanda();

    println("Cont1 sold: ${cont1.getSold()}")
    println("Cont2 sold: ${cont2.getSold()}")
}