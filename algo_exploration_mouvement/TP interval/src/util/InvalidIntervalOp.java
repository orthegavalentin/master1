package util;
public class InvalidIntervalOp extends RuntimeException {
	
	private static final long serialVersionUID = 1L;
	
	private String msg;
	
	public InvalidIntervalOp(String msg) {
		this.msg = msg;
	}
	
	public String toString() { return msg; }
}