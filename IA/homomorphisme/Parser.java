import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Iterator;


public class ParserHomo {
	
	public static KnowlegdeBase parseBc(String fileName) {
		try {
			ArrayList<String> l = (ArrayList<String>) Files.readAllLines(Paths.get(fileName), StandardCharsets.UTF_8);
			Iterator<String> it = l.iterator();
			String type = it.next();
			
			if(!type.equals("BC")) {
				return null;
			}

			KnowlegdeBase k = new KnowlegdeBase();
			
			int n = Integer.parseInt(it.next());
			for (int i = 0; i < n; i++) {
				String f = it.next();
				String temp[] = f.split("\\(");
				String predicat = temp[0];
				String [] termes = temp[1].substring(0, temp[1].length() - 1).split(";");
				k.addFait(predicat, parseAtome(termes));
			}
			System.out.println(k);
			
			n = Integer.parseInt(it.next());
			for (int i = 0; i < n; i++) {
				String r = it.next();
				Rule rule = new Rule();
				System.out.println(r);
				
			}
			
			return k;
		}
		catch(Exception e)
		{	
			return null;
		}
	}
	
	private static Atome parseAtome(String  [] termes) {
		ArrayList<Terme> a = new ArrayList<Terme>();
		for (int j = 0; j < termes.length; j++) {
			boolean isConstant = termes[j].contains("'");
			termes[j] = termes[j].replaceAll("'", "");
			Terme t = new Terme(isConstant, termes[j]);
			a.add(t);
		}
		return new Atome(a);
	}

	public static Homomorphisme parseHomo(String fileName)
	{
		try {
			ArrayList<String> l = (ArrayList<String>) Files.readAllLines(Paths.get(fileName), StandardCharsets.UTF_8);
			Iterator<String> it = l.iterator();
			String type = it.next();
			
			if(!type.equals("H")) {
				return null;
			}
			
			Homomorphisme h = new Homomorphisme();
			
			h.setEnsemble1(createEnsemble(it.next()));
			h.setEnsemble2(createEnsemble(it.next()));
			return h;
		}
		catch(Exception e)
		{	
			return null;
		}
	}
	
	private static Ensemble createEnsemble(String s) {
		System.out.println(s);
		Ensemble e = new Ensemble();	
		
		String[] atomes = s.split(";");
		for (int i = 0; i < atomes.length; i++) {
			String temp[] = atomes[i].split("\\(");
			String predicat = temp[0];
			String [] termes = temp[1].substring(0, temp[1].length() - 1).split(",");
			ArrayList<Terme> a = new ArrayList<Terme>();
			for (int j = 0; j < termes.length; j++) {
				boolean isConstant = termes[j].contains("'");
				termes[j] = termes[j].replaceAll("'", "");
				Terme t = new Terme(isConstant, termes[j]);
				a.add(t);
			}
			e.addAtome(predicat, new Atome(a));
		}
		
		return e;
	}
	
}
