/**
* @author DIMITRI BERNOT
* @version 0.1 : Date : Tue Jan 10 18:46:44 CET 2017
*
*/
public class Rationnel {
	private int p;
	private int q;

	public static Rationnel demi = new Rationnel(1, 2);
	
	public Rationnel(int p, int q) {
		this.p = p;
		this.q = q;
		if(this.q == 0) {
			System.out.println("/!\\ Denominateur egal a 0, sera donc mis a 1"); // Utiliser une exception, mais j'y connais rien lol
			this.q = 1;
		}
		this.reduire();
	}

	public int num() {
		return p;
	}

	public int den() {
		return q;
	}

	public static Rationnel intToRationnel(int i) {
		return new Rationnel(i, 1);
	}

	public double toDouble() {
		double res = (double)p/q; // Cast nécessaire, sinon division de deux entiers -> Résultat entier
		return res;
	}

	public Rationnel somme(Rationnel r) {
		int n = this.p * r.q + r.p * this.q;
		int d = this.q * r.q;

		Rationnel resultat = new Rationnel(n,d);
		return resultat;
	}

	public Rationnel difference(Rationnel r) {
		int n = this.p * r.q - r.p * this.q;
		int d = this.q * r.q;

		Rationnel resultat = new Rationnel(n,d);
		return resultat;
	}

	public Rationnel produit(Rationnel r) {
		Rationnel resultat = new Rationnel(this.p * r.p, this.q * r.q);
		return resultat;
	}

	public Rationnel quotient(Rationnel r) {
		Rationnel resultat = new Rationnel(this.p * r.q, this.q * r.p);
		return resultat;
	}

	public Rationnel puissance(int n) {
		Rationnel resultat = new Rationnel(1, 1);
		for(int i = 0; i < n; i++) {
			resultat = resultat.produit(this);
		}
		return resultat;
	}

	public int compareTo(Rationnel r) {
		if(this.toDouble() < r.toDouble()) {
			return -1;
		} else if(this.toDouble() == r.toDouble()) {
			return 0;
		} else {
			return 1;
		}
	}

	public Rationnel abs() {
		Rationnel inv = new Rationnel(this.p * (-1), this.q);
		if(this.compareTo(inv) >= 0) {
			return this;
		}

		return inv;
	}

	// Fonction calculant le PGCD honteusement copiée sur les Internets
	public int GCD(int a, int b) {
		if (b==0) return a;
			return GCD(b,a%b);
	}

	public Rationnel reduire() {
		int p = this.p / GCD(this.p, this.q);
		int q = this.q / GCD(this.p, this.q);

		this.p = p;
		this.q = q;

		return this;
	}

	public static Rationnel moyenne(Rationnel[] t) {
		Rationnel somme = new Rationnel(0, 1);
		for(int i = 0; i < t.length; i++) {
			somme = somme.somme(t[i]);
		}

		Rationnel div = new Rationnel(t.length, 1);
		somme = somme.quotient(div);
		
		return somme;
	}

	public static Rationnel[] systeme(int a, int b, int c, int d, int e, int f) {
		Rationnel entiers[] = new Rationnel[6];
		Rationnel resultat[] = new Rationnel[2];
		
		entiers[0] = intToRationnel(a);
		entiers[1] = intToRationnel(b);
		entiers[2] = intToRationnel(c);
		entiers[3] = intToRationnel(d);
		entiers[4] = intToRationnel(e);
		entiers[5] = intToRationnel(f);

		Rationnel u = entiers[0].produit(entiers[4]);
		Rationnel v = entiers[1].produit(entiers[3]);

		Rationnel g = u.difference(v);

		if(g.toDouble() == 0) {
			System.out.println("Le systeme ne dipose pas de solution unique");
		} else {
			System.out.println(g.toDouble());
			resultat[0] = entiers[1].produit(entiers[5]).difference(entiers[2].produit(entiers[4])).quotient(g); //x
			resultat[1] = entiers[2].produit(entiers[3]).difference(entiers[0].produit(entiers[5])).quotient(g); //y

			System.out.print("x = ");
			resultat[0].affiche();
			System.out.print("y = ");
			resultat[1].affiche();
		}

		return resultat;
	}

	public static Rationnel sqrt(Rationnel r, Rationnel precision) {
		Rationnel uk_1 = r.produit(Rationnel.demi);
		Rationnel uk = Rationnel.demi.produit(uk_1.somme(r.quotient(uk_1)));
		while(uk_1.difference(uk).abs().compareTo(precision) > 0) {
			uk_1 = uk;
			uk = Rationnel.demi.produit(uk_1.somme(r.quotient(uk_1)));
		}

		return uk;
	}

