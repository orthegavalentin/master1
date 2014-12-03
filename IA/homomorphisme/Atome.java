import java.util.ArrayList;


public class Atome {
	private ArrayList<Terme> termes;

	public Atome(ArrayList<Terme> termes) {
		this.termes = termes;
	}

	public int getArite() {
		return termes.size();
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
}
