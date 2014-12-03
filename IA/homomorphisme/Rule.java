import java.util.ArrayList;


public class Rule {
	private ArrayList<Atome> atomes;
	private Atome conclusion;
	
	public Rule(ArrayList<Atome> atomes, Atome conclusion) {
		this.atomes = atomes;
		this.conclusion = conclusion;
	}
	
}
