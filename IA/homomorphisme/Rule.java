import java.util.ArrayList;
import java.util.HashMap;


public class Rule {
	private HashMap<String, ArrayList<Atome>> atomes;
	private Atome conclusion;
	
	public Rule() {
		this.atomes = new HashMap<String, ArrayList<Atome>>();
	}
	
	public void addAtome(String predicat, Atome a) {
		if(!atomes.containsKey(predicat)) {
			atomes.put(predicat, new ArrayList<Atome>());
		}
		atomes.get(predicat).add(a);
	}
	
	public void setConclusion(Atome a) {
		this.conclusion = a;
	}
} 
