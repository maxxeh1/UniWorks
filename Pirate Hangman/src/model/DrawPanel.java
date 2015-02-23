package model;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.*;

public class DrawPanel extends JPanel
{
	//Variables to allow for the HangmanGUI class to manipulate the images.
	int stickX = 333;
	int stickY = 185;
	int waterX = 3;
	int shipY = 30;
	int sharkY = 300;

	/*
	 * This method Paints all the .png's for the GUI.
	 */
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		Image sky = new ImageIcon("sky.png").getImage();
		Image ship = new ImageIcon("pirateship.png").getImage();
		Image water = new ImageIcon("water.png").getImage();
		Image stickman = new ImageIcon("stickman.png").getImage();
		Image shark = new ImageIcon("shark.png").getImage();
		Image sunclouds = new ImageIcon("sunandclouds.png").getImage();
		
		g.drawImage(sky, 3, 4, this);
		g.drawImage(ship, 30, shipY, this);
		g.drawImage(water, waterX, 4, this);
		g.drawImage(sunclouds, 50, 20, this);
		g.drawImage(stickman, stickX, stickY, this);
		g.drawImage(shark, 210, sharkY, this);
	}
}
