
package tpBranchEvalTwoCircles;

import java.util.ArrayList;
import java.util.Stack;

import util.Box;
import util.Constraint;
import util.Pair;

public class BranchEval {

//	Constraint[] ctrs;     // list of constraints
	ArrayList<Constraint> ctrs;

	Box[] solutions;       // list of solutions

	int numSolutions;      // number of solutions found

	public BranchEval(Constraint[] _ctrs) {
		ctrs = new ArrayList<Constraint>();
		for (int i = 0; i < _ctrs.length; i++) {
			ctrs.add(_ctrs[i]);
		}
		this.solutions = new Box[1000];
		this.numSolutions = 0;
	}

	public boolean solve(Box x0, double eps) {

		this.numSolutions = 0;

		int N=x0.dim();

		Stack<Box> s = new Stack<Box>();

		s.push(x0);
		int count = 0; // number of branchings

		while (!s.empty()) {
			Box x=s.pop();
			
//			(apply and (map (lambda (i) (i.violated)))
					
			if(ctrs.stream()
                    .filter(w -> w.violated(x))
                    .count() == 0) {
				if(!x.isEmpty() && x.maxDiam() < eps) {
					solutions[numSolutions++] = x;
				} else {
					Pair<Box, Box> p = x.bisect();
					s.push(p.fst);
					s.push(p.snd);
				}
			}
			count++;
		}

		System.out.println("Number of potential solutions = " + numSolutions + 
				" found with " + count + " branchings !");     
		System.out.print("List of solutions: \n");
		
		for (int i = 0; i < numSolutions; i++) {
			System.out.println(solutions[i]);
		}
		
		return (numSolutions > 0);
	}

}