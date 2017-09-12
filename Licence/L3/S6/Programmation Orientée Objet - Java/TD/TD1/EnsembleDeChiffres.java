/**
* @author DIMITRI BERNOT
* @version 0.1 : Date : Tue Jan 10 18:00:51 CET 2017
*
*/

import java.lang.Math;

public class EnsembleDeChiffres {
	private boolean[] present;

	public EnsembleDeChiffres(int i) {
		present = new boolean[i];
	}

	public int longueur() {
		return this.present.length;
	}

	public void ajoute(int i) {
		present[i] = true;
	}

	public void retire(int i) {
		present[i] = false;
	}

	public void tirerAuHasard() {
		for(int i = 0; i < 10; i++) {
			present[i] = (Math.random() < 0.5);
		}
	}

	public boolean appartient(int i) {
		return present[i];
	}

	public boolean equals(Object o) {
		if(o instanceof EnsembleDeChiffres) {
			EnsembleDeChiffres e = (EnsembleDeChiffres) o;
			if(this.longueur() == e.longueur()) {
				int i = 0;
				while(i < this.longueur()) {
					if(this.appartient(i) == e.appartient(i)) {
						i++;
					} else {
						return false;
					}
				}

				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}

	public EnsembleDeChiffres intersectionAvec(EnsembleDeChiffres e) {
		int lg = Math.min(this.longueur(), e.longueur());
		EnsembleDeChiffres eFinal = new EnsembleDeChiffres(lg);

		for(int i = 0; i < lg; i++) {
			if(this.appartient(i) && e.appartient(i)) {
				eFinal.ajoute(i);
			}
		}

		return eFinal;
	}

	public EnsembleDeChiffres unionAvec(EnsembleDeChiffres e) {
		int lg = Math.max(this.longueur(), e.longueur());
		EnsembleDeChiffres eFinal = new EnsembleDeChiffres(lg);

		// Puisqu'on risque de regarder en dehors des limites d'un des tableaux, on doit vérifier à chaque fois qu'on est dans les limites
		for(int i = 0; i < lg; i++) {
			if((i < lg && this.appartient(i)) || (i < lg && e.appartient(i))) {
				eFinal.ajoute(i);
			}
		}

		return eFinal;
	}

	public boolean estInclusDans(EnsembleDeChiffres e) {
		return this.equals(this.intersectionAvec(e));
	}

	public void affiche() {
		System.out.print("(");
		for(int i = 0; i < this.longueur(); i++) {
			if(appartient(i)) {
				System.out.print(i + " ");
			}
		}
		System.out.println(")");
	}

	public static void Test() {
		System.out.println("Test avec l'ensemble des chiffres 0, 3, 4, 6, et 7 :\n");
		System.out.println(" - Creation et affichage d'un ensemble vide de 10 chiffres : ");
		EnsembleDeChiffres e = new EnsembleDeChiffres(10);
		e.affiche();

		System.out.println("\n - Ajout de 0, 3, 4, 6, et 7 : ");
		e.ajoute(0);
		e.ajoute(3);
		e.ajoute(4);
		e.ajoute(6);
		e.ajoute(7);
		e.affiche();

		System.out.println("\n - Test d'inclusion de e dans un tableau complet : ");
		EnsembleDeChiffres e1 = new EnsembleDeChiffres(10);
		e1.ajoute(0);
		e1.ajoute(1);
		e1.ajoute(2);
		e1.ajoute(3);
		e1.ajoute(4);
		e1.ajoute(5);
		e1.ajoute(6);
		e1.ajoute(7);
		e1.ajoute(8);
		e1.ajoute(9);
		e.affiche();
		e1.affiche();
		System.out.println("   e inclus dans e1 : " + e.estInclusDans(e1));

		System.out.println("\n - Retrait de 7 et test d'inclusion : ");
		e1.retire(7);
		e.affiche();
		e1.affiche();
		System.out.println("    e inclus dans e1 : " + e.estInclusDans(e1));
	}

	public static void main(String args[]) {
		EnsembleDeChiffres.Test();

		System.exit(0);
	}
}