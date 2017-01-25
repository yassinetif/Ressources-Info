/**
* @author DIMITRI BERNOT
* @version 0.1 : Date : Wed Jan 11 10:12:01 CET 2017
*
*/

public class Droite {
	private double a;
	private double b;

	public Droite(double a, double b) {
		this.a = a;
		this.b = b;
	}

	public double coeff() {
		return a;
	}

	public double ordonnee() {
		return b;
	}

	public double appliquer(double abscisse) {
		return abscisse * this.coeff() + this.ordonnee();
	}

	public double droiteEn(double x) {
		return (a*x + b);
	}

	public static Droite pointsToDroite(Point p1, Point p2) {
		// Système de deux équations à deux inconnues
		// p1.y = a * p1.x + b || p2.y = a * p2.x + b
		// p1.y - p2.y = a * (p1.x - p2.x)
		// a = (p1.y - p2.y) / (p1.x - p2.x) && b = p2.y - a * p2.x

		double a = (p1.ordo() - p2.ordo()) / (p1.absc() - p2.absc());
		double b = p2.ordo() - a * p2.absc();

		Droite result = new Droite(a, b);

		return result;
	}

	public boolean estParallele(Droite d) {
		return this.coeff() == d.coeff();
	}

	public Point intersection(Droite d) {
		if(this.estParallele(d)) {
			this.afficher();
			d.afficher();
			System.out.println("Droites paralleles");
			return null;
		} else {
			Droite inter = new Droite(this.coeff() - d.coeff(), this.ordonnee() - d.ordonnee());
			//y = ax + b -> x = y-b / a
			double result = (0 - inter.ordonnee()) / inter.coeff();

			Point resultat = new Point(result, this.appliquer(result));

			return resultat;
		}
	}

	/* METHODES D'AFFICHAGE ET DE TEST */

	public void afficher() {
		System.out.println("Droite d'equation " + a + "x + " + b);
	}

	public static void test() {
		System.out.println("\nCreation d'une droite d1 d'equation 5a + 2");
		Droite d1 = new Droite(5,2);
		d1.afficher();

		System.out.println("\nCreation d'une droite d2 a partir des points (1,2) et (3,1)");
		Point p1 = new Point(1,2);
		Point p2 = new Point(3,1);
		Droite d2 = Droite.pointsToDroite(p1, p2);
		d2.afficher();

		System.out.println("\nCreation de deux points (1,2) et (0,2) et verification de leur presence sur la droite d2");
		Point p3 = new Point(0,2);
		System.out.println("(1,2) : " + p1.estSurDroite(d2));
		System.out.println("(0,2) : " + p3.estSurDroite(d2));

		System.out.println("\nCreation d'un droite d3 (5, 12) et test de son parallelisme avec d1 et d2");
		Droite d3 = new Droite(5, 12);
		System.out.println("d3 et d1 : " + d3.estParallele(d1));
		System.out.println("d3 et d2 : " + d3.estParallele(d2));

		System.out.println("\nIntersection de d3 et d2");
		Point inter = d3.intersection(d2);
		inter.afficher();
		System.out.println("Verification : d3(intersection) = " + d3.appliquer(inter.absc()) + " ; d2(intersection) = " + d2.appliquer(inter.absc()));

		System.out.println("\nCreation d'une quatrieme droite d4 (0, 7) et creation d'un triangle a partir de trois droites non paralleles");
		Droite d4 = new Droite(0, 7);
		Droite droites[] = new Droite[3];
		droites[0] = d1;
		droites[1] = d2;
		droites[2] = d4;

		d1.afficher();
		d2.afficher();
		d4.afficher();
		Triangle t1 = new Triangle(droites);

		t1.afficher();
	}

	public static void main(String args[]) {
		Droite.test();
	}
}