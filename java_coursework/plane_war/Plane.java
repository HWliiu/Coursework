package plane_war;

import java.awt.Graphics;
import java.awt.image.ImageObserver;
import java.util.Vector;

public abstract class Plane extends RigidBody{
	protected int maxHealth;
	protected int health;
	protected Vector<Bullet> bullet = new Vector<Bullet>();
	public static Vector<Plane> planes=new Vector<Plane>();
	public Plane(int xPos,int yPos,int xSpeed,int ySpeed,int maxHealth) {
		super(xPos, yPos, xSpeed,ySpeed);
		this.maxHealth=maxHealth;
		health=this.maxHealth;
		planes.add(this);
	}
	public void takeDamage(int damage) {
		health-=damage;
		//System.out.println(this.toString()+":"+health);
		if(health<=0) {
			isAlive=false;
		}
	}
	public void removePlane() {
		if(!isAlive) {
			if(existRigidBody.contains(this)) {
				existRigidBody.remove(this);				
			}
			Plane.planes.remove(this);
			//System.out.println("removed rigidbody "+this.toString());
			//System.out.println(existRigidBody.size());
		}else {
			System.out.println("err");
		}
	}
	public abstract void fire();
}
