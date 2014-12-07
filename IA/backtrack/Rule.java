import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;



public class Rule {
	private HashMap<String, ArrayList<Atome>> atomes;
	private Atome conclusion;
	private String predicatConclusion;
	
	public Rule() {
		this.atomes = new HashMap<String, ArrayList<Atome>>();
	}

	public void addAtome(String predicat, Atome a) {
		if(!atomes.containsKey(predicat)) {
			atomes.put(predicat, new ArrayList<Atome>());
		}
		atomes.get(predicat).add(a);
	}

	public void setConclusion(String predicat, Atome a) {
		this.conclusion = a;
		this.predicatConclusion = predicat;
	}

	public ArrayList<Atome> getAtomeWithPredicat(String predicat) {
		return atomes.get(predicat);
	}

	public String getPredicatConclusion() {
		return predicatConclusion;
	}

	public Atome assign(HashMap<String, Object> assignation) {
		ArrayList<Terme> a = new ArrayList<Terme>();

		for (Terme terme : conclusion.getTermes()) {
			String label = (String) assignation.get(terme.getLabel());
			if(label == null) {
				return null;
			}
			Terme t = new Terme(true, label);
			a.add(t);
		}

		Atome atome = new Atome(a);

		return atome;
	}

	@Override
	public String toString() {
		String s = "\n";
		for (String predicat : atomes.keySet()) {
			for (Atome a : atomes.get(predicat)) {
				s += predicat + "(" + a.toString() + ") ^ ";
			}
		}
		s = s.substring(0, s.length() - 2);
		s += "=> " + predicatConclusion + "(" + conclusion.toString() + ")";
		return s;
	}

	public String export() {
		String s = "";
		for (String predicat : atomes.keySet()) {
			for (Atome a : atomes.get(predicat)) {
				s += predicat + "(" + a.export() + ");";
			}
		}
		s = s.substring(0, s.length() - 1);
		return s;
	}
} 
