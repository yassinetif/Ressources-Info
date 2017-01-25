/**
* @author DIMITRI BERNOT
* @version 0.1 : Date : Tue Jan 24 16:07:45 CET 2017
*
*/

import java.util.*;

class NoSuchElementException extends Exception {
	public NoSuchElementException() {
		System.out.println("Element non present dans la base");
	}
}
public class BaseDocuments { 
	// COMPLETER // attribut(s) et constructeur(s)
	private List listeDoc;

	public BaseDocuments() {
		listeDoc = new LinkedList();
	}
	
	/** ajoute un document dans la base de documents 
	* @param d le document à ajouter 
	*/ 
	public BaseDocuments ajouter(Document d) {
		listeDoc.add(d);
		return this;
	}

	/** supprime un document de la base de documents (si il est plusieurs 
	* fois présents, une seule des occurrences est supprimée). Il 
	* importe peu que le document soit emprunté ou non au moment de sa 
	* suppression. 
	* @param d le document à supprimer 
	* @return le document supprimé, null s’il n’existe pas 
	*/ 
	public Document retirer(Document d) {
		if(listeDoc.remove(d)) {
			return d;
		}

		return null;
	}

	/** affiche tous les documents de la mediathèque (pour impression 
	* du catalogue par exemple) 
	*/
	public void afficher() {
		System.out.println(this);
	}

	public String toString() {
		String chaine = new String();
		for(int i = 0; i < listeDoc.size(); i++) {
			chaine += listeDoc.get(i) + "\n";
		}

		return chaine;
	}

	/** indique si le document donné est disponible (non emprunté) 
	* @param d le document concerné 
	* @return true si le document donné est disponible (non emprunté) 
	* @exception NoSuchElementException si le document n’existe 
	* pas dans la mediathèque 
	*/ 
	public boolean estDisponible(Document d) throws NoSuchElementException {
		if(listeDoc.indexOf(d) != -1) {
			return true;
		} else {
			throw new NoSuchElementException();
		}
		
	}

	/** permet d’emprunter un document 
	* @param d le document concerné 
	* @exception NoSuchElementException si le document n’existe 
	* pas dans la mediathèque 
	* @return true si le document donné était disponible et a pu être emprunté 
	*/ 
	public boolean emprunter(Document d) throws NoSuchElementException {
		try {
			if(estDisponible(d)) {
				emprunter(d);
				return true;
			}
		} catch(NoSuchElementException e){};
		return false;
	}

	/** permet de rendre un document 
	* @param d le document concerné 
	*/ 
	public boolean rendre(Document d) throws NoSuchElementException {
		try {
			if(!estDisponible(d)) {
				rendre(d);
				return true;
			}
		} catch(NoSuchElementException e){};
		return false;
	}

	/** Parcourt tous les documents de la base et les renvoie s'ils correspondent à certains critères
	* @param s le sélectionneur comprenant les critères demandés
	* @return L'itérateur content les documents sélectionnés
	*/ 
	public Iterator selectionne(Selectionneur s) {
		ArrayList listeDocSelectionnes = new ArrayList();
		for(int i = 0; i < listeDoc.size(); i++) {
			if(s.estSatisfaitPar((Document)listeDoc.get(i))) {
				listeDocSelectionnes.add(listeDoc.get(i));
			}
		}
		Iterator i = listeDocSelectionnes.iterator();
		return i;
	}

	/** Trie une liste de documents avec un comparateur donné
	* @param i l'itérateur comprenant les documents, c la fonction comparant les dits éléments
	* @return La liste triée
	*/
	public static List listeTriee(Iterator<Document> i, Comparator c) {
		List<Document> liste = new ArrayList<Document>();
		while(i.hasNext()) {
			liste.add(i.next());
		}

		Collections.sort(liste, c);

		System.out.println(liste);
		return liste;
	}
}