package lzw;

import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;

public class Decompressor {

	private static String result;
	private static ArrayList<String> dico;
	private static final int ENCODING_LENGHT = 12;
	
	public static void decompress(String inputFile, String outputFile) throws IOException
	{

		initDico();
		result = "";
		char prevcode, currcode, ch;
		String e = "";
		byte [] l = Files.readAllBytes(Paths.get(inputFile));
		int [] chars = decode(l);
		
		prevcode = (char) chars[0];
		result += "" + prevcode;
		for(int i = 1; i < chars.length; i++) {
			currcode = (char) chars[i];
			if(currcode >= dico.size())
			{
				e ="" +  e.charAt(0);
			}
			else
			{
				e = dico.get((int)currcode);
			}
			result += e;
			ch = e.charAt(0);
			dico.add(dico.get((int) prevcode) + ch);
			prevcode = currcode;
		}
		
		
		PrintWriter out = new PrintWriter(outputFile);
		out.println(result);
		out.flush();
		out.close();
		System.out.println(result);
	}
	private static void initDico()
	{
		dico = new ArrayList<String>();
		for (int i = 0; i < 256; i++) {
			dico.add("" + (char) i);
		}
	}
	
	private static int [] decode(byte[] b)
	{
		int [] n = new int [b.length * 8 / ENCODING_LENGHT]; 
		
		String s = "";
		
		for (int i = 0; i < b.length; i++) {
			int a = b[i] + 127;
			s += complete(8, Integer.toBinaryString(a));
		}
		
		for (int i = 0; i < n.length; i++) {
			n[i] = Integer.parseInt(s.substring(i * ENCODING_LENGHT, i * ENCODING_LENGHT + ENCODING_LENGHT), 2);
		}
		
		System.out.println(s);
		System.out.println(Arrays.toString(n));
		return n;
	}
	
	private static String complete(int encodingLength, String binaryCode)
	{
		String s = "";
		
		int toAdd = encodingLength - binaryCode.length();
		
		for (int i = 0; i < toAdd; i++) {
			s += "0";
		}
		
		s += binaryCode;
		return s;
	}
	
}
