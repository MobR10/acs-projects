interface ISubscriber {
    fun update(masa: String)
}

class IRaphahell {
    private val abonatii = mutableListOf<ISubscriber>()

    fun subscribe(s: ISubscriber) {
        abonatii.add(s)
    }

    private fun notifica(mesaj: String) {
        for (s in abonatii) {
            s.update(mesaj)
        }
    }

    fun postezVideo(titlu: String) {
        println("Iraphahell: $titlu")
        notifica("A POSTAT IRAPHAHELL $titlu\n")
    }

    fun postezShort(titlu: String) {
        println("Iraphahell: $titlu")
        notifica("A POSTAT IRAPHAHELL!!!")
    }

    fun postezPostare(titlu: String) {
        println("Iraphahell: $titlu")
        notifica("Postare de la Iraphahell")
    }
}

class AppALert : ISubscriber {
    override fun update(masa: String) {
        println("Notificare app: $masa")
    }
}


fun main() {
    val canal = IRaphahell()
    canal.subscribe(AppALert())

    canal.postezVideo("WEEKEND-UL HORROR EP20")
    canal.postezShort("Fiti atenti la faza asta")
    canal.postezPostare("M-am tuns")
}
