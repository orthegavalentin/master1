package lzw;

import java.io.FileOutputStream;
import java.io.IOException;

public class Main {

	public static void main(String[] args) {
		char a = 'Ü';
		char c = '\n';
		System.out.println((int)c);
		// TODO Auto-generated method stub
		
//		try {
//			FileOutputStream out = new FileOutputStream("/home/noe/Téléchargements/test.txt");
//			for (int i = 0; i < 2555; i++) {
//				String s = " " + i;
//				out.write(s.getBytes());
//			}	
//			out.close();
//		} catch (IOException e1) {
//			// TODO Auto-generated catch block
//			e1.printStackTrace();
//		}
		try {
			Compressor.compress("/home/noe/Téléchargements/test.txt", "/home/noe/Téléchargements/compjava");
			System.out.println("compressed!");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			Decompressor.decompress("/home/noe/Téléchargements/compjava", "/home/noe/Téléchargements/outjava.txt");
			System.out.println("decompressed!");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
