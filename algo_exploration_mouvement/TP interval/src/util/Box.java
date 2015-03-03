package util;

import java.util.Vector;


/**
 * Last update: September 06, 2011
 * 
 * By convention an empty box has a dimension. A box becomes empty 
 * when one of its component becomes empty and all the components
 * are set to the empty interval.  
 */
public class Box {	

	/* The components.
	 * Must be *private* for at least 2 reasons:
	 * - the underlying structure may change
	 * - the box must be set to an box empty when a component is empty
	 *   see, e.g. set(int, Interval). */
	private Vector<Interval> comp;	
	
	/** Create a box of dimension "dim" with 
	 * all the components initialized to (a copy of) "x". */
	public Box(int dim, Interval x) {
		if (dim<=0) throw new InvalidBoxOp("Negative box dimension.");
		comp = new Vector<Interval>(dim);
		for (int i=0; i<dim; i++) {
			comp.add(x.copy());	
		}
	}

	/** Create a box of dimension "dim" with 
	 * all components initialized to (-inf,+inf) */
	public Box(int dim) {
		this(dim, Interval.ALL_REALS());
	}

	/** Create a deep copy of "other".
	 * 
	 */
	private Box(Box other) {
		comp = new Vector<Interval>(other.dim());		
		for (int i=0; i<other.dim(); i++)
			comp.add(other.comp.get(i).copy());
	}
	
	/**
	 * Create the box [bounds[0][0],bounds[0][1]]x...x[bounds[n-1][0],bounds[n-1][1]]
	 * 
	 * @param bounds an nx2 array of doubles
	 */
//	public Box(double[][] bounds) {
//		comp = new Vector<Interval>(bounds.length);
//		for (int i=0; i<bounds.length; i++)
//			comp.add(new Interval(bounds[i][0],bounds[i][1]));
//	}
	
	/** 
	 * Get a copy of "other". 
	 */
	private Box copy() {
		return new Box(this);
	}
	
	/** 
	 * Create a empty box (all the components being empty intervals). 
	 */
//	public static Box EMPTY(int dim) {
//		return new Box(dim, Interval.EMPTY());
//	}
	
	/** 
	 * Resize the box. If the size is increased,	 
	 * the existing components are not affected and 
	 * the new ones are set to (-inf,+inf), or the
	 * empty interval if the box was empty.
	 */
//	public void reDim(int i) {		
//		if (i<=0) throw new InvalidBoxOp("Negative box dimension");
//		if (i>dim()) {
//			for (int j=dim()+1; j<=i; j++)
//				comp.addElement(isEmpty()? Interval.EMPTY() : Interval.ALL_REALS());
//		}
//		else comp.setSize(i);
//	}
	 
	/** 
	 * Increment the dimension by one. 
	 * @see reDim(int)
	 */
//	public void incrDim() {
//		reDim(dim()+1);
//	}
//	
	/**
	 * Get the lower bound of the ith component
	 */
//	public double getLB(int i) {
//		return comp.get(i).getLB();
//	}

	/**
	 * Get the upper bound of the ith component
	 */
//	public double getUB(int i) {
//		return comp.get(i).getUB();
//	}
	
	/** 
	 * Get a const reference of the ith component.
	 * 
	 * This reference is non assignable directly, you 
	 * must use set(int, Interval) instead. We can
	 * control when a box becomes empty in this way.
	 */ 
	public Interval get(int i) {
		return comp.get(i);
	}
	
	/** 
	 * Set the lower bound of the ith component of x, unless the
	 * box was empty in which case the ith component remains
	 * the empty interval.
	 */
//	public void setLB(int i, double lb) {
//		if (!isEmpty()) {		
//			comp.get(i).setLB(lb);
//			if (comp.get(i).isEmpty()) setToEmpty();
//		}
//	}

	/** 
	 * Set the upper bound of the ith component of x, unless the
	 * box was empty in which case the ith component remains
	 * the empty interval.
	 */
//	public void setUB(int i, double ub) {
//		if (!isEmpty()) {
//			comp.get(i).setUB(ub);		
//			if (comp.get(i).isEmpty()) setToEmpty();
//		}
//	}

	/** 
	 * Assign the ith component to [lb,ub], unless the
	 * box was empty in which case the ith component remains
	 * the empty interval.
	 */
	private void set(int i, double lb, double ub) {
		if (!isEmpty()) {		
			comp.get(i).set(lb,ub);		
			if (comp.get(i).isEmpty()) setToEmpty();
		}
	}
	
