/**
* @author DIMITRI BERNOT
* @version 0.1 : Date : Tue Jan 10 18:46:44 CET 2017
*
*/
public class Rationnel {
	private int p;
	private int q;
	
	public Rationnel(int p, int q) {
		this.p = p;
		this.q = q;
		if(this.q == 0) {
			System.out.println("/!\\ Dénominateur égal à 0, sera donc mis à 1"); // Utiliser une exception, mais j'y connais rien lol
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

	public void affiche() {
		System.out.println(" " + p + " / " + q + " ");
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

	public static void main(String args[]) {
		//Rationnel.Question1();
		Rationnel.Question2();

		System.exit(0);
	}
}