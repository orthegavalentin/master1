package affichage;


import java.awt.Color;
import java.awt.Graphics2D;

class Segment {
	PointVisible gauche;
	PointVisible droit;
	Color lineColor;

	//Precondition: f.x < t.x par convention et pour les besoins de l'algorithme de balayage gauche droite
	Segment(PointVisible f, PointVisible t) {
		gauche = f;
		droit = t;
		lineColor =  Couleur.nw;
		gauche.segment = this;
		droit.segment = this;
	}

	public void dessine(Graphics2D g) {
		g.setColor(lineColor);
		g.drawLine((int) gauche.x , (int) gauche.y , (int) droit.x, (int) droit.y);
	}
}
