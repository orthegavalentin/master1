package lzw;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;

public class Compressor {
	private static String w;
	//	private static ArrayList<Long> dico = new ArrayList<Long>();
	private static HashMap<String, Long> dico = new HashMap<String, Long>();
	private static String result;
	private static final int ENCODING_LENGTH = 15;
	private static long index = 256;

	public static void compress (String inputFile, String outputFile)
	{
		FileOutputStream out = null;
		try {
			out = new FileOutputStream(outputFile);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		InputStreamReader in = null;
		try {
			in = new InputStreamReader(new FileInputStream(inputFile));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println(in.getEncoding());
		Utils.initDicoBis(dico);
		w = "";
		result = "";
		String temp = "";
		int c;
		boolean bool = true;
		try {
			while(bool) {
				if((c = in.read()) == -1)
				{
					c = '#';
					bool = false;
				}
				System.out.println(c);
//				System.out.println(c);
				//temp = Utils.pair(w, c);
				temp = w + ""+c;
				if(dico.containsKey(temp))
				{
					w = temp;
				}
				else
				{
					dico.put(temp, index);
					index++;
					result += Utils.complete(ENCODING_LENGTH, Long.toBinaryString(dico.get(w)));
					w = ""+c;
				}
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		result += Utils.complete(ENCODING_LENGTH, Long.toBinaryString(dico.get(w)));

		//		result = result.substring(0, result.length() - ENCODING_LENGTH);
		//		result += Utils.complete(ENCODING_LENGTH, Integer.toBinaryString(dico.get(temp)));

		String encodingLength = Utils.complete(8, Integer.toBinaryString(ENCODING_LENGTH));
		result = encodingLength + result;
		try {
			writeResult(out);
			out.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			in.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

	private static void writeResult(FileOutputStream out) throws IOException {
		int n = result.length() % 8;
		//		if(n != 0)
		//		{
		//			String s1 = result.substring(0, result.length() - n - 1);
		//			String s2 = result.substring(result.length() - n - 1, result.length() - 1);
		//			
		//			for (int i = 0; i < 8 - n + 1; i++) {
		//				s1 += "0";
		//			}
		//			result = s1 + s2;
		//		}
		//		result = result.substring(0, result.length() - n);

		int [] chars = new int [(result.length() - 8 - n) / 8];
		for (int i = 0; i < (result.length() - 8 - n) / 8; i++) {
			chars[i] = Integer.parseInt(result.substring(i * 8, i * 8 + 8), 2);
			chars[i] -= 127;
		}
		for (int i = 0; i < chars.length; i++) {
			out.write(chars[i]);
		}
		//		System.out.println(chars.length);
		//		System.out.println(result);
		char a = -78+127;
	}
}
