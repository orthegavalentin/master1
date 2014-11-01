package lzw;

import java.util.ArrayList;
import java.util.HashMap;

public class Utils {
	
	public static void initDico(ArrayList<String> dico)
	{
		for (int i = 0; i < 256; i++) {
			dico.add("" + (char) i);
		}
	}
	
	public static void initDicoBis(HashMap<Long, Long> dico)
	{
		for (long i = 0; i < 256; i++) {
			dico.put(i, i);
		}
	}
	
	public static long pair(long x, long y)
	{
		return ((x + y) * (x + y + 1)) / 2 + y;
	}
	
	public static String complete(int encodingLength, String binaryCode)
	{
		String s = "";
		
		if(binaryCode.length() > encodingLength)
		{
			System.out.println(binaryCode);
		}
		
		int toAdd = encodingLength - binaryCode.length();
		
		for (int i = 0; i < toAdd; i++) {
			s += "0";
		}
		
		s += binaryCode;
		return s;
	}
}
