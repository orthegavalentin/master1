import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.HashSet;


public class Homomorphisme {
	Ensemble e1;
	Ensemble e2;
	HashSet<String> vars;
	HashSet<String> consts;

	public Homomorphisme() {
		vars = new HashSet<String>();
		consts = new HashSet<String>();
	}

	public void setEnsemble1(Ensemble e) {
		e1 = e;
	}
	
	public void setEnsemble2(Ensemble e) {
		e2 = e;
	}
	
	private String getFormattedTermes() {
		HashSet<String> vars = e1.getVariables();
		HashSet<String> consts = e2.getVariables();
		String s = "" + vars.size() + "\n";
		
		for (String s1 : vars) {
			s += s1;
			for (String s2 : consts) {
				s += ";" + s2;
			}
			s += "\n";
		}
		
		return s;
	}

	public void export() throws FileNotFoundException, UnsupportedEncodingException {
		String ex = "";
		int cpt = 0;

		System.out.println("==========");
		for (String s : e1.getPredicats()) {
			ArrayList<Atome> a1 = e1.getAtomes(s);
			ArrayList<Atome> a2 = e2.getAtomes(s);
			for (Atome atome1 : a1) {
				int n = 0;
				String temp = "";
				for (Atome atome2 : a2) {
					if(atome2.canWorkWith(atome1)) {
						n++;
						temp += atome2 + "\n";
					}
				}
				if(n > 0) {
					cpt++;
					ex += atome1.toString() + "\n" + n + "\n" + temp;
				}
			}
		}
		ex = "" + "E\n" + getFormattedTermes() + cpt + "\n" + ex;
		//System.out.println("***************");
		//System.out.println(ex);
		
		PrintWriter writer = new PrintWriter("homoexport.txt", "UTF-8");
		writer.println(ex);
		writer.close();
	}
	
	public CSP toCSP() {
		String ex = "";
		int cpt = 0;

		System.out.println("==========");
		for (String s : e1.getPredicats()) {
			ArrayList<Atome> a1 = e1.getAtomes(s);
			ArrayList<Atome> a2 = e2.getAtomes(s);
			for (Atome atome1 : a1) {
				int n = 0;
				String temp = "";
				for (Atome atome2 : a2) {
					if(atome2.canWorkWith(atome1)) {
						n++;
						temp += atome2 + "\n";
					}
				}
				if(n > 0) {
					cpt++;
					ex += atome1.toString() + "\n" + n + "\n" + temp;
				}
			}
		}
		ex = "" + "E\n" + getFormattedTermes() + cpt + "\n" + ex;
		//System.out.println("***************");
		//System.out.println(ex);
		
		return Parser.parseString(ex);
	}
}
