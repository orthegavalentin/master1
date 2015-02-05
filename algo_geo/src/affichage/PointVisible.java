package affichage;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Rectangle;


public class PointVisible extends Rectangle{
	public static int midWidth = 5;
	Color color = Couleur.nw;
	role role ;
	public Segment segment;

	public PointVisible(int x, int y, role r) {
		super(x,y, 2 * PointVisible.midWidth,2 * PointVisible.midWidth);
		this.role = r;
		switch(role){
		case begin: 
			color = Couleur.beginPoint;
			break;
		case intersect: // blanc
			color = Couleur.intersection;
			break;
		case end: //rouge
			color = Couleur.endPoint;
			break;
		}
	}

	public void dessine(Graphics2D g2d) {
		g2d.setColor(color);
		g2d.fill(this);	
	}

	public void print() {
		System.out.println("x = " + x + " y = " + y+" w = " + width + " h = " + height + " role = "+role);
	}	

}

