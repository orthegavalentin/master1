package util;

public class Pair<A,B> {
	public A fst;
	public B snd;
	public Pair(A fst, B snd) {
		this.fst = fst;
		this.snd = snd;
	}
	public String toString() {
		return "(" + this.fst + "," + this.snd + ")";
	}
}