	/** 
	 * Assign the ith component to x:
	 * 1- The reference of the ith component does not change.
	 * 2- The bounds are copies of the bounds of x, unless the
	 *    box was empty in which case the ith component remains
	 *    the empty interval.
	 * 3- If x is the empty interval, the box becomes empty. 
	 */
	public void set(int i, Interval x) {
		set(i, x.getLB(), x.getUB());
	}

	/** 
	 * Assign this box to x.
	 * 
	 * Dimensions of this and x must match 
	 */
//	public void set(Box x) {
//		if (dim()!=x.dim()) throw new InvalidBoxOp("Cannot set a box to a box with different dimension");
//		if (x.isEmpty()) { setToEmpty(); return; }
//		// don't use "set(...)" because the test "isEmpty()" called inside
//		// may return prematurely in case "this" is empty.
//		// use physical copy instead:
//		for (int i=0; i<dim(); i++) {
//			comp.get(i).set(x.comp.get(i));			
//		}
//	}

	/** 
	 * Return the dimension.
	 * */
	public int dim() {
		return comp.size();
	}
	
	/**
	 * Return the midpoint (a degenerated box)
	 */
	public Box mid() {
		Box mBox=new Box(dim());
		for (int i=0; i<dim(); i++) {
			double m =  get(i).mid();
			mBox.set(i, new Interval(m,m));
		}
		return mBox;
	}
	
	/** 
	 * True iff this box is empty 
	 * */
	public boolean isEmpty() {
		return get(0).isEmpty();
	}

	/** 
	 * True iff this box is flat, i.e.,
	 * the radius is 0 on at least one dimension 
	 * */
//	public boolean isFlat() {
//		if (isEmpty()) return false;
//		for (int i=0; i<dim(); i++)
//			if (getLB(i)==getUB(i)) // don't use diam() because of roundoff
//				return true;
//		return false;
//	}
	
	/**
	 * Set this box to the empty box 
	 * */
	public void setToEmpty() {
		// warning: do not insert this test:
		//	 if (isEmpty()) return;
		// because we call setToEmpty() from set(...) and the first component
		// may be empty in an intermediate state
		
		for (int i=0; i<dim(); i++) 
			comp.get(i).setToEmpty(); 
	}
	
	/** 
	 * Return true if the bounds of this box match that of "other". 
	 */
//	public boolean equals(Object other) {
//		if (!(other instanceof Box)) return false;
//		Box b2=(Box) other;
//		if (dim()!=b2.dim()) return false;
//		if (isEmpty() || b2.isEmpty()) return isEmpty() && b2.isEmpty();
//		for (int i=0; i<dim(); i++)
//			if (!comp.get(i).equals(b2.comp.get(i))) return false;
//		return true;
//	}
//	
	
	/** 
	 * Return the index of the component with minimal/maximal diameter
	 *  
	 *  @param min true => minimal diameter 
	 *  @throws InvalidBoxOp if the box is empty. 
	 */ 
    	private int extrDiamIndex(boolean min) {
    	double d=min? Double.POSITIVE_INFINITY : -1;
    	int selectedIndex=-1;
    	if (isEmpty()) throw new InvalidBoxOp("Diameter of an empty box is undefined");
    	for (int i=0; i<comp.size(); i++) {
    		if (min? get(i).diam()<d : get(i).diam()>d) { 
    			selectedIndex=i; 
    			d=get(i).diam(); 
    		}
    	}
    	return selectedIndex;
    }		
	
	/** 
	 * Return the maximal diameter for all the components
	 *  
	 *  @throws InvalidBoxOp if the box is empty. 
	 */ 
	public double maxDiam() {
		return get(extrDiamIndex(false)).diam();
	}	

	/** 
	 * Return the minimal diameter for all the components
	 *  
	 *  @throws InvalidBoxOp if the box is empty. 
	 */ 
//	public double minDiam() {
//		return get(extrDiamIndex(true)).diam();
//	}
	
	/** 
	 * Intersects the ith component of this box with another interval.
	 * 
	 * @return true iff the intersection is nonempty   
	 */
	public boolean setToInter(int i, Interval x) {
		//if (x.isEmpty()) { setToEmpty(); return false; }
		//if (isEmpty()) return false;
		comp.get(i).setToInter(x);
		if (comp.get(i).isEmpty()) { setToEmpty(); return false; }
		return true;
	}

