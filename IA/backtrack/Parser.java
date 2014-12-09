import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;


public class Parser {

	public static CSP parse(String fileName)
	{
		try {
			ArrayList<String> l = (ArrayList<String>) Files.readAllLines(Paths.get(fileName), StandardCharsets.UTF_8);
			Iterator<String> it = l.iterator();
			String type = it.next();
			if(type.equals("E"))
			{
				return parseFromExt(it);
			}
			else if(type.equals("I"))
			{
				return parseFromInt(it);
			}
		}
		catch(Exception e)
		{	
			return null;
		}
		return null;
	}
	
	public static CSP parseString(String s) {
		String[] l = s.split("\n");
		ArrayList<String> list = new ArrayList<String>();
		for (int i = 0; i < l.length; i++) {
			list.add(l[i]);
		}
		Iterator<String> it = list.iterator();
		String type = it.next();
		if(type.equals("E"))
		{
			return parseFromExt(it);
		}
		else if(type.equals("I"))
		{
			return parseFromInt(it);
		}
		return null;
	}

	private static CSP parseFromExt(Iterator<String> it)
	{
		CSP p = new CSP();

		int nbVariables = Integer.parseInt(it.next());
		for (int i = 1; i < nbVariables + 1; i++) {
			String [] variables = it.next().split(";");
			p.addVariable(variables[0]);
			for (int j = 1; j < variables.length; j++) {
				p.addValue(variables[0], variables[j]);
			}
		}

		//ajout des contraintes
		int nbContraintes = Integer.parseInt(it.next());
		for (int i = nbVariables + 1; i < nbVariables + 1 + nbContraintes; i++) {
			Constraint c = new Constraint(new ArrayList<String>(Arrays.asList(it.next().split(";"))));
			int nbTuple = Integer.parseInt(it.next());
			for (int j = 0; j < nbTuple; j++) {
				c.addTuple(new ArrayList<Object>(Arrays.asList(it.next().split(";"))));
			}
			p.addConstraint(c);
		}

		return p;
	}

	private static CSP parseFromInt(Iterator<String> it) {
		CSP p = new CSP();
		boolean onlyNumerics = true;

		int nbVariables = Integer.parseInt(it.next());
		for (int i = 1; i < nbVariables + 1; i++) {
			String [] variables = it.next().split(";");
			p.addVariable(variables[0]);
			for (int j = 1; j < variables.length; j++) {
				p.addValue(variables[0], variables[j]);
				if(!isNumeric(variables[j]))
					onlyNumerics = false;
			}
		}

		//ajout des contraintes
		int nbContraintes = Integer.parseInt(it.next());
		for (int i = 0; i < nbContraintes; i++) {
			String [] vars = it.next().split(";");
			String type = it.next();
			boolean isEqual = false;

			if(type.equals("E")) {
				isEqual = true;
			}
			else if(type.equals("D")) {
				isEqual = false;
			}

			for (String s1 : vars) {
				for (String s2 : vars) {
					int modifier1 = 0, modifier2 = 0;

					if(onlyNumerics) {
						int sign = Math.max(s1.indexOf("+"), s1.indexOf("-"));
						if(sign >= 0) {
							modifier1 = Integer.valueOf(s1.substring(sign, s1.length()));
							s1 = s1.substring(0, sign);
						}
						sign = Math.max(s2.indexOf("+"), s2.indexOf("-"));
						if(sign >= 0) {
							modifier2 = Integer.valueOf(s2.substring(sign, s2.length()));
							s2 = s2.substring(0, sign);
						}

					}
					if(!s1.equals(s2)) {
						ArrayList<String> a = new ArrayList<String>();
						a.add(s1);
						a.add(s2);
						Constraint c = new Constraint(a);
						for (Object val1 : p.getDom(s1)) {
							for (Object val2 : p.getDom(s2)) {
								if(onlyNumerics) {
									int n1 = Integer.valueOf(val1.toString());
									int n2 = Integer.valueOf(val2.toString());
									if(isEqual) {
										if(n1 - n2 == modifier1 - modifier2) {
											c.addTuple(createTuple(val1, val2));
										}
									}
									if(!isEqual) {
										if(n1 - n2 != modifier1 - modifier2)
										{
											c.addTuple(createTuple(val1, val2));
										}
									}
								}
								else {
									if(isEqual) {
										if(val1.equals(val2)) {
											c.addTuple(createTuple(val1, val2));
										}
									}
									else {
										if(!val1.equals(val2))
										{
											c.addTuple(createTuple(val1, val2));
										}
									}
								}
							}
						}
						p.addConstraint(c);
					}
				}
			}
		}

		return p;
	}

	private static ArrayList<Object> createTuple(Object val1, Object val2) {
		ArrayList<Object> tuple = new ArrayList<Object>();
		tuple.add(val1);
		tuple.add(val2);
		return tuple;
	}

	private static boolean isNumeric(String s) {
		return s.matches("[-+]?\\d*\\.?\\d+");  	
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
				String temp[] = it.next().split("\\(");
				String predicat = temp[0];
				String [] termes = temp[1].substring(0, temp[1].length() - 1).split(",");
				
				k.addFait(predicat, parseAtome(termes));
			}
			
			n = Integer.parseInt(it.next());
			for (int i = 0; i < n; i++) {
				k.addRule(parseRule(it.next()));
			}
			
			return k;
		}
		catch(Exception e)
		{	
			return null;
		}
	}

	private static Rule parseRule(String s) {
		Rule r = new Rule();
		
		String[] atomes = s.split(";");
		for (int i = 0; i < atomes.length; i++) {
			String temp[] = atomes[i].split("\\(");
			String predicat = temp[0];
			String [] termes = temp[1].substring(0, temp[1].length() - 1).split(",");

			if(i == atomes.length - 1) {
				r.setConclusion(predicat, parseAtome(termes));
			} else {
				r.addAtome(predicat, parseAtome(termes));
			}
		}
		
		return r;
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
	
	public static Homomorphisme parseStringHomo(String s) {
		System.out.println("\nhomo string : " + s);
		String[] l = s.split("\n");
		ArrayList<String> list = new ArrayList<String>();
		for (int i = 0; i < l.length; i++) {
			list.add(l[i]);
		}
		Iterator<String> it = list.iterator();
		String type = it.next();
		
		if(!type.equals("H")) {
			return null;
		}
		
		Homomorphisme h = new Homomorphisme();
		
		h.setEnsemble1(createEnsemble(it.next()));
		h.setEnsemble2(createEnsemble(it.next()));
		return h;
	}
	
	private static Ensemble createEnsemble(String s) {
		System.out.println("ensemble : " + s);
		Ensemble e = new Ensemble();	
		
		String[] atomes = s.split(";");
		for (int i = 0; i < atomes.length; i++) {
			String temp[] = atomes[i].split("\\(");
			String predicat = temp[0];
			String [] termes = temp[1].substring(0, temp[1].length() - 1).split(",");

			e.addAtome(predicat, parseAtome(termes));
		}
		
		return e;
	}
}
