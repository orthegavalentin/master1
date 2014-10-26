                                                                                                                    

import java.util.HashMap;

// exemple de main pour le test de l'algorithme de backtrack

public class TP {

	public static void main(String args[]) {
		//Lire un CSP depuis un fichier
		String fileName = "triangleInt.txt";
		CSP myProblem;
		try {    
			fileName = new java.io.File( "." ).getCanonicalPath()+"/"+fileName;
			System.out.println("Chargement du fichier : "+fileName);
			myProblem = Parser.parse(fileName);
		}catch(Exception e) {
	     System.err.println("Erreur lors du chargement du fichier " + fileName);
			System.err.println(e);
			return;
		}
		System.out.println("\nRecherche d'une solution au probleme :\n" + myProblem);
		Solver mySolver = new Solver(myProblem);
		HashMap<String,Object> mySolution = mySolver.searchSolution();
		if (mySolution == null) System.out.println("Pas de solution !");
		else System.out.println("Une solution est " + mySolution);
	}
}

