package util;

import java.text.DecimalFormat;

/**
 * Interval
 */
public class Interval {
	
	// It is better not to define singleton like:
	//   static Interval EMPTY = new Interval(Double.NEGATIVE_INFINITY, Double.NEGATIVE_INFINITY);
	// in order to avoid cross references (e.g. between different empty boxes)
	private static double EMPTY_LB = Double.NEGATIVE_INFINITY;
	private static double EMPTY_UB = Double.NEGATIVE_INFINITY;	

	private double lb;
	private double ub;
	
	/**
	 * Create an (instance of the) empty interval
	 */
	public static Interval EMPTY() {
		return new Interval(EMPTY_LB, EMPTY_UB); 
	}
	
	/**
	 * Create an (instance of the) interval (-oo,+oo)
	 */
	public static Interval ALL_REALS() {
		return new Interval();
	}

	/**
	 * Create an interval (-oo,+oo)
	 */
	private Interval() {
		this(Double.NEGATIVE_INFINITY, Double.POSITIVE_INFINITY);
	}

	/**
	 * Create a (closed) interval [lb,ub]
	 */
	public Interval(double lb, double ub) {
		this.lb = lb;
		this.ub = ub;
		normalize();
	}

	private void normalize() {
		if (lb>ub) throw new InvalidIntervalOp("Bounds in reverse order");
		if (lb==Double.POSITIVE_INFINITY || ub==Double.NEGATIVE_INFINITY)
			setToEmpty();
	} 
	
	/** 
	 * Create a copy of "other".
	 */
	public Interval(Interval other) {
		this(other.getLB(), other.getUB());
	}

	/** 
	 * Return a copy of this.
	 */
	public Interval copy() {
		return new Interval(this);
	}

	/**
	 * Get the lower bound
	 */
	public double getLB() {
		return lb;
	}

	/**
	 * Get the upper bound
	 */
	public double getUB() {
		return ub;
	}

	/** 
	 * Set the lower bound of this interval 
	 */
	public void setLB(double _lb) {
		lb = _lb;
		normalize();
	}
	
	/** 
	 * Set the upper bound of this interval 
	 */
	public void setUB(double _ub) {
		ub = _ub;
		normalize();
	}
	
	/** 
	 * Set this interval to [_lb,_ub] 
	 */
	public void set(double _lb, double _ub) {
		lb = _lb;
		ub = _ub;
		normalize();
	}

	/** 
	 * Set the bounds of this interval to that of "other".
	 * (no intersection). 
	 * if clone=true, time stamp is set to that of "other". Otherwise,
	 * it is set to "now". 
	 */
	public void set(Interval other) {
		set(other.getLB(), other.getUB()); 
	}
	
	/** 
	 * Set this interval to the empty interval. 
	 */
	public void setToEmpty() {
		this.lb = EMPTY_LB;
		this.ub = EMPTY_UB;
		// don't call set(EMPTY_LB, false, EMPTY_UB, false) ==> infinite loop with "normalize"
	}
	
	/**
	 * Return true iff this interval is empty. 
	 */
	public boolean isEmpty() {
		return (lb==EMPTY_LB) && (ub==EMPTY_UB);
	}
	
	/** 
	 * Return the diameter 
	 */
	public double diam() {
		if (isEmpty()) {
			throw new InvalidIntervalOp("Diameter of an empty interval is undefined");
		} 
		if (lb==Double.NEGATIVE_INFINITY || ub==Double.POSITIVE_INFINITY)
			throw new InvalidIntervalOp("Cannot calculate diameter with infinite bounds");
		else {
			return ub-lb;
		}
	}
	
	/** 
	 * Return the intersection of x1 & x2 
	 */
	public static Interval inter(Interval x1, Interval x2) {
		Interval _x=x1.copy();
		_x.setToInter(x2);
		return _x;
	}

	/** 
	 * Set this interval to the intersection of itself with "other".
	 */ 
	public void setToInter(Interval other) {
		if (isEmpty()) return;
		if (other.isEmpty()) { setToEmpty(); return; }
		
		if (lb<other.getLB()) {
			this.lb = other.getLB();
		} 
		
		if (ub>other.getUB()) {
			this.ub = other.getUB();
		}
		
		if (lb>ub) setToEmpty();
		
		normalize();
	}

	/** 
	 * Return the hull of x1 and x2. 
	 */
	public static Interval hull(Interval x1, Interval x2) {
		Interval _x=x1.copy();
		_x.setToHull(x2);
		return _x;
	}
		
	/** 
	 * Set this interval to the hull of itself with "other".
	 * @return a reference to this.
	 */
	private void setToHull(Interval other) {
		if (isEmpty()) {
			set(other);
		} else if (!other.isEmpty()) {

			if (lb>other.getLB()) {
				this.lb = other.getLB();
			}
			
			if (ub<other.getUB()) {
				this.ub = other.getUB();
			}
			normalize(); // useful??
		}		
	}

    /**
     * Returns true if this interval contains the value
     */
    public boolean contains(double value) {
	return !isEmpty() && lb <= value && value <= ub;
    }

