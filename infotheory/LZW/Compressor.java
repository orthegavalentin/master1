package lzw;

import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;

public class Compressor {
	private static String w;
	private static ArrayList<String> dico;
	private static String result;
	private static final int ENCODING_LENGTH = 12;
	
	public static void compress (String fileName, String outputFile) throws Exception
	{
		FileOutputStream out = new FileOutputStream(outputFile);
		
		initDico();
		w = "";
		result = "";
		String temp;
		char c;
		byte [] l = Files.readAllBytes(Paths.get(fileName));
		for (int i = 0; i < l.length; i++) {
			c = (char) l[i];
			
			temp = w + c;
			if(dico.contains(temp))
			{
				w = temp;
			}
			else
			{
				dico.add(temp);
				int index = dico.indexOf(w);
				result += complete(ENCODING_LENGTH, Integer.toBinaryString(index));
				w = "" + c;
			}
		}
		writeResult(out);
		out.close();
		
	}
	
	private static String complete(int encodingLength, String binaryCode) throws Exception
	{
		String s = "";
		
		if(binaryCode.length() > encodingLength)
		{
			System.out.println(binaryCode);
			throw new Exception();
		}
		
		int toAdd = encodingLength - binaryCode.length();
		
		for (int i = 0; i < toAdd; i++) {
			s += "0";
		}
		
		s += binaryCode;
		
		return s;
	}
	
	private static void initDico()
	{
		dico = new ArrayList<String>();
		for (int i = 0; i < 256; i++) {
			dico.add("" + (char) i);
		}
	}
	
	private static void writeResult(FileOutputStream out) throws IOException {
		int [] chars = new int [result.length() / 8 + 1];
		for (int i = 0; i < result.length() / 8; i++) {
			chars[i] = Integer.parseInt(result.substring(i * 8, i * 8 + 8), 2);
			chars[i] -= 127;
		}
		for (int i = 0; i < chars.length; i++) {
			out.write(chars[i]);
			chars[i] += 127;
		}
		System.out.println(Arrays.toString(chars));
	}
}
