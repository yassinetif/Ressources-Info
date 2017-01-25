/**
* @author DIMITRI BERNOT
* @version 0.1 : Date : Wed Jan 25 09:36:04 CET 2017
*
*/

public class MotDansTitreSelectionneur implements Selectionneur {
	private String m;

	public MotDansTitreSelectionneur(String m) {
		this.m = m;
	}
	
	public boolean estSatisfaitPar(Document d) {
		return d.getTitre().indexOf(m) != -1;
	}
}