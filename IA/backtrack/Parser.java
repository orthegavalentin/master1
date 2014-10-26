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

	private static CSP parseFromExt(Iterator<String> it)
	{
		CSP p = new CSP();

		int nbVariables = Integer.parseInt(it.next());
		System.out.println("nbvar : " + nbVariables);
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

		int nbVariables = Integer.parseInt(it.next());
		System.out.println("nbvar : " + nbVariables);
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
			String [] vars = it.next().split(";");
			String type = it.next();
			boolean isEqual = false;

			if(type.equals("E"))
			{
				isEqual = true;
			}
			else if(type.equals("D"))
			{
				isEqual = false;
			}

			Constraint c = new Constraint(new ArrayList<String>(Arrays.asList(vars)));
			
			for (Object val1 : p.getDom(vars[0])) {
				for (Object val2 : p.getDom(vars[1])) {
					if(isEqual)
					{
						if(val1.equals(val2))
						{
							c.addTuple(createTuple(val1, val2));
						}
					}
					else
					{
						if(!val1.equals(val2))
						{
							c.addTuple(createTuple(val1, val2));
						}
					}
				}
			}
			p.addConstraint(c);
		}

		return p;
	}
	
	private static ArrayList<Object> createTuple(Object val1, Object val2)
	{
		ArrayList<Object> tuple = new ArrayList<Object>();
		tuple.add(val1);
		tuple.add(val2);
		return tuple;
	}
}
