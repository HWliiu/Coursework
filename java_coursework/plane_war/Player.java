package plane_war;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.image.ImageObserver;
import java.util.Timer;

import javax.swing.JFrame;

public class Player extends Plane {
	private Image playerImg;
	private long startTime=System.currentTimeMillis();
	public Player(int xPos,int yPos,int xSpeed,int ySpeed,int maxHealth) {
		super(xPos, yPos, xSpeed,ySpeed,maxHealth);
		// TODO Auto-generated constructor stub
		tag="player";
		playerImg=Toolkit.getDefaultToolkit().getImage(GamePanel.class.getResource("hero.gif"));
	}

	@Override
	public void move() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void paint(Graphics g,ImageObserver obs) {
		// TODO Auto-generated method stub
		g.drawImage(playerImg, xPos-50, yPos-50, 100, 100, obs);
		//g.setColor(new Color(192, 192, 64));
		for (Bullet bul : bullet) {
			bul.paint(g, obs);
		}
		g.setColor(Color.green);
		g.drawRect(xPos-48, yPos-50, maxHealth, 5);
		g.fillRect(xPos-48, yPos-50, health, 5);
		g.drawRect(xPos-40, yPos-40, 80, 50);
	}

	@Override
	public void fire() {
		// TODO Auto-generated method stub
		long endTime=System.currentTimeMillis();
		if(endTime-startTime>200) {
			bullet.add(new Bullet(xPos-23, yPos-50, 0, 30,true));
			startTime=endTime;
			//System.out.println("start"+startTime+",end"+endTime);
		}
	}

	@Override
	public void move(int mouseX, int mouseY) {
		// TODO Auto-generated method stub
			xPos+=((mouseX-xPos)/5)*xSpeed;
			yPos+=((mouseY-yPos)/5)*ySpeed;
			fire();
			collisionDetection();
			for(int i=0;i<bullet.size();i++) {
				bullet.get(i).move();
				if(!bullet.get(i).isAlive) {
					bullet.remove(i);
				}
			}
			//System.out.println("bullet number:"+bullet.size());

	}
	public void repairPlane() {
		health=maxHealth;
	}

	@Override
	public void collisionDetection() {
		// TODO Auto-generated method stub
		collider.updateRegion(xPos-40, xPos+40, yPos-40, yPos+10);
		for (int i = 0; i < existRigidBody.size(); i++) {
			if (existRigidBody.get(i) != this && collider.collidTo(existRigidBody.get(i).collider)) {
				if(((existRigidBody.get(i).tag.equals(new String("downBullet"))) || (existRigidBody.get(i).tag.equals(new String("enemy"))))) {
					takeDamage(10);
					existRigidBody.remove(i);
					//System.out.println("hitted");
					if(!isAlive) {
						System.out.println("you die");
						removePlane();
						GameControl.gameOver();
					}
					break;					
				}else if(existRigidBody.get(i).tag.equals(new String("repair"))){
					System.out.println("repaired");
					repairPlane();
					existRigidBody.remove(i);
					break;
				}
			}
		}
	}
}
