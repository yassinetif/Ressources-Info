/**
* @author DIMITRI BERNOT
* @version 0.1 : Date : Tue Jan 24 14:53:44 CET 2017
*
*/

public class Auteur {
	private String nom;
	private Date naissance;
	private Date deces;

	public Auteur(String nom, Date naissance, Date deces) {
		this.nom = nom;
		this.naissance = naissance;
		this.deces = deces;
	}

	/** Donne le nom de l'auteur en question
	* @return Le nom de l'auteur
	*/ 
	public String getNom() {
		return nom;
	}

	/** Donne la date de naissance de l'auteur en question
	* @return Une date correspondant à la date de naissance de l'auteur
	*/ 
	public Date getNaissance() {
		return naissance;
	}

	/** Donne la date de décès de l'auteur en question
	* @return Une date correspondant à la date de décès de l'auteur, null si l'auteur est en vie
	*/ 
	public Date getDeces() {
		return deces;
	}

	/** Compare un auteur (a1) à celui donné en paramètre (a2) selon ces critères : Nom, date de naissance, date de décès
	* @param o Objet correspondant à a2
	* @return 0 si les auteurs sont égaux, >0 si a1 > a2, <0 si a1 < a2
	*/ 
	public int compareTo(Object o) {
		Auteur a = (Auteur)o;
		if(getNom() != a.getNom()) {
			return getNom().compareTo(a.getNom());
		}

		if(!(getNaissance().equals(a.getNaissance()))) {
			return getNaissance().compareTo(a.getNaissance());
		}

		if(getDeces() != null) {
			if(a.getDeces() != null) {
				return getDeces().compareTo(a.getDeces());
			}
			return -1;
		} else {
			if(a.getDeces() != null) {
				return -1;
			}
			return 0;
		}
	}

	/** Indique si deux auteurs sont égaux
	* @param o Objet correspondant à a2
	* @return Vrai ou faux, selon l'égalité des auteurs
	*/ 
	public boolean equals(Object o) {
		if(o instanceof Auteur) {
			Auteur a = (Auteur)o;
			return getNom() == a.getNom() && getNaissance() == a.getNaissance() && getDeces() == a.getDeces();
		}
		return false;
	}

	/** Convertit un auteur en chaîne
	* @return La chaîne correspondant à l'auteur
	*/ 
	public String toString() {
		if(deces != null) {
			return nom + ", " + naissance + ", " + deces;
		}

		return nom + ", " + naissance + ", toujours en vie";
	}

	/** Affiche un auteur
	*/
	public void afficher() {
		System.out.println(this);
	}
}