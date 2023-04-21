package plane_war;

public final class Collider {
	private int left;
	private int right;
	private int top;
	private int bottom;
	public void updateRegion(int l,int r,int t,int b) {
		left=l;
		right=r;
		top=t;
		bottom=b;
	}
	public boolean collidTo(Collider other) {
		if(other.left>this.right || other.right<this.left || other.top>this.bottom || other.bottom<this.top) {
			return false;
		}
		return true;
	}
}
