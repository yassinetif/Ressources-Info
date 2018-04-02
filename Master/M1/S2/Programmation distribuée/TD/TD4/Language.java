@Entity

public class Language implements Serializable { //Liée à une session
	@Id
	private Long id;

	@Column(length=100, nullable=false, unique=true)
	private String name;

	@OneToMany(fetch=FetchType.LAZY, cascade=CascadeType.ALL)
	@JoinTable(joinColumns = {@JoinColumn(name="LANGUAGE_ID")}, inverseJoinColumns={@JoinColumn(name="TEXT_ID")})
	private List<Text> texts;
}