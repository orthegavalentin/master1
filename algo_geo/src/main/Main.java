package main;
import javax.swing.JFrame;
import affichage.Vue;

public class Main {
	
	public static void main(String s[]) {
		int w = 500, h= 500;
		JFrame frame = new JFrame("Gestionnaire de fichiers");
		Vue v = new Vue(10,w,h);
		frame.add(v);
		frame.pack();
		frame.setVisible(true);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}
