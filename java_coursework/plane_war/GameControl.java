package plane_war;

import java.awt.Dimension;
import java.awt.Window;

import javax.swing.JButton;
import javax.swing.JFrame;

public class GameControl {
	private static JFrame huaBan;
	private static JFrame gameOverFrame;
	private static Thread t;
	public static int score;
	public static void startGame() {
		huaBan=new JFrame();
		huaBan.setVisible(true);
		huaBan.setTitle("Plane War");
		Dimension dimension=new Dimension(500, 700);
		huaBan.setSize(dimension);
		huaBan.setResizable(false);
		huaBan.setLocationRelativeTo(null);
		GamePanel huaBu=new GamePanel();
		t=new Thread(huaBu);
		t.start();
		huaBan.add(huaBu);
		huaBan.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		if(gameOverFrame!=null) {
			gameOverFrame.dispose();
		}
	}
	
	public static void gameOver() {
		gameOverFrame=new JFrame();
		gameOverFrame.setVisible(true);
		gameOverFrame.setTitle("Game over");
		Dimension dimension=new Dimension(300, 200);
		gameOverFrame.setSize(dimension);
		gameOverFrame.setLocationRelativeTo(null);
		gameOverFrame.setResizable(false);
		GameOverPanel gamePanel=new GameOverPanel();
		gameOverFrame.add(gamePanel);
		gameOverFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		huaBan.dispose();
		//t.interrupt();
		t.stop();	
	}
}
