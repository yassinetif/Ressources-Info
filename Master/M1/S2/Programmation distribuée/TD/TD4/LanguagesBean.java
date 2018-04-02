@Stateless(name="languageSB")
@TransactionAttribute(value="TransactionAttributeType.REQUIRED")
public class LanguagesBean implements LanguagesBeanLocal {
	@PersistenceContext(unitName="Tutorial-war")
	private EntityManager em;

	@Override
	public List<Language> getAvailables(){
		return em.executeQuery("SELECT l FROM Language l").getResultList();
	}

	@Override
	public Language createLanguage(String name){
		Language language = null;
		try{
			Query query = em.executeQuery("SELECT l FROM Language l WHERE l.name LIKE :param");
			query.setParameter("param", name);
			language = (Language) query.getSingleResult();
		}catch(NoResultException e){ //Si le langage n'est pas présent dans la base
			language = new Language();
			language.setName(name);
			em.persist(language);
		}
		return language;
	}

	@Override
	public Language getLanguage(Long id){
		return (Language) em.find(Language.class, id);
	}

	@Override
	public Language updateLanguage(Language language){
		em.persist(em.merge(language));	//Car merge est serialisable
		return language;
	}
}