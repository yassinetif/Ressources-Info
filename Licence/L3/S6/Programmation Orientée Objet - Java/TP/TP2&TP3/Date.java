/**
* @author DIMITRI BERNOT
* @version 0.1 : Date : Tue Jan 24 13:40:22 CET 2017
*
*/

class InvalidDateException extends Exception {
	public InvalidDateException() {
		System.out.println("Erreur dans la date\n");
	}
}

public class Date implements Comparable {
	private int jour;
	private int mois;
	private int annee;

	public Date(int jour, int mois, int annee) throws InvalidDateException {
		if(jour > 31 || mois > 12 || jour < 1 || mois < 1 || annee < 1) {
			throw new InvalidDateException();
		} else {
			this.jour = jour;
			this.mois = mois;
			this.annee = annee;
		}
	}

	/** Donne le jour de la date concernée
	* @param Aucun
	* @return Le jour en question
	*/ 
	public int getJour() {
		return jour;
	}

	/** Donne le mois de la date concernée
	* @param Aucun
	* @return Le mois en question
	*/ 
	public int getMois() {
		return mois;
	}

	/** Donne l'année de la date concernée
	* @param Aucun
	* @return L'année en question
	*/ 
	public int getAnnee() {
		return annee;
	}

	/** Compare une date (d1) à celle donnée en paramètre (d2)
	* @param o Objet correspondant à d2
	* @return 0 si les dates sont égales, >0 si d1 > d2, <0 si d1 < d2
	*/ 
	public int compareTo(Object o) {
		Date d = (Date)o;
		if(this.getAnnee() != d.getAnnee()) {
			return getAnnee() - d.getAnnee();
		}

		if(this.getMois() != d.getMois()) {
			return getMois() - d.getMois();
		}

		if(this.getJour() != d.getJour()) {
			return getJour() - d.getJour();
		}

		return 0;
	}

	/** Indique si deux dates sont égales
	* @param o Objet correspondant à d2
	* @return Vrai ou faux, selon l'égalité des dates
	*/ 
	public boolean equals(Object o) {
		if(o instanceof Date) {
			Date d = (Date)o;
			return this.annee == d.getAnnee() && this.mois == d.getMois() && this.jour == d.getJour();
		} else {
			return false;
		}
	}

	/** Convertit une date en chaîne
	* @return La chaîne correspondant à la date
	*/ 
	public String toString() {
		return jour + "/" + mois + "/" + annee;
	}

	/** Affiche une date
	*/ 
	public void afficher() {
		System.out.println(this + "\n");
	}
}