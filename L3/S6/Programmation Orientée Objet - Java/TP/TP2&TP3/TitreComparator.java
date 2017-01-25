/**
* @author DIMITRI BERNOT
* @version 0.1 : Date : Wed Jan 25 10:21:06 CET 2017
*
*/

import java.util.Comparator;

public class TitreComparator implements Comparator {
	/** Compare deux documents selon leur titre
	* @param Object doc1 et doc2, correspondant aux deux documents à comparer 
	* @return Un entier correspondant au résultat de la comparaison
	*/ 
	public int compare(Object doc1, Object doc2) {
		Document d1 = (Document)doc1;
		Document d2 = (Document)doc2;
		return d1.getTitre().compareTo(d2.getTitre());
	}
}