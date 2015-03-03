package util;
/**
 * 
 * Last update: September 06, 2011
 *  
 */
public class InvalidBoxOp extends RuntimeException {
	
	private static final long serialVersionUID = 1L;
	
	private String msg;
	
	public InvalidBoxOp(String msg) {
		this.msg = msg;
	}
	
	public String toString() { return msg; }
}
