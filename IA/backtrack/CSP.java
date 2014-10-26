
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

// Choix de codage 
//		Variable = String
//      Valeur = Object
//		un domaine = TreeSet<Object>
//		les couples (variable, domaine) = HashMap<String,TreeSet<Object>>
//		les contraintes = ArrayList<Constraint>

public class CSP {
	
	private HashMap<String,TreeSet<Object>> varDom; // table de hachage associant � chaque variable son domaine
	private ArrayList<Constraint> constraints; // liste des contraintes
	
	// initialise un CSP avec des structures vides
	public CSP() {
		varDom = new HashMap<String,TreeSet<Object>>();
		constraints = new ArrayList<Constraint>();
	}

	// initialise un CSP � partir d'un fichier texte
//	public CSP(String fileName) {
//		this();
//		try {
//			ArrayList<String> l = (ArrayList<String>) Files.readAllLines(Paths.get(fileName), StandardCharsets.UTF_8);
//			Iterator<String> it = l.iterator();
//			System.out.println(it.next());
//			//			for (String s : l) {
////				System.out.println(s);
////			}
//			//ajout des variables + domaine
//			int nbVariables = Integer.parseInt(it.next());
//			System.out.println("nbvar : " + nbVariables);
//			for (int i = 1; i < nbVariables + 1; i++) {
//				String [] variables = it.next().split(";");
//				addVariable(variables[0]);
//				for (int j = 1; j < variables.length; j++) {
//					addValue(variables[0], variables[j]);
//				}
//			}
//			
//			//ajout des contraintes
//			int nbContraintes = Integer.parseInt(it.next());
//			for (int i = nbVariables + 1; i < nbVariables + 1 + nbContraintes; i++) {
//				Constraint c = new Constraint(new ArrayList<String>(Arrays.asList(it.next().split(";"))));
//				int nbTuple = Integer.parseInt(it.next());
//				for (int j = 0; j < nbTuple; j++) {
//					c.addTuple(new ArrayList<Object>(Arrays.asList(it.next().split(";"))));
//				}
//				addConstraint(c);
//			}
//			
//		} catch (Exception e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//	}
	
	// ajoute une variable
	public void addVariable(String var) {
		if(varDom.get(var)==null) varDom.put(var, new TreeSet<Object>());
		else System.err.println("Variable " + var + " deja existante");
	}

	// ajoute une valeur au domaine d'une variable
	public void addValue(String var, Object val) {
		if(varDom.get(var)==null) System.err.println("Variable " + var + " non existante");
		else {
			TreeSet<Object> dom = varDom.get(var);
			if (!dom.add(val)) /*varDom.put(var, dom);
			else */System.err.println("La valeur " + val + " est deja dans le domaine de la variable " + var); 
		}
	}
	
	// ajoute une contrainte
	public void addConstraint(Constraint c) {		
		// on ne verifie pas que les valeurs des contraintes sont "compatibles" avec les domaines
		if(!varDom.keySet().containsAll(c.getVariables())) System.err.println("La contrainte "+ c.getName() + " contient des variables ("+ c.getVariables() +") non declarees dans le CSP dont les variables sont " + varDom.keySet());
		else constraints.add(c);
	}
	
	public int getVarNumber() {
		return varDom.size();
	}

	public int getDomSize(String var) {
		return varDom.values().size();
	}
	
	public int getConstraintNumber(){
		return constraints.size();
	}
	
	public Set<String> getVars() {
		return varDom.keySet();
	}

	public TreeSet<Object> getDom(String var) {
		return varDom.get(var);
	}
	
	public HashMap<String,TreeSet<Object>> getDom() {
		return varDom;
	}

	public ArrayList<Constraint> getConstraints() {
		return constraints;
	}
	
