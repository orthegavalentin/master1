
package util;

public abstract class NumericConstraint extends Constraint {

    Function func;

    public NumericConstraint (Function f) {
	func = f;
    }
}

