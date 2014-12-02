import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;


public class Ensemble {
	HashMap<String, ArrayList<Atome>> ens;
	HashSet<String> vars;
	
	public Ensemble() {
		ens = new HashMap<String, ArrayList<Atome>>();
		vars = new HashSet<String>();
	}
	
	public void addAtome(String s, Atome a) {
		if(ens.get(s) == null) {
			ens.put(s, new ArrayList<Atome>());
		}
		ens.get(s).add(a);
		for (Terme t : a.getTermes()) {
			vars.add(t.getLabel());
		}
	}
	
	public HashSet<String> getVariables() {
		return this.vars;
	}
	
	public Set<String> getPredicats() {
		return ens.keySet();
	}
	
	public ArrayList<Atome> getAtomes(String key) {
		return ens.get(key);
	}
}