	// retourne l'ensemble des contraintes contenant la variable pass�e en param�tre
	public ArrayList<Constraint> getConstraintsContaining(String var) {
		ArrayList<Constraint> selected = new ArrayList<Constraint>();
		for(Constraint c : constraints) {
			if(c.getVariables().contains(var)) selected.add(c);
		}
		return selected;
	}
		
	public String toString() {
		return "Var et Dom : " + varDom + "\nConstraints :" + constraints;
	}
	
//	public static void main(String[] args){
//		CSP monCSP = new CSP();
//		// les variables
//		String v1 = new String("x"); // la variable v1 a pour nom x
//		String v2 = new String("y");
//		String v3 = new String("z");
//		monCSP.addVariable(v1); // ajout de la variable v1 au CSP
//		monCSP.addVariable(v2);
//		monCSP.addVariable(v3);
//		monCSP.addVariable("x");
//		// les domaines
//		monCSP.addValue(v1,1); // ajout de la valeur 1 aud omaine de v1
//		monCSP.addValue(v1,2);
//		monCSP.addValue(v1,3);
//		monCSP.addValue(v2,"as");
//		monCSP.addValue(v2,"tutu");
//		monCSP.addValue(v3,2);
//		monCSP.addValue(v3,4);
//		monCSP.addValue(v3,6);
//		monCSP.addValue(v3,0);
//		monCSP.addValue(v3,2);
//		// les contraintes
//		ArrayList<String> varTuple;
//		ArrayList<Object> valTuple;
//		// c1 : <x,y> : <2,"if"> <2,"as">,<4,"tutu">
//		varTuple= new ArrayList<String>(2);
//		varTuple.add(0,"x") ;
//		varTuple.add(1,"y") ;
//		Constraint c1 = new Constraint(varTuple);
//		valTuple = new ArrayList<Object>(2);
//		valTuple.add(0,2);
//		valTuple.add(1,"if");
//		c1.addTuple(valTuple);
//		valTuple = new ArrayList<Object>(2);
//		valTuple.add(0,2);
//		valTuple.add(1,"as");
//		c1.addTuple(valTuple);
//		valTuple = new ArrayList<Object>(2);
//		valTuple.add(0,4);
//		valTuple.add(1,"tutu");
//		c1.addTuple(valTuple);
//		monCSP.addConstraint(c1);  
//
//		// c2 : <y,x,z> : <"as",1,3> <"toto",3,5>
//		varTuple= new ArrayList<String>(3);
//		varTuple.add(0,"y") ;
//		varTuple.add(1,"x") ;
//		varTuple.add(2,"z") ;
//		Constraint c2 = new Constraint(varTuple);
//		valTuple = new ArrayList<Object>(3);
//		valTuple.add(0,"as");
//		valTuple.add(1,1);
//		valTuple.add(2,3);
//		c2.addTuple(valTuple);
//		valTuple = new ArrayList<Object>(3);
//		valTuple.add(0,"toto");
//		valTuple.add(1,3);
//		valTuple.add(2,5);
//		c2.addTuple(valTuple);
//		valTuple = new ArrayList<Object>(2);
//		valTuple.add(0,4);
//		valTuple.add(1,"tutu");
//		c2.addTuple(valTuple);
//		valTuple = new ArrayList<Object>(3);
//		valTuple.add(0,"as");
//		valTuple.add(1,1);
//		valTuple.add(2,3);
//		c2.addTuple(valTuple);
//		monCSP.addConstraint(c2);
//		
//		//c3 : <w> : <1> <2>
//		varTuple= new ArrayList<String>(1);
//		varTuple.add(0,"w") ;
//		Constraint c3 = new Constraint(varTuple);
//		valTuple = new ArrayList<Object>(1);
//		valTuple.add(0,1);
//		c3.addTuple(valTuple);
//		valTuple = new ArrayList<Object>(1);
//		valTuple.add(0,2);
//		c3.addTuple(valTuple);
//		monCSP.addConstraint(c3);
//
//		System.out.println("\nMon CSP " + monCSP);
//	}
	
}


