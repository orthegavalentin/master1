
public class Terme {
	private boolean isConstant;
	private String label;
	
	public Terme(boolean isConstant, String label) {
		this.isConstant = isConstant;
		this.label = label;
	}
	
	public String getLabel() {
		return this.label;
	}
	
	public String export() {
		if(isConstant) {
			return "'" + getLabel() + "'";
		}
		return getLabel();
	}
	
	public boolean isConstant() {
		return isConstant;
	}
	
	public boolean equals(Terme t) {
		if(t.isConstant() == this.isConstant()) {
			if(t.getLabel().equals(this.label)) {
				return true;
			}
		}
		return false;
	}
}
