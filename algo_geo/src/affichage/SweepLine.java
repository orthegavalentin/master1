package affichage;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Stroke;
import java.util.ArrayList;


public class SweepLine {
	Color sweepLineColor = Couleur.tb;
	int width, height;
	int pos, step, maxStep, stepWidth;
	
	ArrayList<Segment> status; // la liste des segments qui croisent la ligne de balayage
	ArrayList<PointVisible> eventPoints = new ArrayList<PointVisible>(); // la liste des points générant des évènements (ie chgt de la sweepline
	Vue vue; // la vue qui contient les segments à étudier
	
	public SweepLine(int n, int w, int h, Vue v){
		status = new ArrayList<Segment>();
		width = w;
		height = h;
		pos = 0;
		vue = v;
		stepWidth = w/100;
		step = 0;
		maxStep = w /stepWidth;
	}
	
	public void dessine(Graphics2D g) {
		g.setColor(sweepLineColor);
		Stroke s = g.getStroke();
		g.setStroke(new BasicStroke(2));
		g.drawLine(pos,0,pos,height);
		g.setStroke(s);
	}

	// déplacement de la ligne de balayage	
	public void next() {
		step = step < maxStep ? step + 1 : 0;

		if (eventPoints.size() > 0) {
				//todo
			} else {
				pos = step * stepWidth;
		}
	}
	
	private void remove(Segment segment) {
		status.remove(segment);
	}
	
	// calcul déterminant
	public double determinant(Segment s0, Segment s1){
		return (s0.droit.x - s0.gauche.x) * (s1.droit.y - s1.gauche.y) - (s1.droit.x - s1.gauche.x) * (s0.droit.y - s0.gauche.y);
	}

}
