/**
* @author DIMITRI BERNOT
* @version 0.1 : Date : Wed Jan 25 09:59:54 CET 2017
*
*/

import java.util.*;

public class SelectionneurComposite implements Selectionneur {
	private LinkedList listeSelec;

	public SelectionneurComposite() {
		listeSelec = new LinkedList();
	}

	public void add(Selectionneur s) {
		listeSelec.add(s);
	}

	public boolean estSatisfaitPar(Document d) {
		boolean satisfait = true;
		Selectionneur actuel;

		for(int i = 0; i < listeSelec.size(); i++) {
			actuel =  (Selectionneur)(listeSelec.get(i));
    		satisfait = satisfait & actuel.estSatisfaitPar(d);
		}

		return satisfait;
	}
}