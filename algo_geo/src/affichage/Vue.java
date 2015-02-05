package affichage;
import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.util.ArrayList;

public class Vue extends JPanel implements MouseWheelListener, MouseListener{
	Color bgColor = Couleur.bg; // la couleur de fond de la fenêtre
	Color fgColor = Couleur.fg; // la couleur des lignes
	int width, height;
	ArrayList<Segment> segments = new ArrayList<Segment>();
	SweepLine sweepLine;	

	// n : le nombre de lignes
	// width, height : largeur, hauteur de la fenêtre
	public Vue(int n, int width, int height) {
		setBackground(bgColor);
		this.width = width;
		this.height = height;
		setPreferredSize(new Dimension(width, height));
		sweepLine = new SweepLine(n, width, height, this);
		addMouseListener(this);
		addMouseWheelListener(this);
	}
	
	// initialisation random 
	public void init(int n){
		//à compléter
	}
	
	// methode utilitaire 
	// retourne un entier compris entre xmin et xmax
	int random(int xmin,int xmax){
		// à modifier
		return 0;
	}
		
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		Graphics2D g2d = (Graphics2D) g;
		g2d.setPaintMode(); 
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,	RenderingHints.VALUE_ANTIALIAS_ON);	

		g2d.setColor(fgColor);
		
		for (Segment lg: segments) {
			lg.dessine(g2d);
		}
		sweepLine.dessine(g2d);
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		int n = segments.size();
		if (e.getClickCount() == 2){
				// à compléter
		}
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
	}

	@Override
	public void mouseExited(MouseEvent arg0) {
	}

	@Override
	public void mousePressed(MouseEvent arg0) {
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
	}
	
	@Override
	public void mouseWheelMoved(MouseWheelEvent e) {
		int scrollUnit = e.getWheelRotation();
		if (scrollUnit > 0)
			sweepLine.next();
		repaint();
	}

}
	

