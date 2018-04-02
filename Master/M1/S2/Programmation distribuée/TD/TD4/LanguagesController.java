package controller;

import entity.Language;
import java.io.Serializable;
import java.util.List;
import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import stateless.LanguagesBeanLocal;

@ManagedBean(name="languages")
@SessionScoped
public class LanguagesController implements Serializable {
	@EJB
	private LanguagesBeanLocal languageSB;

	private Long select = null;			//Langage actuel sélectionné
	private String newLanguage = null;	//Nouveau langage

	//Property select
	public Long getSelect(){ return this.select; }
	public void setSelect(Long select) { this.select = select; }

	//Property newLanguage
	public String getNewLanguage() { return this.newLanguage; }
	public void setNewLangugage(String newLanguage) { this.newLanguage = newLanguage;}

	//Property availables
	public List<Language> getAvailables() {
		return languageSB.getLanguage();
	}

	public String doSubmit() {
		//Création d'un nouveau langage
		if(newLanguage != null && !"".equals(language)){
			Language langage = languageSB.createLanguage(newLanguage);
			select = langage.getId();	//Simuler la sélection
			newLanguage = null;			//Vider la valeur de la propriété
		}

		//Sélection d'un langage
		if(select == null){
			return "edition";
		}
		return null;
	}
}