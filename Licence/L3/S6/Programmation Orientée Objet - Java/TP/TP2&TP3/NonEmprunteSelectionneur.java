/**
* @author DIMITRI BERNOT
* @version 0.1 : Date : Wed Jan 25 09:35:38 CET 2017
*
*/

public class NonEmprunteSelectionneur implements Selectionneur {
	public boolean estSatisfaitPar(Document d) {
		return !(d.getEmprunt());
	}
}