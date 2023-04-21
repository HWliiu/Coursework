package plane_war;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.image.ImageObserver;

public class Repair extends RigidBody {
	private boolean flagX;
	private boolean flagY;
	public Repair(int xPos, int yPos, int xSpeed, int ySpeed) {
		super(xPos, yPos, xSpeed, ySpeed);
		// TODO Auto-generated constructor stub
		tag="repair";
	}

	@Override
	public void move() {
		// TODO Auto-generated method stub
		if(flagX) {
			xPos-=xSpeed;
			if(xPos<0) {
				flagX=false;
			}
		}else {
			xPos+=xSpeed;
			if(xPos>450) {
				flagX=true;
			}
		}
		if(flagY) {
			yPos-=ySpeed;
			if(yPos<0) {
				flagY=false;
			}
		}else {
			yPos+=ySpeed;
			if(yPos>630) {
				flagY=true;
			}
		}
		collisionDetection();
	}

	@Override
	public void move(int mouseX, int mouseY) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void paint(Graphics g, ImageObserver obs) {
		// TODO Auto-generated method stub
		g.setColor(Color.green);
		g.fillRect(xPos+9, yPos, 12, 30);
		g.fillRect(xPos, yPos+9, 30, 12);
		g.drawRect(xPos, yPos, 30, 30);
	}

	@Override
	public void collisionDetection() {
		// TODO Auto-generated method stub
		collider.updateRegion(xPos, xPos+30, yPos, yPos+30);
		for (int i = 0; i < existRigidBody.size(); i++) {
			if (existRigidBody.get(i) != this && collider.collidTo(existRigidBody.get(i).collider) 
					&& ((existRigidBody.get(i).tag.equals(new String("player"))))) {
				isAlive=false;
				break;
			}
		}
	}

}