	/**
	 * Return the midpoint of this interval.
	 * By convention, the definition of midpoint is extended to the following cases:
	 * <ul>
	 * <li> mid([-oo,oo]) = 0
	 * <li> mid([x,oo]) = MAX_DOUBLE for all float x set.t. -oo<x<MAX_DOUBLE
	 * <li> mid([-oo,x]) = -MAX_DOUBLE for all float x set.t. -MAX_DOUBLE<x<+oo
	 * </ul>
	 */
	public double mid() {
		if (lb==Double.NEGATIVE_INFINITY) {
			if (ub==Double.POSITIVE_INFINITY) 
				return 0;			
			else { 
				if (ub==-Double.MAX_VALUE) throw new InvalidIntervalOp("Undefined midpoint for [-oo,-MAX_VALUE]");
				return -Double.MAX_VALUE;
			}
		} else if (ub==Double.POSITIVE_INFINITY) {
			if (lb==Double.MAX_VALUE) throw new InvalidIntervalOp("Undefined midpoint for [MAX_VALUE,+oo]");
			return Double.MAX_VALUE;
		}
		else return (lb+ub)/2;
	}
	
	/** 
	 * Bisect this interval at point "pt" and return the two subintervals.
	 * The right interval has an open bound 
	 */
	public Pair<Interval,Interval> bisect(double pt) throws InvalidIntervalOp {
		if (isEmpty()) throw new InvalidIntervalOp("Cannot bisect an empty interval");
		
		if (lb==ub) // this case is subsumed in the following one, but we
			// want to throw a specific exception. 
			throw new InvalidIntervalOp("Cannot bisect a degenerated interval");
		
		if (pt<=lb || pt>=ub) 
			throw new InvalidIntervalOp("Bisection point not strictly inside the interval");
		
		// rem: at this point, -oo<pt<+oo
		return new Pair<Interval,Interval>(
				new Interval(lb, pt), 
				new Interval(pt, ub));
	}

	/** 
	 * Bisect this interval at midpoint and return the two subintervals. 
	 */
	public Pair<Interval,Interval> bisect() throws InvalidIntervalOp {
		return bisect(mid());
	}
	
	/** 
	 * Return true if this interval is a superset of "other". 
	 */
//	public boolean superset(Interval other) {
//		if (other.isEmpty()) return true;
//		if (isEmpty()) return false;
//		
//		return (other.getLB()>=lb && other.getUB()<=ub);
//	}
	
	/** 
	 * Return true if this interval intersect "other". 
	 */
//	public boolean doesIntersect(Interval other) {
//		return !inter(this, other).isEmpty();
//	}
//	
	/** 
	 * Return true if this interval contains "x". 
	 */
//	public boolean contain(double x) {
//		return superset(new Interval(x,x));
//	}
	
	/** 
	 * Return true if the bounds of this interval match that of "other". 
	 */
//	public boolean equals(Object other) {
//		if (other instanceof Interval) {
//			Interval x=((Interval)other);
//			return x.getLB()==lb && x.getUB()==ub; 
//		} else {
//			return false;
//		}			
//	}
	
	/**
	 * Return a random point inside the interval
	 */
//	public double random() {
//		if (isEmpty()) throw new InvalidIntervalOp("Cannot pick a random point inside an empty interval");
//		if (lb==Double.NEGATIVE_INFINITY || ub==Double.POSITIVE_INFINITY) 
//			throw new InvalidIntervalOp("random() not implemented with infinite bounds");
//		/*
//		double _lb=lb==Double.NEGATIVE_INFINITY? -Double.MAX_VALUE : lb;
//		double _ub=ub==Double.NEGATIVE_INFINITY? Double.MAX_VALUE : ub;*/		
//		double x=lb+Math.random()*diam();
//		
//		if (x<=lb || x>=ub) {
//			throw new Error("Warning : random point out of/at the boundary of domain");
//		}
//		
//		/*
//		if (closedLB) {
//			if (x<lb) x=lb;
//		}	
//		else
//			if (x<=lb) x=mid();
//		
//		if (closedUB) {
//			if (x>ub) x=ub;
//		}	
//		else		
//			if (x>=ub) x=mid();
//		*/
//		
//		return x;
//	}
	
	/** 
	 * Return "[lb,ub]" 
	 */
	public String toString() {
		return isEmpty()? "[empty]" : 
			"[" + df.format(this.lb) + "," + df.format(this.ub) + "]";
	}

	static DecimalFormat df = new DecimalFormat ( ) ; // for toString()
	
	static { // default values
		df.setMaximumFractionDigits (4); 
		df.setMinimumFractionDigits (2);
		df.setDecimalSeparatorAlwaysShown (true);
	}

	/** 
	 * Change the number of digits displayed in toString() 
	 */
	public static void setFormatPrec(int minDigits, int maxDigits) {		
	    df.setMaximumFractionDigits ( maxDigits ) ; 
	    df.setMinimumFractionDigits ( minDigits ) ;
	}	
	
}
