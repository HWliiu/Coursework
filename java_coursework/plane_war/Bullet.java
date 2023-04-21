package plane_war;

import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.image.ImageObserver;

public class Bullet extends RigidBody {
	private Image bulletImgUpward;
	private Image bulletImgDownward;
	private long startTime=System.currentTimeMillis();
	boolean isUpWard;
	public Bullet(int x,int y,int xSpeed,int ySpeed,boolean upward) {
		super(x, y, xSpeed,ySpeed);
		isUpWard=upward;
		bulletImgUpward=Toolkit.getDefaultToolkit().getImage(GamePanel.class.getResource("bullet.gif"));
		bulletImgDownward=Toolkit.getDefaultToolkit().getImage(GamePanel.class.getResource("bullet3.gif"));
		if(isUpWard) {
			tag="upBullet";
		}else {
			tag="downBullet";
		}
	}
	public void move() {
		// TODO Auto-generated method stub
		if(isUpWard) {
			yPos-=ySpeed;
		}else {
			yPos+=ySpeed;
			xPos+=xSpeed;
			long endTime=System.currentTimeMillis();
			if(endTime-startTime<300) {
				bulletImgDownward=Toolkit.getDefaultToolkit().getImage(GamePanel.class.getResource("bullet1.gif"));
			}else if(endTime-startTime<600) {
				bulletImgDownward=Toolkit.getDefaultToolkit().getImage(GamePanel.class.getResource("bullet3.gif"));
			}else {
				startTime=endTime;
			}
			
		}
		collisionDetection();
		if(yPos<0 || yPos>700) {
			this.isAlive=false;
			existRigidBody.remove(this);
		}
	} 
	@Override
	public void move(int mouseX, int mouseY) {
		// TODO Auto-generated method stub
		
	}
	public void paint(Graphics g, ImageObserver obs) {
		// TODO Auto-generated method stub
		//g.fillRect(xPos, yPos, 5, 20);
		if(isUpWard) {
			g.drawImage(bulletImgUpward, xPos, yPos, 50, 50, obs);	
			g.drawRect(xPos, yPos+20, 50, 30);
		}else {
			g.drawImage(bulletImgDownward, xPos, yPos, 20, 20, obs);
			g.drawRect(xPos, yPos, 20, 20);
		}
	}
	@Override
	public void collisionDetection() {
		// TODO Auto-generated method stub
		if(isUpWard) {
			collider.updateRegion(xPos, xPos+50, yPos+20, yPos+30);			
		}else {
			collider.updateRegion(xPos, xPos+20, yPos, yPos+20);
		}
		for (int i = 0; i < existRigidBody.size(); i++) {
			if (existRigidBody.get(i) != this && collider.collidTo(existRigidBody.get(i).collider)) {
				if(isUpWard) {
					if((existRigidBody.get(i).tag.equals(new String("enemy")))) {
						isAlive=false;
						//existRigidBody.remove(this);
						break;					
					}
				}else {
					if((existRigidBody.get(i).tag.equals(new String("player")))) {
						isAlive=false;
						//existRigidBody.remove(this);
						break;
					}
				}
			}
		}
	}
}
