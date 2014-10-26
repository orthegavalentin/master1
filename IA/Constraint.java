
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;


public class Constraint {
	
	private static int num=0; //pour donner un num�ro unique � chaque contrainte
	private String name; // nom de la contrainte
	private ArrayList<String> varTuple; // ensemble ordonn� de variables
	private Set<ArrayList<Object>> valTuples; // ensemble de tuples de la contrainte
	
	public Constraint(ArrayList<String> var) {
		num++;
		this.name = "C"+num;
		varTuple = var; 
		valTuples = new HashSet<ArrayList<Object>>();
	}
	
	public Constraint(ArrayList<String> var, String name) {
		num++;
		this.name = name;
		varTuple = var; 
		valTuples = new HashSet<ArrayList<Object>>();
	}
	
	public int getArity() {
		return varTuple.size();
	}
	
	public Set<ArrayList<Object>> getContraintes() {
		return valTuples;
	}
	
	public String getName() {
		return name;
	}
	public ArrayList<String> getVariables() {
		return varTuple;
	}
	
	public void addTuple(ArrayList<Object> valTuple) {
		if(valTuple.size() != varTuple.size()) System.err.println("Le tuple " + valTuple + " n'a pas l'arite " + varTuple.size() + " de la contrainte " + name);
		else if(!valTuples.add(valTuple)) System.err.println("Le tuple " + valTuple + " est deja present dans la contrainte "+ name);
	}
	
	
	public String toString() {
		return "\n\t"+ name + " = " + varTuple + " : " + valTuples; 
	}


}
