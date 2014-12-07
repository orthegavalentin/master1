import java.io.FileNotFoundException;
import java.io.UnsupportedEncodingException;



public class Main {

	public static void main(String[] args) {
		String fileName = "dep.txt";
//		try {    
//			fileName = new java.io.File( "." ).getCanonicalPath()+"/"+fileName;
//			System.out.println("Chargement du fichier : "+fileName);
//		}catch(Exception e) {
//	     System.err.println("Erreur lors du chargement du fichier " + fileName);
//			System.err.println(e);
//			return;
//		}
		
		KnowlegdeBase k = Parser.parseBc(fileName);
		k.sature();
		
//		Homomorphisme h = Parser.parseHomo(fileName);
//		CSP csp = h.toCSP();
	}

}
