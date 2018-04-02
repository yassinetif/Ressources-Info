@Entity

public class Text implements Serializable {		//Lié à Language
	@Id
	private Long id;

	@Column(nullable=false, length=50, unique=true)
	private String attribut;

	@Column(nullable=false, length=200, unique=false)
	private String value;

	//Liste des accesseurs
	//..
	
	//Méthodes de l'interface Serializable
	//..
}