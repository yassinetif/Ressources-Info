@Local

public interface LanguagesBeanLocal {
	public List<Language> getAvailables();
	public Language createLanguage(String name);
	public Language getLanguage(Long id);
	public Language updateLanguage(Language langage);
}