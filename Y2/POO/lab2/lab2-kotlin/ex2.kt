class Motorbike(var producer: String, var model: String,var engine: String,var year: Int,var price: Float){

    constructor() this("N/A","N/A","N/A",-1,-1.){println("Constructor1")}
    constructor(var producer: String, var model: String, var engine: String) this(producer,model,engine,year){
        println("Constructo2")
    }
    constructor(var producer: String, var model: String, var engine: String, var year:Int) this(producer,model,engine,year,-1.){
        println("Constructor3")
    }
    constructor(var producer: String, var model: String,var engine: String,var year: Int,var price: Float) this(producer,model,engine,year,price){
        println("Constructo4")
    }
}


fun main(){
    var motor = Motorbike()
}