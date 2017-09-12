/**
* @author DIMITRI BERNOT
* @version 0.1 : Date : Wed Jan 25 09:35:55 CET 2017
*
*/

public class AuteurVivantSelectionneur implements Selectionneur {
	private int annee;

	public AuteurVivantSelectionneur(int annee) {
		this.annee = annee;
	}
	
	public boolean estSatisfaitPar(Document d) {
		return d.getAuteur().getDeces() != null;
	}
}