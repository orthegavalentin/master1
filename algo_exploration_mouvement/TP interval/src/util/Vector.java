package util;

/**
 * Class representing a vector x of R^n
 * 
 * @author Gilles Chabert
 *
 */
public class Vector {
	private int n;
	private double[] tab;
	
	/**
	 * Build x as an uninitialized vector of R^n.
	 */
	public Vector(int n) {
		this.n = n;
		this.tab=new double[n];
		for (int i=0; i<n; i++)
			tab[i]=0;
	}
	
	/**
	 * Build x as a copy of v.
	 */
	public Vector(Vector v) {
		this.n = v.n;
		this.tab=new double[n];
		for (int i=0; i<n; i++)
			set(i,v.get(i));
	}
	
	/**
	 * Build x from an array of double.
	 */
	public Vector(double[] x) {
		this.n = x.length;
		this.tab=new double[n];
		for (int i=0; i<n; i++)
			set(i,x[i]);
	}
	
	/**
	 * Return the size (n) of x.
	 */
	public int size() {
		return n;
	}
	
	/**
	 * Return x[i].
	 */
	public double get(int i) {
		return tab[i];
	}
	
	/**
	 * Set x[i].
	 */
	public void set(int i, double d) {
		tab[i]=d;
	}
	
	/**
	 * Return -x.
	 */
	public Vector minus() {
		Vector v2=new Vector(n);
		for (int i=0; i<n; i++)
			v2.set(i,-get(i));
		return v2;
	}
	
	/**
	 * Return x+v.
	 */
	public Vector add(Vector v) {
		assert(n==v.size());
		Vector v2=new Vector(n);
		for (int i=0; i<n; i++)
			v2.set(i,get(i)+v.get(i));
		return v2;
	}
	
	/**
	 * Return x-v.
	 */
	public Vector sub(Vector v) {
		return add(v.minus());
	}
	
	/**
	 * Return lambda*x.
	 */
	public Vector leftmul(double lambda) {
		Vector v=new Vector(n);
		for (int i=0; i<n; i++)
			v.set(i,lambda*get(i));
		return v;
	}
	
	/**
	 * Return <x,v>.
	 */
	public double scalar(Vector v) {
		assert(n==v.size());
		double s=0;
		for (int i=0; i<n; i++)
			s=s+get(i)*v.get(i);
		return s;
	}
	
	/**
	 * Return ||x||.
	 */
	public double norm() {
		double ret=0;
		for (int i=0; i<n; i++)
			ret=ret+Math.pow(get(i),2);
		return Math.sqrt(ret);
	}
	
	/**
	 * Return x as a string.
	 */
	public String toString() {
		String res="(";
		for (int i=0; i<n; i++) {
			res+=get(i)+(i<n-1?", ":"");
			if (i==4) res+="\n\t";
		}
		return res+")";
	}
}
 