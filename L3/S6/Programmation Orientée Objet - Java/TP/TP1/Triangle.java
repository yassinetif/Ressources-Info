/**
* @author DIMITRI BERNOT
* @version 0.1 : Date : Wed Jan 11 09:20:08 CET 2017
*
*/

public class Triangle {
	private Point[] points;

	public Triangle(Point[] points) {
		if(points.length >= 3) {
			this.points = new Point[3];
			for(int i = 0; i < 3; i++) {
				this.points[i] = points[i];
			}
		} else {
			System.out.println("3 points sont necessaires !");
		}
	}

	public Triangle(Droite[] droites) {
		if(droites.length >= 3) {
			int nbPoints = 0;
			this.points = new Point[3];
			Point inter;
			for(int i = 0; i < 3; i++) {
				for(int j = i+1; j < 3; j++) {
					inter = droites[i].intersection(droites[j]);
					if(inter != null) { // Droites non parallèles
						this.points[nbPoints] = inter;
						nbPoints++;
					} else {
						System.out.println("Deux des droites sont paralleles");
						return;
					}
				}
			}
		} else {
			System.out.println("3 droites sont necessaires !");
		}
	}

	public double perimetre() {
		double peri = 0.0;

		for(int i = 0; i < 3; i++) {
			peri += points[i].distance(points[(i+1) % 3]);
		}

		return peri;
	}

	public double surface() {
		// On créé un rectangle fictif dont la base sera droite
		double sur = 0.0;
		Point[] pointsFictifs = new Point[3];
		pointsFictifs[0] = new Point(this.points[0].absc(), this.points[0].ordo());
		pointsFictifs[1] = new Point(this.points[0].distance(this.points[1]), 0);
		pointsFictifs[2] = new Point(this.points[0].distance(this.points[2]), this.points[0].distance(this.points[1]));
		
		Triangle triangleFictif = new Triangle(pointsFictifs);

		triangleFictif.afficher();

		double lg = (triangleFictif.points[2].absc() - triangleFictif.points[0].absc()) * (triangleFictif.points[1].ordo() - triangleFictif.points[0].ordo());

		return lg;
	}

	/* METHODES D'AFFICHAGE ET DE TEST */

	public void afficher() {
		for(int i = 0; i < 3; i++) {
			System.out.println(" Point " + i + " - x: " + this.points[i].absc() + "; y: " + this.points[i].ordo());
		}
	}

	public static void test() {
		System.out.println("Creation d'un triangle en (0,0), (4, 0), et (0, 3)");
		Point p[] = new Point[3];
		p[0] = new Point(0, 0);
		p[1] = new Point(4, 0);
		p[2] = new Point(0, 3);
		
		Triangle t1 = new Triangle(p);
		
		t1.afficher();

		System.out.println("Perimetre du rectangle : " + t1.perimetre());
		System.out.println("Surface du rectangle : " + t1.surface());
	}

	public static void main(String args[]) {
		Triangle.test();
	}
}