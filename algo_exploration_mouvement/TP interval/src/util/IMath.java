package util;

/**
 * Last update: September 06, 2011
 *  		
 */
public class IMath {

	/**
	 *  Return -x. 
	 */
	public static Interval minus(Interval x) {
		if (x.isEmpty()) return Interval.EMPTY();
		return new Interval(-x.getUB(), -x.getLB());
	}
	
	/** 
	 * Contract x w.r.t y=-x. 
	 */
	public static void minusBwd(Interval y, Interval x) {
		x.setToInter(minus(y));
	}

	/** 
	 * Return x1+x2. 
	 */
	public static Interval add(Interval x1, Interval x2) {
		if (x1.isEmpty() || x2.isEmpty()) return Interval.EMPTY();
		 
		double _lb;
		double _ub;
		if (x1.getLB()==Double.NEGATIVE_INFINITY || x2.getLB()==Double.NEGATIVE_INFINITY) {
			_lb = Double.NEGATIVE_INFINITY;
		} else {
			_lb = x1.getLB() + x2.getLB();
		}
		if (x1.getUB()==Double.POSITIVE_INFINITY || x2.getUB()==Double.POSITIVE_INFINITY) {
			_ub = Double.POSITIVE_INFINITY;
		} else {
			_ub = x1.getUB() + x2.getUB();
		}			
		return new Interval(_lb,_ub);
	}
	
	/** 
	 * Return a*x.
	 */
	public static Interval scalmul(double a, Interval x) {
		if (x.isEmpty() || a==Double.NEGATIVE_INFINITY || a==Double.POSITIVE_INFINITY) return Interval.EMPTY();
		 
		if (a==0) return new Interval(0,0);
		if (a<0) return
				new Interval(x.getUB()==Double.POSITIVE_INFINITY? Double.NEGATIVE_INFINITY : a*x.getUB(),
						x.getLB()==Double.NEGATIVE_INFINITY? Double.POSITIVE_INFINITY : a*x.getLB());
		else return
			new Interval(x.getLB()==Double.NEGATIVE_INFINITY? Double.NEGATIVE_INFINITY : a*x.getLB(),
					x.getUB()==Double.POSITIVE_INFINITY? Double.POSITIVE_INFINITY : a*x.getUB());
	}
	
	/** 
	 * Contract x1 and x2 w.r.t y=x1+x2. 
	 */
	public static void addBwd(Interval y, Interval x1, Interval x2) {
		x1.setToInter(sub(y,x2));
		x2.setToInter(sub(y,x1));
	}
	
	/** 
	 * Return x1-x2.(Time stamp of the new interval is "now").
	 */
	public static Interval sub(Interval x1, Interval x2) {
		if (x1.isEmpty() || x2.isEmpty()) return Interval.EMPTY();
		 
		double _lb;
		double _ub;
		if (x1.getLB()==Double.NEGATIVE_INFINITY || x2.getUB()==Double.POSITIVE_INFINITY) {
			_lb = Double.NEGATIVE_INFINITY;
		} else {
			_lb = x1.getLB() - x2.getUB();
		}
		if (x1.getUB()==Double.POSITIVE_INFINITY || x2.getLB()==Double.NEGATIVE_INFINITY) {
			_ub = Double.POSITIVE_INFINITY;
		} else {
			_ub = x1.getUB() - x2.getLB();
		}			
		return new Interval(_lb,_ub);
	}
	
	
	/** 
	 * Contract x1 and x2 w.r.t y=x1-x2. 
	 */
	public static void subBwd(Interval y, Interval x1, Interval x2) {
		x1.setToInter(add(y,x2));
		x2.setToInter(sub(x1,y));
	}
	
	/** 
	 * Return x^2. 
	 */ 
	public static Interval sqr(Interval x) {
		if (x.isEmpty()) return Interval.EMPTY();		
		double lb=x.getLB();
		double ub=x.getUB();
		double _lb;
		double _ub;

		if (ub < 0) { _lb=ub*ub; _ub=lb*lb; }
		else if (lb > 0) { _lb=lb*lb; _ub=ub*ub; }
		else { _lb=0; _ub=Math.max(-lb,ub); _ub*=_ub; }
		
		return new Interval(_lb,_ub);
	}

	/** 
	 * Contract x w.r.t. y=x^2
	 */
	public static void sqrBwd(Interval y, Interval x) {
		Interval sqrt=IMath.sqrt(y);		
		Interval neg_proj=Interval.inter(x,IMath.minus(sqrt));
		Interval pos_proj=Interval.inter(x,sqrt);
		x.set(Interval.hull(neg_proj, pos_proj));
	}

	/** 
	 * Return sqrt(i). 
	 */ 
	public static Interval sqrt(Interval i) {
		if (i.isEmpty() || i.getUB()<0.0) return Interval.EMPTY();		
		double _lb=i.getLB()<0 ? 0 : Math.sqrt(i.getLB());
		double _ub=Math.sqrt(i.getUB());
		
		return new Interval(_lb,_ub);
	}

	/** 
	 * Contract x w.r.t. y=sqrt(x)	 
	 */
	public static void sqrtBwd(Interval y, Interval x) {
		x.setToInter(sqr(y));
	}
}
