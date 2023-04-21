package plane_war;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.image.ImageObserver;
import java.util.ArrayList;

public class Enemy extends Plane {
	private Image enemy1Img;
	private long startTime=System.currentTimeMillis();
	private long startShufflingTime=System.currentTimeMillis();
	private int moveState;
	private boolean bombEnd;
	private int imgI;
	private boolean scoreTirgger;
	public Enemy(int xPos, int yPos, int xSpeed, int ySpeed, int maxHealth) {
		super(xPos, yPos, xSpeed, ySpeed, maxHealth);
		// TODO Auto-generated constructor stub
		tag="enemy";
		enemy1Img=Toolkit.getDefaultToolkit().getImage(GamePanel.class.getResource("el_0.gif"));
	}

	@Override
	public void fire() {
		// TODO Auto-generated method stub
		long endTime=System.currentTimeMillis();
		if(endTime-startTime>1000+(int)(Math.random()*2000)) {
			switch (moveState) {
			case -1:
				bullet.add(new Bullet(xPos-5, yPos+40, -xSpeed-3, 10,false));				
				break;
			case 0:
				bullet.add(new Bullet(xPos-5, yPos+40, 0, 10,false));	
				break;
			case 1:
				bullet.add(new Bullet(xPos-5, yPos+40, xSpeed+3, 10,false));	
				break;
			default:
				break;
			}
			startTime=endTime;
			//System.out.println("start"+startTime+",end"+endTime);
		}
	}

	@Override
	public void move() {
		// TODO Auto-generated method stub
		long endShufflingTime=System.currentTimeMillis();
		if(endShufflingTime-startShufflingTime>(int)(Math.random()*2000+500)) {
			double rand=Math.random();
			if(rand<0.4) {
				moveState=-1;
			}else if(rand<0.8) {
				moveState=1;
			}else {
				moveState=0;
			}
			startShufflingTime=endShufflingTime;
		}
		if(moveState==-1) {
			xPos-=xSpeed;
			enemy1Img=Toolkit.getDefaultToolkit().getImage(GamePanel.class.getResource("plane_l.gif"));
		}else if(moveState==1){
			xPos+=xSpeed;
			enemy1Img=Toolkit.getDefaultToolkit().getImage(GamePanel.class.getResource("plane_r.gif"));
		}else {
			enemy1Img=Toolkit.getDefaultToolkit().getImage(GamePanel.class.getResource("el_0.gif"));
		}
		yPos+=ySpeed;
		
		if(yPos>700) {
			this.isAlive=false;
			removePlane();
		}
		fire();
		collisionDetection();
		if(!isAlive) {			//播放爆炸动画
			existRigidBody.remove(this);
			moveState=0;
			enemy1Img=Toolkit.getDefaultToolkit().getImage(GamePanel.class.getResource("bomb_"+(imgI++)+".gif"));
			//System.out.println(this.toString()+":"+imgI);
			if(imgI>3) {
				bombEnd=true;
				imgI=3;
			}
			if(bombEnd && !scoreTirgger) {
				GameControl.score++;
				scoreTirgger=true;
				//removePlane();							
			}
			
		}
		for(int i=0;i<bullet.size();i++) {
			bullet.get(i).move();
			if(!bullet.get(i).isAlive) {
				bullet.remove(i);
				//existRigidBody.remove();
			}
		}
		//System.out.println(this.toString()+":s"+bullet.size());
		//System.out.println(Plane.planes.size());
	}

	@Override
	public void move(int mouseX, int mouseY) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void paint(Graphics g, ImageObserver obs) {
		// TODO Auto-generated method stub
		if(!bombEnd) {
			g.drawImage(enemy1Img, xPos-40, yPos-40, 80, 80, obs);			
			g.drawRect(xPos-40, yPos-40, 80, 80);
			g.setColor(Color.red);
			g.drawRect(xPos-45, yPos-50, maxHealth, 5);
			g.fillRect(xPos-45, yPos-50, health, 5);
		}
		//g.drawString(Integer.toString(health), xPos, yPos);
		for (Bullet bul : bullet) {
			bul.paint(g, obs);
			//g.drawRect(xPos-5, yPos+45, 10, 10);
		}
	}

	@Override
	public void collisionDetection() {
		// TODO Auto-generated method stub
		collider.updateRegion(xPos-40, xPos+40, yPos-40, yPos+40);
		for (int i = 0; i < existRigidBody.size(); i++) {
			if (existRigidBody.get(i) != this && collider.collidTo(existRigidBody.get(i).collider)) {
				if(existRigidBody.get(i).tag.equals(new String("upBullet"))) {
					takeDamage(20);
					existRigidBody.remove(i);	//移除子弹刚体
					//System.out.println("biu");
					break;					
				}
				if(existRigidBody.get(i).tag.equals(new String("player"))) {
					takeDamage(100);
					break;
				}
			}
		}
	}	 
}
