/**
* @author DIMITRI BERNOT
* @version 0.1 : Date : Wed Jan 11 09:07:04 CET 2017
*
*/

import java.lang.Math;

public class Point {
	private double x;
	private double y;

	public Point(double x, double y) {
		this.x = x;
		this.y = y;
	}

	public double absc() {
		return this.x;
	}

	public double ordo() {
		return this.y;
	}

	public boolean equals(Object o) {
		if(o instanceof Point) {
			Point p = (Point) o;
			return ((this.x == p.x) && (this.y == p.y));
		}
		return false;
	}

	public double distance(Point p) {
		double dist = Math.sqrt(Math.pow(this.x - p.x, 2) + Math.pow(this.y - p.y, 2));

		return dist;
	}

	public boolean estSurDroite(Droite d) {
		return this.ordo() == d.coeff() * this.absc() + d.ordonnee();
	}

	/* METHODES D'AFFICHAGE ET DE TEST */

	public void afficher() {
		System.out.println(" x: " + x + "; y: " + y);
	}

	public static void test() {
		System.out.println("Creation d'un point en 3, 4");
		Point p1 = new Point(3, 4);
		p1.afficher();

		System.out.println("Creation d'un point en 0, 0");
		Point p2 = new Point(0, 0);
		p2.afficher();

		System.out.println("Distance entre ces deux points : " + p1.distance(p2));
		
	}

	public static void main(String args[]) {
		Point.test();
	}
}