	public static Rationnel sqrtTest(Rationnel r, Rationnel precision) {
		Rationnel uk_1 = r.produit(Rationnel.demi);
		Rationnel uk = Rationnel.demi.produit(uk_1.somme(r.quotient(uk_1)));

		System.out.print("\nuk-1 : ");
		uk_1.affiche();
		System.out.print("uk : ");
		uk.affiche();
		System.out.print("Difference entre uk_1 et uk : ");
		uk_1.difference(uk).abs().affiche();

		while(uk_1.difference(uk).abs().compareTo(precision) > 0) {
			uk_1 = uk;
			uk = Rationnel.demi.produit(uk_1.somme(r.quotient(uk_1)));

			System.out.print("\nuk-1 : ");
			uk_1.affiche();
			System.out.print("uk : ");
			uk.affiche();
			System.out.print("Difference entre uk_1 et uk : ");
			uk_1.difference(uk).abs().affiche();
		}

		return uk;
	}

	public static Rationnel std(Rationnel[] t, Rationnel precision) {
		// sqrt(1/n * SUM(t[i] - t.moyenne)²

		Rationnel moyenne = Rationnel.moyenne(t);
		Rationnel sommeT = intToRationnel(0);
		Rationnel ecart;
		Rationnel resultat;

		for(int i = 0; i < t.length; i++) {
			ecart = t[i].difference(moyenne);
			sommeT = sommeT.somme(ecart.puissance(2));
		}

		System.out.println("Somme des ecarts a la moyenne : " + sommeT.toDouble());
		sommeT.produit(new Rationnel(1, t.length)).affiche();
		resultat = Rationnel.sqrt(sommeT.produit(new Rationnel(1, t.length)), precision);
		resultat.affiche();
		System.out.println(resultat.toDouble());

		return resultat;
	}

	/* AFFICHAGE */
	
	public void affiche() {
		System.out.println(" " + p + " / " + q + " ");
	}

	/* QUESTIONS DU TD */

	public static void Question1() {
		System.out.println("\nCreation du rationnel 12 / 28 :");
		Rationnel r = new Rationnel(12, 28);
		r.affiche();

		System.out.println("\nConversion du rationnel en double : " + r.toDouble());

		System.out.println("\nCreation du rationnel 2 / 28 :");
		Rationnel r1 = new Rationnel(2, 28);
		r1.affiche();

		System.out.println("\nOperations sur les rationnels :");
		System.out.println("\n - Somme :");
		r.affiche();
		System.out.println(" +");
		r1.affiche();
		System.out.println(" =");
		r.somme(r1).affiche();
		
		System.out.println("\n - Difference :");
		r.affiche();
		System.out.println(" -");
		r1.affiche();
		System.out.println(" =");
		r.difference(r1).affiche();

		System.out.println("\n - Produit :");
		r.affiche();
		System.out.println(" *");
		r1.affiche();
		System.out.println(" =");
		r.produit(r1).affiche();

		System.out.println("\n - Quotient :");
		r.affiche();
		System.out.println(" /");
		r1.affiche();
		System.out.println(" =");
		r.quotient(r1).affiche();
	}

	public static void Question2() {
		System.out.println("Creation de 0/2, 1/2, 2,2, 3/2, et 4/2 :");
		Rationnel tab[] = new Rationnel[4];
		tab[0] = new Rationnel(0,2);
		tab[1] = new Rationnel(1,2);
		tab[2] = new Rationnel(2,2);
		tab[3] = new Rationnel(3,2);

		tab[0].affiche();
		tab[1].affiche();
		tab[2].affiche();
		tab[3].affiche();

		System.out.println("\nMoyenne de ces rationnels :");
		moyenne(tab).affiche();
		
	}

	public static void Question3() {
		System.out.println("Creation d'un systeme avec a = 2 ; b = 4; c = 4; d = 4; e = 8; f = 10");
		Rationnel.systeme(2, 4, 4, 4, 8, 10);

		System.out.println("Creation d'un systeme avec a = 1 ; b = 12; c = 7; d = 0; e = 9; f = 3");
		Rationnel.systeme(1, 12, 7, 0, 9, 3);
		
	}

	public static void Question4() {
		System.out.println("Test de la racine carree avec 2");
		Rationnel deux = intToRationnel(2);
		Rationnel precision = new Rationnel(1, 10);
		Rationnel sqrt2 = Rationnel.sqrtTest(deux, precision);

		sqrt2.affiche();
		System.out.println(sqrt2.toDouble());

		System.out.println("Test de la racine carree avec 6.25");
		Rationnel nb = new Rationnel(25,4);
		Rationnel sqrtNb = Rationnel.sqrtTest(nb, precision);

		sqrtNb.affiche();
		System.out.println(sqrtNb.toDouble());
	}

	public static void Question5() {
		System.out.println("Test de l'ecart type avec [0,2,4,6,8,10]");
		Rationnel tab[] = new Rationnel[6];
		for(int i = 0; i < 6; i++) {
			tab[i] = intToRationnel(2*i);
		}

		Rationnel.std(tab, new Rationnel(1, 4)).affiche();
	}

	public static void main(String args[]) {
		//Rationnel.Question1();
		//Rationnel.Question2();
		//Rationnel.Question3();
		//Rationnel.Question4();
		Rationnel.Question5();
		//Rationnel.Question6();

		System.exit(0);
	}
}