
package tpBranchEvalTwoCircles;

import util.Box;
import util.IMath;
import util.Interval;
import util.Equation;

/**
 * 2D distance expression from a given point of coordinates (p1,p2)
 */
public class CircleEquation extends Equation {

    public CircleEquation(double _p1, double _p2, double _radius) {
	super(new CircleFunction(_p1, _p2, _radius));
    }
}
