import java.util.ArrayList;
import java.util.HashMap;


public class KnowlegdeBase {
	private HashMap<String, ArrayList<Atome>> bf;
	private ArrayList<Rule> rules;
	
	public KnowlegdeBase() {
		this.bf = new HashMap<String, ArrayList<Atome>>();
		this.rules = new ArrayList<Rule>();
	}
	
	public KnowlegdeBase(HashMap<String, ArrayList<Atome>> bf) {
		this.bf = bf;
	}

	public HashMap<String, ArrayList<Atome>> getBf() {
		return bf;
	}

	public void setBf(HashMap<String, ArrayList<Atome>> bf) {
		this.bf = bf;
	}

	public ArrayList<Rule> getRules() {
		return rules;
	}

	public void setRules(ArrayList<Rule> rules) {
		this.rules = rules;
	}
	
	public void addRule(Rule r) {
		rules.add(r);
	}
	
	public void addFait(String s, Atome f) {
		if(!bf.containsKey(s)) {
			bf.put(s, new ArrayList<Atome>());
		}
		
		bf.get(s).add(f);
	}
	
	@Override
	public String toString() {
		String s = "Base de faits : \n";
		for (String string : bf.keySet()) {
			for (Atome a : bf.get(string)) {
				s += string + "(" + a + ")\n";
			}
		}
		s += "\nBase de regles : " + rules.toString();
		return s;
	}
}
