import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Iterator;


public class ParserHomo {
	public static Homomorphisme parse(String fileName)
	{
		try {
			ArrayList<String> l = (ArrayList<String>) Files.readAllLines(Paths.get(fileName), StandardCharsets.UTF_8);
			Iterator<String> it = l.iterator();
			
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
		boolean isConstant = s.contains("\"");
		s.replaceAll("\"", "");
		
		String[] atomes = s.split(";");
		for (int i = 0; i < atomes.length; i++) {
			String temp[] = atomes[i].split("\\(");
			String predicat = temp[0];
			String [] termes = temp[1].substring(0, temp[1].length() - 1).split(",");
			ArrayList<Terme> a = new ArrayList<Terme>();
			for (int j = 0; j < termes.length; j++) {
				System.out.println("terme : " + termes[j]);
				Terme t = new Terme(isConstant, termes[j]);
				a.add(t);
			}
			e.addAtome(predicat, new Atome(a));
		}
		
		return e;
	}
	
}
