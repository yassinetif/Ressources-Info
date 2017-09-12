/**
* @author DIMITRI BERNOT
* @version 0.1 : Date : Tue Jan 24 14:10:34 CET 2017
*
*/

import java.util.*;

public class Test {
	public static void date() {
		List l = new LinkedList();
		
		System.out.println("Creation de 1er janvier 1970");
		Date d1 = null;
		try {
			d1 = new Date(1, 1, 1970);
			d1.afficher();
		} catch(InvalidDateException e) {}

		System.out.println("Creation de 60 décembre 2014");
		Date d2 = null;
		try {
			d2 = new Date(60, 12, 2014);
			d2.afficher();
		} catch(InvalidDateException e) {}

		System.out.println("Creation de 2 septembre 1996");
		Date d3 = null;
		try {
			d3 = new Date(2, 9, 1996);
			d3.afficher();
		} catch(InvalidDateException e) {}

		System.out.println("Creation de 17 mars 1998");
		Date d4 = null;
		try {
			d4 = new Date(17, 3, 1998);
			d4.afficher();
		} catch(InvalidDateException e) {}

		System.out.println("Creation de 31 aout 2005");
		Date d5 = null;
		try {
			d5 = new Date(31, 8, 2005);
			d5.afficher();
		} catch(InvalidDateException e) {}

		l.add(d3);
		l.add(d1);
		l.add(d5);
		l.add(d4);

		for(int i = 0; i < l.size(); i++) {
    		System.out.print("Élément à l'index " + i + " = " + l.get(i));
		}

		System.out.println("Tri de la liste");
		Collections.sort(l);

		for(int i = 0; i < l.size(); i++) {
    		System.out.print("Élément à l'index " + i + " = " + l.get(i));
		}
	}

	public static void auteur() {
		System.out.println("Ajout de Don Rosa, 29/7/1951");
		Date d1 = null;
		try {
			d1 = new Date(29, 7, 1951);
		} catch(InvalidDateException e) {}
		
		Auteur a1 = new Auteur("Don Rosa", d1, null);
		a1.afficher();

		System.out.println("\nAjout de Tolkien, 3/1/1892, 2/9/1973");
		Date d2 = null;
		try {
			d2 = new Date(3, 1, 1892);
		} catch(InvalidDateException e) {}
		Date d3 = null;
		try {
			d3 = new Date(2, 9, 1973);
		} catch(InvalidDateException e) {}
		
		Auteur a2 = new Auteur("Tolkien", d2, d3);
		a2.afficher();

		System.out.println("\nTolkien, 3/1/1892, 2/9/1973");
		Auteur a3 = new Auteur("Tolkien", d2, d3);

		System.out.println("\nEgalite d'auteurs :");
		System.out.println("Don Rosa et Tolkien : " + a1.equals(a2));
		System.out.println("Tolkien et Tolkien : " + a2.equals(a3));
	}

	public static void document() {
		System.out.println("Ajout de La Communauté de l'Anneau, par Tolkien");
		
		Date d2 = null;
		try {
			d2 = new Date(3, 1, 1892);
		} catch(InvalidDateException e) {}
		Date d3 = null;
		try {
			d3 = new Date(2, 9, 1973);
		} catch(InvalidDateException e) {}
		Auteur a1 = new Auteur("Tolkien", d2, d3);

		Document doc1 = new Document(a1, "La Communauté de l'Anneau");
		doc1.afficher();

		System.out.println("\nAjout de Les Deux Tours, par Tolkien");
		Document doc2 = new Document(a1, "Les Deux Tours");
		doc2.afficher();

		System.out.println("\nEgalité entre les documents :");
		System.out.println("Doc1 & Doc2 : " + doc1.equals(doc2));
		System.out.println("Doc2 & Doc2 : " + doc2.equals(doc2));

		System.out.println("\n2 emprunts et 2 retours de Doc1");
		try {
			doc1.emprunter();
		} catch(InvalidEmpruntExceptionAbsent e) {}
		try {
			doc1.emprunter();
		} catch(InvalidEmpruntExceptionAbsent e) {}
		try {
			doc1.rendre();
		} catch(InvalidEmpruntExceptionPresent e) {}
		try {
			doc1.rendre();
		} catch(InvalidEmpruntExceptionPresent e) {}
	}

