import scala.io.Source

object TP1 {

	def afficherListe(l: List[Int]) = {
		l.map(println)
	}

	def abs(e: Int) = {
		if(e>=0){
			e
		}else{
			-e
		}
	}

	def toAbsolute(l: List[Int]) = {
		l.map(e => abs(e))
	}

	def calculNbElement(l: List[Int]): Int = {
		if(l.isEmpty){
			return 0
		}
		return 1 + calculNbElement(l.tail)
	}

	def invert1(l: List[Int]): List[Int] = {
		l.foldLeft(List[Int]()) { 
			(acc, elem) => elem :: acc
		}
	}

	def fib(n: Int): Int = {
		if (n <= 1){
			n
		}else{
			fib(n-2) + fib(n-1)
		} 
	}


	def fib2 (n: Int): Int = {
	    def fibT (n: Int, value: Int = 1, acc: Int = 0): Int = n match {
	      case 0 => acc
	      case _ => fibT(n - 1, acc, value + acc)
	    }
	    fibT(n)
  	}



	def main(args: Array[String]) {
		val l = List(1, -2, 3, 4)
		l.map(println)
		println("\n")
		val la = toAbsolute(l)
		la.map(println)
		println("\n")

		val lf = l.map {
			v => 
			if(v < 0) v
		}
		lf.map(println)

		l.filter(_ < 0).map(println)

		val nb = calculNbElement(l)
		println("Le nombre d'element de la liste " + l + " est : " + nb)

		val l42 = invert1(l)
		l42.map(println)

		println(fib2(7))

		if(args.length == 1) {
			val filename = args(0)
			if(scala.reflect.io.File(scala.reflect.io.Path(filename)).exists){
				for (line <- Source.fromFile(filename).getLines) {
	    			println(line)
				}
			}else{
				println("Le fichier n'existe pas")
			}
		}else{
			println("On attend un seul paramètre : le nom du fichier à lire")
		}
		
	}
}
