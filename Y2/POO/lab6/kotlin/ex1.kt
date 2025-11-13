abstract class City(
    open var name: String,
    open var countyCode: Int
){
    abstract fun gtName(): String

    abstract fun gtCountyCode(): Int

    abstract fun gtType(): String
}

class Rural(override var name: String = "N/A",
override var countyCode: Int = 0): City(name,countyCode){
    override fun gtName(): String{
        return name
    }

    override fun gtCountyCode(): Int{
        return countyCode
    }

    override fun gtType(): String{
        print("Im a rural city\n")
        return "rural"
    }
}

class Industrial(override var name: String = "N/A",
override var countyCode: Int = 0): City(name,countyCode){
override fun gtName(): String{
        return name
    }

    override fun gtCountyCode(): Int{
        return countyCode
    }

    override fun gtType(): String{
        print("Im an industrial city\n")
        return "industrial"
    }
}

class Port(override var name: String = "N/A",
override var countyCode: Int = 0): City(name,countyCode){
    override fun gtName(): String{
        return name
    }

    override fun gtCountyCode(): Int{
        return countyCode
    }

    override fun gtType(): String{
        print("Im a port city\n")
        return "port"
    }
}
fun main(){
    val orasRural = Rural("Las Fierbinti", 50)
    println(orasRural.gtName())
    println(orasRural.gtCountyCode())
    orasRural.gtType()

    val orasIndustrial = Industrial("Londra", 12)
    println(orasIndustrial.gtName())
    println(orasIndustrial.gtCountyCode())
    orasIndustrial.gtType()

    val orasPort = Port("Mangalia", 67)
    println(orasPort.gtName())
    println(orasPort.gtCountyCode())
    orasPort.gtType()
}