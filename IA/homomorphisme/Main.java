import java.io.FileNotFoundException;
import java.io.UnsupportedEncodingException;


public class Main {

	public static void main(String[] args) {
		String fileName = "homo1.txt";
		try {    
			fileName = new java.io.File( "." ).getCanonicalPath()+"/"+fileName;
			System.out.println("Chargement du fichier : "+fileName);
		}catch(Exception e) {
	     System.err.println("Erreur lors du chargement du fichier " + fileName);
			System.err.println(e);
			return;
		}
		
		Homomorphisme h = ParserHomo.parse(fileName);
		
		fileName = "homoexport.txt";
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
		//HashMap<String,Object> mySolution = mySolver.searchSolution();
		System.out.println(mySolver.searchAllSolutions());
	}

}
