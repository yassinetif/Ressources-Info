/**
* @author DIMITRI BERNOT
* @version 0.1 : Date : Tue Jan 24 15:48:54 CET 2017
*
*/

class InvalidEmpruntException extends Exception {
	public InvalidEmpruntException() {
		System.out.println("Erreur dans la présence du document\n");
	}
}

class InvalidEmpruntExceptionPresent extends InvalidEmpruntException {
	public InvalidEmpruntExceptionPresent() {
		System.out.println("Document déjà présent\n");
	}
}

class InvalidEmpruntExceptionAbsent extends InvalidEmpruntException {
	public InvalidEmpruntExceptionAbsent() {
		System.out.println("Document absent\n");
	}
}

public class Document {
	private Auteur auteur;
	private String titre;
	private boolean emprunt;

	public Document(Auteur auteur, String titre) {
		this.auteur = auteur;
		this.titre = titre;
		this.emprunt = false;
	}
	
	/** Donne l'auteur du document en question
	* @return L'auteur du document
	*/ 
	public Auteur getAuteur() {
		return auteur;
	}

	/** Donne le titre du document en question
	* @return Le titre du document
	*/ 
	public String getTitre() {
		return titre;
	}

	/** Indique si le document est emprunté ou non
	* @return True si le document est emprunté, false sinon
	*/ 
	public boolean getEmprunt() {
		return emprunt;
	}

	/** Emprunte le document en question
	* @return True si le document a pu être emprunté, InvalidEmpruntExceptionAbsent si le document est déjà emprunté
	*/ 
	public void emprunter() throws InvalidEmpruntExceptionAbsent {
		if(emprunt == true) {
			throw new InvalidEmpruntExceptionAbsent();
		} else {
			emprunt = true;
		}
	}

	/** Rend le document en question
	* @return True si le document a pu être rendu, InvalidEmpruntExceptionPresent si le document est déjà disponible
	*/ 
	public void rendre() throws InvalidEmpruntExceptionPresent {
		if(emprunt == false) {
			throw new InvalidEmpruntExceptionPresent();
		} else {
			emprunt = false;
		}
	}

	/** Convertit un document en chaîne
	* @return La chaîne correspondant au document
	*/ 
	public String toString() {
		return titre + " - " + auteur + " : " + emprunt;
	}

	/** Affiche un document
	*/
	public void afficher() {
		System.out.println(this);
	}

	/** Indique si deux documents sont égaux
	* @param o Objet correspondant à doc2
	* @return Vrai ou faux, selon l'égalité des documents
	*/ 
	public boolean equals(Object o) {
		if(o instanceof Document) {
			Document doc = (Document)o;
			return getAuteur() == doc.getAuteur() && getTitre() == doc.getTitre();
		}
		return false;
	}
}