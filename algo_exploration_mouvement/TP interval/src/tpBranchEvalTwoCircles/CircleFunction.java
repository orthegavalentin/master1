
package tpBranchEvalTwoCircles;

import util.Box;
import util.IMath;
import util.Interval;
import util.Function;

/**
 * 2D distance expression from a given point of coordinates (p1,p2)
 */
public class CircleFunction extends Function {

	/**
	 * First coordinate (abscissa) of the fixed point
	 */
	public double p1;

	/**
	 * Second coordinate (ordinate) of the fixed point
	 */
	public double p2;

	/**
	 * Distance from the fixed point (p1,p2)
	 */
	public double radius;

	public CircleFunction(double _p1, double _p2, double _radius) {
		super();
		p1 = _p1;
		p2 = _p2;
		radius = _radius;
	}

	/**
	 * Evaluate in a box : f(x1,x2) = (p1 - x1)^2 + (p2 - x2)^2 - radius^2
	 */
	public Interval eval(Box x) {

		Interval p1d = new Interval(p1, p1);
		Interval p2d = new Interval(p2, p2);
		Interval radiusd = new Interval(radius, radius);
		
		Interval temp = IMath.sqr(IMath.sub(p1d, x.get(0)));
		Interval temp2 = IMath.sqr(IMath.sub(p2d, x.get(1)));

		return IMath.sub(IMath.add(temp, temp2), IMath.sqr(radiusd));

	}
}