	public static void baseDocuments() {
		BaseDocuments b = new BaseDocuments();
		Iterator i;

		MotDansTitreSelectionneur s1 = new MotDansTitreSelectionneur("polymorphisme");
		
		Date d2 = null;
		try {
			d2 = new Date(3, 1, 1892);
		} catch(InvalidDateException e) {}
		Date d3 = null;
		try {
			d3 = new Date(2, 9, 1973);
		} catch(InvalidDateException e) {}
		Auteur a1 = new Auteur("Tolkien", d2, d3);

		System.out.println("Ajout de La Communauté de l'Anneau, par Tolkien");
		Document doc1 = new Document(a1, "La Communauté de l'Anneau");

		b.ajouter(doc1);

		System.out.println("\nAjout de Les Deux Tours, par Tolkien");
		Document doc2 = new Document(a1, "Les Deux Tours");
		b.ajouter(doc2);

		Date d4 = null;
		try {
			d4 = new Date(3, 1, 535);
		} catch(InvalidDateException e) {}
		Date d5 = null;
		try {
			d5 = new Date(2, 9, 4201);
		} catch(InvalidDateException e) {}
		Auteur a2 = new Auteur("Alduin", d4, d5);

		Document doc3 = new Document(a2, "Le polymorphisme d'Akatosh en Alduin");
		b.ajouter(doc3);

		Document doc4 = new Document(a2, "Autre polymorphisme : Exemple de Miraak et des lvl-1 noobs");
		b.ajouter(doc4);

		Document doc5 = new Document(a2, "Comment se faire pwned par un Dovahkiin");
		b.ajouter(doc5);

		System.out.println("\nAffichage de la base de documents");

		b.afficher();

		System.out.println("\nTri de la liste selon les documents contenant 'polymorphisme'");

		i = b.selectionne(s1);

		Comparator c = new TitreComparator();

		b.listeTriee(i, c);
	}

	public static void selectionneur() {
		BaseDocuments b = new BaseDocuments();
		Iterator i;
		
		Date d1 = null;
		try {
			d1 = new Date(3, 1, 1892);
		} catch(InvalidDateException e) {}
		Date d2 = null;
		try {
			d2 = new Date(2, 9, 1973);
		} catch(InvalidDateException e) {}
		Auteur a1 = new Auteur("Tolkien", d1, d2);

		Date d3 = null;
		try {
			d3 = new Date(29, 7, 1951);
		} catch(InvalidDateException e) {}
		Auteur a2 = new Auteur("Don Rosa", d3, null);

		Document doc1 = new Document(a1, "La Communauté de l'Anneau");
		b.ajouter(doc1);

		Document doc2 = new Document(a1, "Les Deux Tours");
		b.ajouter(doc2);

		Document doc3 = new Document(a2, "Le « Dissoutou »");
		b.ajouter(doc3);

		b.afficher();

		System.out.println("\nEmprunt de 'Les Deux Tours'");
		try {
			doc2.emprunter();
		} catch(InvalidEmpruntExceptionAbsent e) {}

		System.out.println("\nRecherche des documents non empruntes");
		NonEmprunteSelectionneur s1 = new NonEmprunteSelectionneur();

		i = b.selectionne(s1);

		while(i.hasNext()) {
			System.out.println(i.next());
		}

		System.out.println("\nRecherche des documents dont l'auteur était vivant en 1914");
		AuteurVivantSelectionneur s2 = new AuteurVivantSelectionneur(1914);

		i = b.selectionne(s2);

		while(i.hasNext()) {
			System.out.println(i.next());
		}

		System.out.println("\nRecherche des documents dont le titre contient 'Le'");
		MotDansTitreSelectionneur s3 = new MotDansTitreSelectionneur("Le");

		i = b.selectionne(s3);

		while(i.hasNext()) {
			System.out.println(i.next());
		}
	}

	public static void selectionneurComposite() {
		System.out.println("Ajout sélectionneurs permetant : Titre contient 'polymorphisme' ; Auteur vivant en 2005");
		SelectionneurComposite s = new SelectionneurComposite();
		MotDansTitreSelectionneur s1 = new MotDansTitreSelectionneur("polymorphisme");
		AuteurVivantSelectionneur s2 = new AuteurVivantSelectionneur(2005);

		s.add(s1);
		s.add(s2);

		// Création de la base de documents
		BaseDocuments b = new BaseDocuments();
		Iterator i;
		
		Date d1 = null;
		try {
			d1 = new Date(3, 1, 535);
		} catch(InvalidDateException e) {}
		Date d2 = null;
		try {
			d2 = new Date(2, 9, 4201);
		} catch(InvalidDateException e) {}
		Auteur a1 = new Auteur("Alduin", d1, d2);

		Date d3 = null;
		try {
			d3 = new Date(29, 7, 4180);
		} catch(InvalidDateException e) {}
		Auteur a2 = new Auteur("Dovahkiin", d3, null);

		Document doc1 = new Document(a1, "Le polymorphisme d'Akatosh en Alduin");
		b.ajouter(doc1);

		Document doc2 = new Document(a1, "Envahir Sovngarde pour les nuls");
		b.ajouter(doc2);

		Document doc3 = new Document(a2, "Le dernier Enfant de Dragon");
		b.ajouter(doc3);

		try {
			doc1.emprunter();
		} catch(InvalidEmpruntExceptionAbsent e) {};

		System.out.println("\nAffichage de la base de documents");
		b.afficher();

		i = b.selectionne(s);

		System.out.println("Documents satisfaisant le sélectionneur composite");
		while(i.hasNext()) {
			System.out.println(i.next());
		}
	}

	public static void main(String args[]) {
		//Test.date();
		//Test.auteur();
		//Test.document();
		Test.baseDocuments();
		//Test.selectionneur();
		//Test.selectionneurComposite();
	}
}