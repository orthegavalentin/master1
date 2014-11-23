package lzw;

import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;

public class Decompressor {

	private static ArrayList<String> dico = new ArrayList<String>();
	private static int ENCODING_LENGTH;

	public static void decompress(String inputFile, String outputFile) throws Exception
	{
		Utils.initDico(dico);
		String result = "";
		int prevcode, currcode, ch;
		String e = "";
		byte [] l = Files.readAllBytes(Paths.get(inputFile));
		ENCODING_LENGTH = l[0] + 127;
		System.out.println("encoding length : " + ENCODING_LENGTH);
		int [] chars = decode(l);


		prevcode = chars[0];
		//		String result = "" + prevcode;
		for(int i = 1; i < chars.length; i++) {
			currcode = chars[i];
			if(dico.size() >= Math.pow(2, ENCODING_LENGTH)) {
				dico.clear();
				Utils.initDico(dico);
			}
			if(currcode >= dico.size())
			{
				e ="" +  e.charAt(0);
			}
			else
			{
				e = dico.get((int)currcode);
			}
			//			result += "A";
			//			result = new String(result).concat("auie");
			result += e;
			//			result = result.concat("e");
			ch = e.charAt(0);
			dico.add(dico.get((int) prevcode) + (char) ch);
			prevcode = currcode;
		}

		//		result = new String(result.getBytes(), Charset.forName("UTF-8"));
		System.out.println(result);

		Writer out = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outputFile)));
		out.write(result);
		out.close();
	}

	private static int [] decode(byte[] b) throws Exception
	{


		String s = "";
		//skip du premier octet (taille de l'encodage)
		for (int i = 1; i < b.length; i++) {
			int a = b[i] + 127;
			if(a == -1)
			{
				a = 255;
			}
			s += Utils.complete(8, Integer.toBinaryString(a));
		}
		//		System.out.println(s.length());
		//		System.out.println(ENCODING_LENGHT);

		int [] n = new int [s.length() / ENCODING_LENGTH]; 
		//		System.out.println(Utils.complete(8, Integer.toBinaryString(ENCODING_LENGHT)) + s);

		for (int i = 0; i < s.length() / ENCODING_LENGTH; i++) {
			n[i] = Integer.parseInt(s.substring(i * ENCODING_LENGTH, i * ENCODING_LENGTH + ENCODING_LENGTH), 2);
		}

		System.out.println(Arrays.toString(n));
		return n;
	}
}
