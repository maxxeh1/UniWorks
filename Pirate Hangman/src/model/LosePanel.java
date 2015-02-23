package model;
import java.awt.*;
import javax.swing.*;

public class LosePanel extends JPanel
{
	/*
	 * This method paints the .jpg for the lose panel
	 */
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		Image lose = new ImageIcon("you lose.jpg").getImage();
		g.drawImage(lose, 3, 4, this);
	}
}
