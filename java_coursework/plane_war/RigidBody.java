package plane_war;

import java.awt.Graphics;
import java.awt.image.ImageObserver;
import java.util.ArrayList;
import java.util.Vector;

public abstract class RigidBody {
	protected int xPos;
	protected int yPos;
	protected int xSpeed;
	protected int ySpeed;
	public String tag;
	public boolean isAlive=true;
	public static Vector<RigidBody> existRigidBody=new Vector<RigidBody>();
	public Collider collider=new Collider();
	public abstract void move();
	public abstract void move(int mouseX,int mouseY);
	public abstract void paint(Graphics g,ImageObserver obs);
	public abstract void collisionDetection();
	public RigidBody(int xPos,int yPos,int xSpeed,int ySpeed) {
		// TODO Auto-generated constructor stub
		existRigidBody.add(this);
		this.xPos=xPos;
		this.yPos=yPos;
		this.xSpeed=xSpeed;
		this.ySpeed=ySpeed;
	}

}
