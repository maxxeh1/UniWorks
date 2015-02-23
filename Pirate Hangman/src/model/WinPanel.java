package model;
import java.awt.*;
import javax.swing.*;

public class WinPanel extends JPanel
{
	/*
	 * This method paints the .jpg for the win panel.
	 */
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		Image win = new ImageIcon("you win.jpg").getImage();
		g.drawImage(win, 3, 4, this);
	}
}
