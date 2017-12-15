/*BIARDEAU
  TRISTAN
  M1
 */


import scala.util.Random

case class Dresseur(nom: String, age: Int)
case class Pkm(nom: String, typePkm: Option[String], evolution: Option[String], dresseur: Option[Dresseur], niveau: Int)


object pokemon {

	val marcel = Dresseur("Marcel", 10)
	val sacha = Dresseur("Sacha", 15)
	val salameche = Pkm("Salameche", Some("Feu"), Some("reptincel"), None, 10)
	val reptincel = Pkm("Reptincel", Some("Feu"), Some("dracaufeu"), Some(marcel), 12)
	val carapuce = Pkm("carapuce", Some("Eau"), None, Some(sacha), 40)

	val listePokemon = List(salameche, reptincel, carapuce)
	val listeDresseur = List(marcel, sacha)

	def lvlPkmSup(pkm: Pkm, lvl: Int): Boolean = {
		if(lvl < pkm.niveau){
			return true
		}
		return false
	}
	def listLvlPkmSup(lvl: Int): List[Pkm] = {
		return listePokemon.filter(lvlPkmSup(_, lvl))
	}



	def aUnDresseur(pkm: Pkm): Boolean = {
		if(pkm.dresseur != None){
			return true
		}
		return false
	}
	def listaUnDresseur(): List[Pkm] = {
		return listePokemon.filter(aUnDresseur(_))
	}

	def aUnDresseurDePlusDe14ans(pkm: Pkm): Boolean = {
		if(aUnDresseur(pkm)){
			if(pkm.dresseur.get.age > 14){
				return true
			}
		}
		return false
	}
	def listaUnDresseurDePlusDe14ans(): List[Pkm] = {
		return listePokemon.filter(aUnDresseurDePlusDe14ans(_))
	}

	def aUnDresseurLettreS(pkm: Pkm): Boolean = {
		if(aUnDresseur(pkm)){
			if(pkm.dresseur.get.nom.charAt(0) == 'S'){
				return true
			}
		}
		return false
	}
	def listaUnDresseurLettreS(): List[Pkm] = {
		return listePokemon.filter(aUnDresseurLettreS(_))
	}



	def listEvolution(): List[String] = {
		return listePokemon.filter(pkm => pkm.evolution != None).map(_.evolution.get).distinct
	}



	def ageDresseur(): Int = {
		val somme =  listeDresseur.map(_.age).sum 
		val nb = listeDresseur.size
		return somme / nb
	}

	def minMaxLvl(lstPkm: List[Pkm]): (Int, Int) = {
		val min = lstPkm.map(_.niveau).min
		val max = lstPkm.map(_.niveau).max
		return (min,max)
	}

	def aUnTypeEau(pkm: Pkm): Boolean = {
		if(pkm.typePkm == Some("Eau")){
			return true
		}
		return false
	}
	def listeDresseurAPkmEau(): List[Dresseur] = {
		return listePokemon.filter(aUnTypeEau(_)).filter(aUnDresseur(_)).map(_.dresseur.get)
	}


	//Question 1
	def combat(lstPkm: List[Pkm]): Pkm = {
		val challenger1 = lstPkm(Random.nextInt(lstPkm.size))
		val challenger2 = lstPkm(Random.nextInt(lstPkm.size))

		if(challenger1.niveau < challenger2.niveau){
			return challenger2
		}
		else{
			return challenger1
		}

	}


	//Question 2
	def combat2[A](lst: List[A], f: A => String): A = {
		val challenger1 = lst(Random.nextInt(lst.size))
		val challenger2 = lst(Random.nextInt(lst.size))
		val val1 = f(challenger1)
		val val2 = f(challenger2)
		print(val1)
		print(val2)
		if(val1.length>val2.length){
			return challenger1
		}else{
			return challenger2
		}
	}

	def main(args: Array[String]) {
		println("")

		val lvl = 11
		val pkmSup = listLvlPkmSup(lvl)
		println("Est de niveau superieur à " + lvl)
		pkmSup.map(println)
		println("")

		val pkmAyantDresseur = listaUnDresseur()
		println("A un dresseur :")
		pkmAyantDresseur.map(println)
		println("")

	
		val evolutions = listEvolution()
		println("Evolutions :")
		evolutions.map(println)
		println("")


		val pkmAyantDresseurDePlusDe14Ans = listaUnDresseurDePlusDe14ans()
		println("A un dresseur de plus de 14 ans:")
		pkmAyantDresseurDePlusDe14Ans.map(println)
		println("")


		val pkmAyantDresseurLettreS = listaUnDresseurLettreS()
		println("A un dresseur ayant 's' en début de nom :")
		pkmAyantDresseurLettreS.map(println)
		println("")

		val dresseursAyantPkmEau = listeDresseurAPkmEau()
		println("Dresseur ayant un pokemon eau :")
		dresseursAyantPkmEau.map(println)
		println("")

		print("Age moyen : " + ageDresseur())
		println("")

		println("Lvl (min,max) = " + minMaxLvl(listePokemon))

		println("Gagant du combat : " + combat(listePokemon).nom)

		//print(combat2(listePokemon,(x => x.name.size)))

	}
}