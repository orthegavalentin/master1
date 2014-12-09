import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

import javax.annotation.PreDestroy;


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

	public void sature() {
		boolean done = false;

		while(!done) {
			done = true;
			for (Rule rule : rules) {
				Solver s = new Solver(Parser.parseStringHomo(buildHomomorphismeString(rule)).toCSP());
				HashSet<HashMap<String, Object>> solutions= s.searchAllSolutions();
//				System.out.println("solutions : " + solutions);
				for (HashMap<String, Object> hashMap : solutions) {
					Atome a = rule.assign(hashMap);
					if(a != null) {
//						System.out.println("rule : " + rule.getPredicatConclusion());
						ArrayList<Atome> atomes = bf.get(rule.getPredicatConclusion());
//						System.out.println("trying to add : " + rule.getPredicatConclusion() + "(" + a.toString() + ")");
						if(atomes == null) {
							bf.put(rule.getPredicatConclusion(), new ArrayList<Atome>());
							atomes = bf.get(rule.getPredicatConclusion());
						}
						boolean contains = false;
						for (Atome atome : atomes) {
							if(a.equals(atome)) {
								contains = true;
							}
						}
						if(!contains) {
							atomes.add(a);
//							System.out.println("added");
							done = false;
						}
					}
				}
			}
		}
	}

	public HashSet<HashMap<String, Object>> requete(Rule r) {
		sature();
		Solver s = new Solver(Parser.parseStringHomo(buildHomomorphismeString(r)).toCSP());
		return s.searchAllSolutions();
	}

	private String buildHomomorphismeString(Rule rule) {
		String s = "H\n";
		s += rule.export();
		s += "\n" + buildBfString();
//		System.out.println("\nhomo string : " + s);
		return s;
	}
	
	private String buildBfString() {
		String bfString = "";

		for (String predicat : bf.keySet()) {
			for (Atome atome : bf.get(predicat)) {
				bfString += predicat + "(" + atome.export() + ");"; 
			}
		}
		bfString = bfString.substring(0, bfString.length() - 1);
		return bfString;
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
