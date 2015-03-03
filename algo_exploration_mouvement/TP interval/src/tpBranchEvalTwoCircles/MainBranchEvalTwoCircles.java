
package tpBranchEvalTwoCircles;

import util.Box;
import util.Interval;

public class MainBranchEvalTwoCircles{

	public static void main(String[] args) {
	   
	    double EPS = 1e-4; 
		
	    Box x0 = new Box(2,new Interval(-3,3));
		
	    // =======================================
	
	    CircleEquation[] ctrs = new CircleEquation[2];

	    ctrs[0] = new CircleEquation(0, 0, 1); // circle centered in (0,0) of radius 1
	    ctrs[1] = new CircleEquation(2, 1, 2.5); // circle centered in (2,1) of radius 2.5

	    // Funny : when there is a single real solution :
	    // ctrs[0] = new CircleEquation(0, 0, 1); 
	    // ctrs[1] = new CircleEquation(2, 0, 1); 
	    
	    BranchEval csp=new BranchEval(ctrs);
				
	    System.out.println("Initial box:" + x0);

	    boolean found = csp.solve(x0, EPS);
		
	    System.out.println("Found = " + found);
	}
}
