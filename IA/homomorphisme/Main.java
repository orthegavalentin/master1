import java.io.FileNotFoundException;
import java.io.UnsupportedEncodingException;


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
		
		Homomorphisme h = ParserHomo.parse(fileName);
		try {
			h.export();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
