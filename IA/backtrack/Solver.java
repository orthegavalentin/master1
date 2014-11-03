
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

import org.omg.CORBA.OBJ_ADAPTER;


public class Solver {

	public CSP problem; // l'instance de CSP                 
	private HashMap<String,Object> assignation; // codage d'une solution partielle ou totale
	private HashSet<HashMap<String,Object>> allSolutions;

	public Solver(CSP p) {
		problem = p;
		assignation = new HashMap<String,Object>(); 
		allSolutions = new HashSet<HashMap<String,Object>>();
	}

	// retourne une solution s'il en existe une, null sinon           
	public HashMap<String,Object> searchSolution() { 
//		System.out.println("all solutions : " + searchAllSolutions());
		return backtrack();
	}

	private boolean isConstraintValid(Constraint c, HashMap<String,Object> a) {
		ArrayList<String> vars = new ArrayList<String>();
		for (String var : a.keySet()) {
			if(c.getVariables().contains(var))
			{
				vars.add(var);
			}
		}
		boolean ok = true;
		for(ArrayList<Object> tuple : c.getContraintes()) {
			ok = true;
			while(ok)
			{
				for (String string : vars) {
//					System.out.println("trying : " + tuple.get(c.getVariables().indexOf(string)).toString() + " with : " + a.get(string).toString() + " : " + tuple.get(c.getVariables().indexOf(string)).toString().equals(a.get(string).toString()));
					if(!tuple.get(c.getVariables().indexOf(string)).toString().equals(a.get(string).toString()))
					{
						ok = false;
						break;
					}
				}
				if(ok)
					return ok;
			}
		}

		return ok;
	}

	private boolean areAllConstraintsValid(HashMap<String,Object> a) {
		for (Constraint c : problem.getConstraints()) {
			if(!isConstraintValid(c, a)) {
				return false;
			}
		}
		return true;
	}

	// l'algo récursif
	private HashMap<String,Object> backtrack() {
		if (this.assignation.size() == problem.getVarNumber())
		{
			return assignation;
		}
		String s = this.chooseVar(problem.getVars(), assignation.keySet());
		for (Object val : problem.getDom(s)) {
			assignation.put(s, val);
			if(areAllConstraintsValid(assignation))
			{
				HashMap<String,Object> temp = backtrack();
				if(temp != null && temp.size() == problem.getVarNumber())
				{
//					System.out.println("sélectionné : " + s + "=" + val);
					return temp;
				}
			}
			else
			{
//				System.out.println("impossible avec : " + s + "=" + val);
				assignation.remove(s);
			}
		}
		return null;
	}

	// choix d'une variable
	private String chooseVar(Set<String> allVar, Set<String> assignedVar) {
		for (String string : allVar) {
			if(!assignedVar.contains(string)) {
				System.out.println("chose : " + string);
				return string;
			}
		}
		return null;
	}


	private TreeSet<Object> tri(TreeSet<Object> values) {
		return values;
	}


	// retourne l'ensemble des solutions
	public HashSet<HashMap<String,Object>> searchAllSolutions() {
		return allSolutions;
	}
}

