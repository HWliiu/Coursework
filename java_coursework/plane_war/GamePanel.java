package plane_war;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.HeadlessException;
import java.awt.Image;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.image.ImageObserver;
import java.util.ArrayList;
import java.util.Vector;

import javax.swing.JPanel;
import javax.swing.text.StyledEditorKit.BoldAction;

public class GamePanel extends JPanel implements Runnable,MouseMotionListener {
	public Plane player;
	public int mouseX;
	public int mouseY;
	private Image bg;
	private int bgY=0;
	private long startTime=System.currentTimeMillis();
	private Font font;
	private Vector<Repair> repairs=new Vector<Repair>();
	private boolean repairTrigger;
	public GamePanel() {
		player=new Player(100,400,1,1,100);
		bg=Toolkit.getDefaultToolkit().getImage(GamePanel.class.getResource("back.jpg"));
		this.addMouseMotionListener(this);
		font=new Font("", 0, 20);
		GameControl.score=0;
	}
	public void paint(Graphics g) {
		super.paint(g);
		g.setFont(font);
		g.setColor(Color.red);
		g.drawImage(bg, 0, bgY, this.getWidth(), this.getHeight(), this);
		g.drawImage(bg, 0, bgY-this.getHeight(), this.getWidth(), this.getHeight(), this);
		//player.paint(g, this);
		for (Plane e : Plane.planes) {
			e.paint(g, this);
		}
		g.drawString("SCORE:"+GameControl.score, 10, 50);
		for (Repair repair : repairs) {
			repair.paint(g, this);
		}
	}
	@Override
	public void run() {
		// TODO Auto-generated method stub
		while(true) {
			bgY++;
			if(bgY>this.getHeight()) {
				bgY=0;
			}
			long endTime=System.currentTimeMillis();
			if(endTime-startTime>2000 && Plane.planes.size()<10 ) {
				new Enemy((int)(Math.random()*450), -200, 5, 5, 100);
				startTime=endTime;
				//System.out.println("start"+startTime+",end"+endTime);
			}
			player.move(mouseX, mouseY);
			for(int i=0;i<Plane.planes.size();i++) {
				Plane.planes.get(i).move();
			}
			
			if(GameControl.score%5==0 && GameControl.score!=0 && !repairTrigger) {
				repairs.add(new Repair((int)(Math.random()*460), (int)(Math.random()*660), 5, 5));
				repairTrigger=true;
			}
			if(GameControl.score%5!=0) {
				repairTrigger=false;
			}
			for(int i=0;i<repairs.size();i++) {
				repairs.get(i).move();
				if(!repairs.get(i).isAlive) {
					repairs.remove(i);
					break;
				}
			}
			
			
			repaint();
			try {
				Thread.sleep(30);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	@Override
	public void mouseDragged(MouseEvent e) {
		// TODO Auto-generated method stub
	}
	@Override
	public void mouseMoved(MouseEvent e) {
		// TODO Auto-generated method stub
		mouseX=e.getX();
		mouseY=e.getY();
		//System.out.println("move");
	}
}
