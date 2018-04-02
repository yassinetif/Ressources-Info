package controller;

import entity.Language;
import entity.Text;
import java.util.ArrayList;
import java.util.List;
import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ManagedProperty;
import javax.faces.bean.RequestScoped;
import stateless.LanguagesBeanLocal;

@ManagedBean(name="editions")
@RequestScoped

public class EditionController {
	@EJB
	private LanguagesBeanLocal languageSB;

	@ManagedProperty("#{languages.select}")
	private Long actual;								//id du langage actuel
	private Language langage = null;					//Langage actuel
	private List<Text> texts = new ArrayList<Text>();	//Les messages du langage actuel

	//Property actual
	public void setActual(Long actual){
		this.actual = actual;
		this.langage = languageSB.getLanguage(actual);
		this.texts.addAll(langage.getTexts()); 	//Ajout des textes
		this.texts.add(new Text());				//Ajout d'une ligne vide
	}

	//Property language
	public Language getLanguage(){ return this.langage; }

	//Property text
	public List<Text> getTexts(){ return texts; }
	public void setTexts(List<Text> texts){ return this.texts = texts; }

	public String doAddText(){
		Text text = this.texts.get(this.texts.size() - 1);	//Récupère le dernier élément
		if(text.getValue() != null && !"".equals.(text.getValue() && text.getAttribut() != null && !"".equals(text.getAttribut())){
			this.langage.setTexts(texts);
			language = languageSB.updateLanguage(language);	//Sauvegarde
			this.texts.add(new Text());						//Ajout d'une ligne vide
		}
		return "";
	}

	public String doFinish(){
		this.texts.remove(this.texts.size() - 1);
		this.language.setTexts(texts);
		language = languageSB.updateLanguage(language);
		return "index";
	}

}