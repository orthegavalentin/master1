
public class Main {

	public static void main(String[] args) {
		String fileName = "homo.txt";
		try {    
			fileName = new java.io.File( "." ).getCanonicalPath()+"/"+fileName;
			System.out.println("Chargement du fichier : "+fileName);
		}catch(Exception e) {
	     System.err.println("Erreur lors du chargement du fichier " + fileName);
			System.err.println(e);
			return;
		}
		
		Homomorphisme h = Parser.parse(fileName);
		h.export();
	}

}
