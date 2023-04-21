package plane_war;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.management.loading.MLetMBean;
import javax.swing.JPanel;

public class GameOverPanel extends JPanel implements MouseListener{
	private Font font;
	public GameOverPanel() {
		// TODO Auto-generated constructor stub
		font=new Font("",0,30);
		this.addMouseListener(this);
	}
	public void paint(Graphics g) {
		// TODO Auto-generated method stub
		super.paint(g);
		this.setBackground(new Color(204, 204, 255));
		g.setColor(Color.red);
		g.setFont(font);
		g.drawString("GAME OVER", this.getWidth()/2-80, this.getHeight()/2-20);
		g.drawString("YOUR SCORE: "+GameControl.score, this.getWidth()/2-115, this.getHeight()/2+20);
		g.setColor(new Color(204,255,153,64));
		g.fillRect(this.getWidth()/2-80, this.getHeight()/2+30, 180, 50);
		g.setColor(new Color(204,255,153));
		g.drawRect(this.getWidth()/2-80, this.getHeight()/2+30, 180, 50);
		g.setColor(new Color(128,128,128));
		g.drawString("Restart", this.getWidth()/2-40, this.getHeight()/2+65);
	}
	@Override
	public void mouseClicked(MouseEvent arg0) {
		// TODO Auto-generated method stub
		if(this.getMousePosition().x>this.getWidth()/2-80&&this.getMousePosition().x<this.getWidth()/2+100
				&&this.getMousePosition().y>this.getHeight()/2+30&&this.getMousePosition().y<this.getHeight()/2+80) {
			GameControl.startGame();
		}
	}
	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mousePressed(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}
