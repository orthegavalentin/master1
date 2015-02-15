                                                                                                                    

import java.util.HashMap;

// exemple de main pour le test de l'algorithme de backtrack

public class TP {

	public static void main(String args[]) {
		//Lire un CSP depuis un fichier
		String fileName = "out.txt";
		CSP myProblem;
		try {    
			fileName = new java.io.File( "." ).getCanonicalPath()+"/"+fileName;
			System.out.println("Chargement du fichier : "+fileName);
		}catch(Exception e) {
	     System.err.println("Erreur lors du chargement du fichier " + fileName);
			System.err.println(e);
			return;
		}
		myProblem = Parser.parse(fileName);
		System.out.println("\nRecherche d'une solution au probleme :\n" + myProblem);
		Solver mySolver = new Solver(myProblem);
		HashMap<String,Object> mySolution = mySolver.searchSolution();
		System.out.println(mySolution);
		//System.out.println(mySolver.searchAllSolutions());
		//if (mySolution == null) System.out.println("Pas de solution !");
		//else System.out.println("Une solution est " + mySolution);
	}
}