	/** 
	 * Intersects this box with another.
	 * 
	 * @return true iff the intersection is nonempty   
	 * @throws InvalidBoxOp if boxes do not have the same dimensions
	 * and dimensions are not 0 (special case for the empty box).
	 */
//	public boolean setToInter(Box other)  {		
//		// dimensions are non zero henceforth
//		if (dim()!=other.dim()) throw new InvalidBoxOp("Cannot intersect boxes with different dimensions");
//
//		if (isEmpty()) return false;
//		if (other.isEmpty()) { setToEmpty(); return false; }
//		
//		for (int i=0; i<dim(); i++) {
//			Interval x=comp.get(i); // the reference
//			x.setToInter(other.comp.get(i));
//			if (x.isEmpty()) {
//				setToEmpty();
//				return false;
//			}
//		}
//
//		return true;
//	}
		
	/** 
	 * Return the intersection of x & y.
	 * @see inter(Box other)
	 */
//	public static Box inter(Box x, Box y) {
//		Box b=x.copy();
//		b.setToInter(y);
//		return b;
//	}
	
	/** 
	 * Set the ith component of this box to the hull with another interval.
	 */
//	public void setToHull(int i, Interval x) {
//		comp.get(i).setToHull(x);		
//	}
	
	/** 
	 * Set this box to the hull of itself and another.
	 * 
	 * @throws InvalidBoxOp if boxes do not have the same dimensions
	 * and dimensions are not 0 (special case for the empty box).
	 */
//	public void setToHull(Box other)  {		
//		// dimensions are non zero henceforth
//		if (dim()!=other.dim()) throw new InvalidBoxOp("Cannot make the hull of boxes with different dimensions");
//
//		if (other.isEmpty()) return;
//		if (isEmpty()) { set(other); return; }		
//
//		for (int i=0; i<dim(); i++) {
//			comp.get(i).setToHull(other.comp.get(i));
//		}		
//	}
	
	/** 
	 * Return the hull of x & y.
	 * @see hull(Box other)
	 */
//	public static Box hull(Box x, Box y) {
//		Box z = x.copy();
//		z.setToHull(y);
//		return z;
//	}
	/**
	 * Return a random vector
	 */
//	public Box random() {
//		Box b=new Box(dim());
//		for (int i=0; i<dim(); i++) {
//			double x=get(i).random();
//			b.set(i, new Interval(x,x));
//		}
//		return b;
//	}
	
	/** 
	 * Bisect the box along "var" at point "pt" and return the two sub-boxes.
	 * Sub-boxes are new boxes independent from each other and
	 * independent from the current box. 
	 * 
	 * @throws InvalidIntervalOp (cf. Interval.bisect) 
	 */
	private Pair<Box,Box> bisect(int var, double pt) {
				
		// split the variable
		Interval i = get(var);
		Pair<Interval,Interval> pi = i.bisect(pt); 
		// copy the box
		Box lowerHalf = copy();
		lowerHalf.set(var, pi.fst);
		Box upperHalf = copy();
		upperHalf.set(var, pi.snd);
		
		return new Pair<Box,Box>(lowerHalf,upperHalf);
	}
	
	/** 
	 * Bisect the box along "var" (at midpoint) and return the two sub-boxes.
	 * Sub-boxes are new boxes independent from each other and
	 * independent from the current box. 
	 * 
	 * @throws InvalidIntervalOp (cf. Interval.bisect) 
	 */
	private Pair<Box,Box> bisect(int var) {
		return bisect(var,get(var).mid());
	}
	
	/** 
	 * Bisect the box along the variable with maximal diameter.
	 * 
	 * @throws InvalidIntervalOp (cf. Interval.bisect)   
	 */
	public Pair<Box,Box> bisect() {
		// select the variable with the maximum interval size
		double sizeMax = Double.NEGATIVE_INFINITY;
		int varMax = -1;
		for (int var=0; var<dim(); var++) {
			double sizeI = get(var).diam();
			if (sizeI>sizeMax) {
				sizeMax = sizeI;
				varMax = var;
			}
		}
		return bisect(varMax);
	}	
	
	/**
	 * Display the box
	 */
	public String toString() {
		String res = "(";
		for (int i=0; i<dim(); i++) 
			res += comp.get(i) + (i<dim()-1? " ; " : "");
		return res+")";
	}
}