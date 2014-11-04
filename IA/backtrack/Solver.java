
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;


public class Solver {

	public CSP problem; // l'instance de CSP                 
	private HashMap<String,Object> assignation; // codage d'une solution partielle ou totale
	private HashSet<HashMap<String,Object>> solutions;

	public Solver(CSP p) {
		problem = p;
		assignation = new HashMap<String,Object>(); 
		solutions = new HashSet<HashMap<String,Object>>();
	}

	// retourne une solution s'il en existe une, null sinon           
	public HashMap<String,Object> searchSolution() { 
		searchAllSolutions();
		System.out.println(solutions);
		System.out.println(solutions.size());
		//		return backtrack();
		return null;
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
		for (Object val : tri(problem.getDom(s))) {
			assignation.put(s, val);
			if(areAllConstraintsValid(assignation))
			{
				HashMap<String,Object> temp = backtrack();
				if(temp != null && temp.size() == problem.getVarNumber())
				{
					System.out.println("sélectionné : " + s + "=" + val);
					return temp;
				}
			}
			else
			{
				System.out.println("impossible avec : " + s + "=" + val);
				assignation.remove(s);
			}
		}
		return null;
	}

	// choix d'une variable
	private String chooseVar(Set<String> allVar, Set<String> assignedVar) {
		for (String string : allVar) {
			if(!assignedVar.contains(string)) {
				return string;
			}
		}
		return null;
	}


	private TreeSet<Object> tri(TreeSet<Object> values) {
		return values;
	}


	// retourne l'ensemble des solutions
	public HashSet<HashMap<String, Object>> searchAllSolutions() {

		if (this.assignation.size() == this.problem.getVarNumber()) {
			this.solutions.add((HashMap<String, Object>) this.assignation.clone());
			return this.solutions;
		}
		
		String s = this.chooseVar(this.problem.getVars(), this.assignation.keySet());
		
		for (Object val : tri(problem.getDom(s))) {
			this.assignation.put(s, val);
			if(areAllConstraintsValid(assignation)) { // Si contrainte validée
				this.searchAllSolutions();
			}
			this.assignation.remove(s);
		}
		
		return this.solutions;
	}
}

