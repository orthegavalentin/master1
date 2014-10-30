package lzw;

import java.io.IOException;

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			Compressor.compress("/home/noe/Téléchargements/test.txt", "/home/noe/Téléchargements/comp");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (Exception e) {
			System.err.println("Dico too long");
		}
		try {
			Decompressor.decompress("/home/noe/Téléchargements/comp", "/home/noe/Téléchargements/out.txt");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
