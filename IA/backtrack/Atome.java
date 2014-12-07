import java.util.ArrayList;


public class Atome {
	private ArrayList<Terme> termes;

	public Atome(ArrayList<Terme> termes) {
		this.termes = termes;
	}

	public int getArite() {
		return termes.size();
	}
	
	public boolean unifiable(Atome a) {
		int size = Math.max(a.getArite(), this.getArite());
		
		ArrayList<Terme> a1 = new ArrayList<Terme>();
		for (Terme terme : this.getTermes()) {
			a1.add(new Terme(terme.isConstant(), terme.getLabel()));
		}
		
		ArrayList<Terme> a2 = new ArrayList<Terme>();
		for (Terme terme : a.getTermes()) {
			a2.add(new Terme(terme.isConstant(), terme.getLabel()));
		}
		
		int j = 0;
		boolean changed = true;
		while (j < size) {
			changed = false;
			changed = unify(a1, a2, j);
			boolean temp = unify(a2, a1, j);
			if(temp || changed) {
				changed = true;
				j = 0;
			}
			j++;
		}
		for (int i = 0; i < size; i++) {
			if(!a1.get(i).equals(a2.get(i))){
				return false;
			}
		}
		return true;
	}
	
	private boolean unify(ArrayList<Terme> a1, ArrayList<Terme> a2, int index) {
		boolean changed = false;
		if(a1.get(index).isConstant() && !a2.get(index).isConstant()) {
			String var = a2.get(index).getLabel();
			String terme = a1.get(index).getLabel();
			for (Terme t : a2) {
				if(t.getLabel().equals(var)) {
					t.set(terme, true);
					changed = true;
				}
			}
		}
		return changed;
	}

	public boolean canWorkWith(Atome a) {
		String patternForThis = getSameTermes(this);
		String patternForA = getSameTermes(a);
		
		for (int i = 0; i < a.getTermes().size(); i++) {
			Terme t = a.getTermes().get(i);
			if(t.isConstant()) {
				if(!t.equals(this.getTermes().get(i))) {
					return false;
				}
			}
		}
		
		if(hasDuplicate(patternForA)) {
			return patternForA.equals(patternForThis);
		}
		return true;
	}
	
	public ArrayList<Terme> getTermes() {
		return this.termes;
	}

	private String getSameTermes(Atome a) {
		String s = "";
		ArrayList<String> set = new ArrayList<String>();
		
		for (int i = 0; i < a.getTermes().size(); i++) {
			String label = a.getTermes().get(i).getLabel();
			if(!set.contains(label)) {
				set.add(label);
			}
			s += set.indexOf(label);
		}
		return s;
	}
	
	private boolean hasDuplicate(String s) {
		for (int i = 0; i < s.length(); i++) {
			char c = s.charAt(i);
			if(s.indexOf(c) != s.lastIndexOf(c)) {
				return true;
			}
		}
		return false;
	}
	
	public String toString() {
		String s = "";
		
		for (Terme terme : termes) {
			s += terme.getLabel() + ";";
		}
		
		s = s.substring(0, s.length() - 1);
		s += "";
		
		return s;
	}
	
	public String export() {
		String s = "";
		
		for (Terme terme : termes) {
			s += terme.export() + ",";
		}
		
		s = s.substring(0, s.length() - 1);
		s += "";
		
		return s;
	}
	
	public boolean equals(Atome a) {
		for (int i = 0; i < termes.size(); i++) {
			if(!termes.get(i).equals(a.getTermes().get(i))) {
				return false;
			}
		}
		return true;
	}
}
