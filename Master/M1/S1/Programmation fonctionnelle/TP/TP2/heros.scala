import scala.io.Source
import java.io._


abstract class Character {
    def name: String
}

case class Civilian(name: String, wealth: Int) extends Character
case class SuperHero(name: String, powers: List[String], alterEgo: Option[Civilian])
  extends Character
case class Enemy(name: String, archEnemy: SuperHero) extends Character


object heros {

	val TonyStark = Civilian("Tony Stark", 1000000)
	val BruceWayne = Civilian("Bruce Wayne", 1000000)
	val ClarkKent = Civilian("Clark Kent", 1000)
	val Vide = Civilian("None", 0)

	val IronMan = SuperHero("Iron Man", List("SuperhumanStrength", "Genius", "Cyborg"),
	                        Some(TonyStark))
	val Batman = SuperHero("Batman", List("Genius", "Gadgets"), Some(BruceWayne))
	val Superman = SuperHero("SuperMan", List("SuperhumanStrength", "Invulnerability"),
	                         Some(ClarkKent))
	val Wolverine = SuperHero("Wolverine", List("SuperhumanStrength", "Invulnerability"), None)

	val personnes = List(IronMan, Batman, Superman, Wolverine, TonyStark, BruceWayne, ClarkKent)

	def estInvulnerable(person: Character): Boolean = person match {
  		case SuperHero(_, powers, _) if powers.contains("Invulnerability") => true
  		case _ => false
	}

	def aDeuxSupersPouvoirs(person: Character): Boolean = person match {
		case SuperHero(_, powers, _) if powers.size >= 2 => true
		case _ => false
	}

	def nePossedePasDAlterEgo(person: Character): Boolean = person match {
		case SuperHero(_, _, alterEgo) if alterEgo == None => true
		case _ => false
	}

	def alterEgo(person: Character) = person match {
		case SuperHero(_, _, alterEgo) if alterEgo != None => alterEgo
		case _ => None
	}

	def pauvre(person: Character): Boolean = person match {
		case SuperHero(_,_,Some(alterEgo)) if estInvulnerable(person) && pauvre(alterEgo) => true
		case Civilian(_, wealth) if wealth < 10000 => true
		case _ => false
	}


	def listArgent(person: List[Character]): Int = {
		person.map(fortune).sum
	}

	def fortune(person: Character): Int = person match {
		case Civilian(_, wealth) => wealth
		case _ => 0
	}


	def listePouvoirs(person: List[Character]) = {
		person.map(pouvoirs)
	}

	def pouvoirs(person: Character): Set[String] = person match {
		case SuperHero(_,powers,_) => powers.toSet
		case _ => Set()
	}

	def listNom(person: List[Character]) = {
		person.map(nom)
	}

	def nom(person: Character): String = person match {
		case Civilian(nom, _) => nom
		case SuperHero(nom,_,_) => nom
		case Enemy(nom, _) => nom
	}

	def estLaliasDeHero(person: Character): Boolean = person match{
		case SuperHero(_,_,_) => true
		case _ => false
	}

	def creerStringTout(person: Character) : String = {
		val name = person.name
		val powers = pouvoirs(person)
		val nameString = name.mkString.concat(",")
		val powersString = powers.mkString(",")
		val alter = alterEgo(person).getOrElse(Vide)
		val nomAlter = nom(alter).replace(" ", "")
		if((nom(alter) != "None")){
			val string = nameString.concat(powersString).concat(",").concat(nomAlter).concat(",").concat(fortune(alter).toString).concat("\n")
			string
		}else{
			val string = nameString.concat(powersString).concat(",").concat(nomAlter).concat("\n")
			string
		}
	}

	def ecrisTout() = {
		val hero = personnes.filter(estLaliasDeHero(_))
		val tout = hero.map(creerStringTout(_))
		scala.tools.nsc.io.File("personnes.csv").writeAll(tout.mkString)
	}


	def main(args: Array[String]) {
		println("Les personnes étant invulnerables : \n")
		val personneInvulnerables = personnes.filter(estInvulnerable(_))
		personneInvulnerables.map(println)

		println("\nLes personnes ayant au moins 2 pouvoirs : \n")
		val personneAyantDeuxPouvoir = personnes.filter(aDeuxSupersPouvoirs(_))
		personneAyantDeuxPouvoir.map(println)

		println("\nLes personnes n'ayant pas d'alterEgo : \n")
		val personneNonAlterEgo = personnes.filter(nePossedePasDAlterEgo(_))
		personneNonAlterEgo.map(println)

		println("\nLes civils gagant moins de 10000 euros et dont l'alterEgo est invulnerable : \n")
		val personnePauvreMaisInvulnerable = personnes.filter(pauvre(_))
		personnePauvreMaisInvulnerable.map(println)

		val argent = listArgent(personnes)
		println(argent)

		val allName = listNom(personnes)
		println(allName)

		val allPowers = listePouvoirs(personnes)
		println(allPowers)

		//scala.tools.nsc.io.File("personnes.csv").writeAll(allName.mkString("\n"))

		ecrisTout()

		val filename = "personnes.csv"
		for (line <- Source.fromFile(filename).getLines) {
    		println(line)
		}


	}

}
