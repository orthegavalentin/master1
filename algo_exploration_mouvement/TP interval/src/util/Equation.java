
package util;

public class Equation extends NumericConstraint {

    public Equation(Function f) {
	super(f);
    }

    public boolean violated(Box b) {
	Interval res = this.func.eval(b);
	return !(res.contains(0));
    }
}
