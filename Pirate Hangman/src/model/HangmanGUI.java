package model;
import javax.swing.*;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.InputMismatchException;
import java.util.Scanner;

public class HangmanGUI
{
	//This class holds all the necessary code for the GUI-based version of the game.
	private HangmanModel mod = new HangmanModel();
	
	//GUI Stuff
	JFrame frame;
	DrawPanel pirateShip;
	LosePanel youLosePanel;
	WinPanel youWinPanel;
	JPanel topPanel;
	JPanel bottomPanel;
	JPanel winPanel;
	JPanel losePanel;
	JPanel bottomPanelAfter;
	JPanel topPanelAfter;
	JPanel cards;
	JPanel topPanelCards;
	JPanel bottomPanelCards;
	
	//Bottom Panel
	JButton inputButtonLetter;
	JButton inputButtonWord;
	JTextField letterField;
	JTextField wordField;
	
	//Top Panel
	JLabel letterLabel;
	JLabel wordLabel;
	JLabel visibleLabel;
	JLabel visibleLabelAfter;
	JLabel visibleDes;
	JLabel guessedDes;
	JLabel guessedLetters;
	JLabel guessLeftDes;
	JLabel guessesLeft;
	
	//On win or lose
	JLabel youWin;
	JLabel yourWord;
	JLabel youLose;
	JLabel playAgain;
	JButton yesButton;
	JButton noButton;
	
	/*
	 * Starts a thread for the go() method.
	 */
	public HangmanGUI() throws IOException
	{
		mod.loadWords("piratewords.txt");
		try
		{
			SwingUtilities.invokeLater
			(
				new Runnable()
				{
					public void run()
					{
						go();
					}
				}
			);
		}
		catch(Exception e)
		{
			System.out.println("Invoke later exception" + e);
		}
	}
	
	/*
	 * Runs the GUI. Initialises all swing components and runs all necessary methods.
	 */
	public void go() 
	{
		mod.setup();

		
		//GUI Stuff
		frame = new JFrame();
		frame.setSize(600,550);
		frame.setVisible(true);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		try 
		{
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} 
		catch (ClassNotFoundException e) 
		{
			e.printStackTrace();
		} 
		catch (InstantiationException e) 
		{
			e.printStackTrace();
		} 
		catch (IllegalAccessException e) 
		{
			e.printStackTrace();
		} 
		catch (UnsupportedLookAndFeelException e) 
		{
			e.printStackTrace();
		}
		
		//Top Panel
		topPanel = new JPanel();
		topPanel.setLayout(new GridLayout(3, 2, 5, 2));
		topPanelAfter = new JPanel();
		topPanelAfter.setLayout(new GridLayout(2, 3, 5, 2));
		
		visibleDes = new JLabel("Guess this: ");
		topPanel.add(visibleDes);
		yourWord = new JLabel("Your word was: ");
		topPanelAfter.add(yourWord);
		visibleLabel = new JLabel(mod.getVisible());
		topPanel.add(visibleLabel);
		visibleLabelAfter = new JLabel(mod.getHidden());
		topPanelAfter.add(visibleLabelAfter);
		guessedDes = new JLabel("Your guessed letters: ");
		topPanel.add(guessedDes);
		guessedLetters = new JLabel(mod.getLetters());
		topPanel.add(guessedLetters);
		guessLeftDes = new JLabel("Guesses Left: ");
		topPanel.add(guessLeftDes);
		guessesLeft = new JLabel(String.valueOf(mod.guessLeft()));
		topPanel.add(guessesLeft);
	
		//CardLayout allows for panel switching upon certain conditions.
		topPanelCards = new JPanel(new CardLayout());
		topPanelCards.add(topPanel, "Top Panel");
		topPanelCards.add(topPanelAfter, "Top Panel After");
		
		CardLayout cardLayoutTop = (CardLayout) topPanelCards.getLayout();
		cardLayoutTop.show(topPanelCards, "Top Panel");
		
		frame.getContentPane().add(BorderLayout.NORTH, topPanelCards);
		
		
		//Middle Panel
		pirateShip = new DrawPanel();
		youLosePanel = new LosePanel();
		youWinPanel = new WinPanel();
		
		cards = new JPanel(new CardLayout());
		cards.add(pirateShip, "Pirate Ship");
		cards.add(youWinPanel, "Win Panel");
		cards.add(youLosePanel, "Lose Panel");
		
		//CardLayout allows for panel switching upon certain conditions.
		CardLayout cardLayout = (CardLayout) cards.getLayout();
		cardLayout.show(cards, "Pirate Ship");
		
		frame.getContentPane().add(BorderLayout.CENTER, cards);
		
		//Bottom Panel
		bottomPanel = new JPanel();
		bottomPanelAfter = new JPanel();
		bottomPanel.setLayout(new GridLayout(2, 2, 5, 2));
		
		letterLabel = new JLabel("Enter a letter: ");
		bottomPanel.add(letterLabel);
		letterField = new JTextField(10);
		bottomPanel.add(letterField);
		inputButtonLetter = new JButton("Enter!");
		bottomPanel.add(inputButtonLetter);
		inputButtonLetter.addActionListener(new tryThisListener());
		wordLabel = new JLabel("Enter a word: ");
		bottomPanel.add(wordLabel);
		wordField = new JTextField(10);
		bottomPanel.add(wordField);
		inputButtonWord = new JButton("Enter!");
		bottomPanel.add(inputButtonWord);
		inputButtonWord.addActionListener(new tryWordListener());;
		playAgain = new JLabel("Would you like to play again?");
		bottomPanelAfter.add(playAgain);
		yesButton = new JButton("Yes");
		bottomPanelAfter.add(yesButton);
		yesButton.addActionListener(new yesListener());;
		noButton = new JButton("No");
		bottomPanelAfter.add(noButton);
		noButton.addActionListener(new noListener());;
		
		//CardLayout allows for panel switching upon certain conditions.
		bottomPanelCards = new JPanel(new CardLayout());
		bottomPanelCards.add(bottomPanel, "Bottom Panel");
		bottomPanelCards.add(bottomPanelAfter, "Bottom Panel After");
		
		CardLayout cardLayoutBottom = (CardLayout) bottomPanelCards.getLayout();
		cardLayoutBottom.show(bottomPanelCards, "Bottom Panel");
		
		frame.getContentPane().add(BorderLayout.SOUTH, bottomPanelCards);
		
		//Animation methods.
		animateWater();
		animateShip();
		animateShark();
	}

	/*
	 * This method holds the necessary code to end the application. It works out whether the user has won or lost and 
	 * provides the relevant stickman animations and switches the CardLayouts to the appropriate panels.
	 */
	public void end() 
	{	
		SwingWorker<Void, Void> worker = new SwingWorker<Void, Void>()
		{
			protected Void doInBackground() throws Exception
			{
				int guesses = mod.guessLeft();
				String stars = visibleLabel.getText();
				String answer = mod.getHidden();
		
				if(guesses <= 0)
				{
					visibleLabel.setText(answer);
					for(int i=0; i<20; i++)
					{
						pirateShip.stickX = pirateShip.stickX -1;
						pirateShip.stickY = pirateShip.stickY +7;
						pirateShip.repaint();
						Thread.sleep(100);
					}
					Thread.sleep(2000);
					CardLayout cardLayout = (CardLayout) cards.getLayout();
					cardLayout.show(cards, "Lose Panel");
					CardLayout cardLayoutBottom = (CardLayout) bottomPanelCards.getLayout();
					cardLayoutBottom.show(bottomPanelCards, "Bottom Panel After");
					CardLayout cardLayoutTop = (CardLayout) topPanelCards.getLayout();
					cardLayoutTop.show(topPanelCards, "Top Panel After");
					}
				else if(stars.equals(answer))
				{
					for(int i=0; i<40; i++)
					{
						pirateShip.stickX = pirateShip.stickX -7;
						pirateShip.stickY = pirateShip.stickY -10;
						pirateShip.repaint();
						Thread.sleep(100);
					}
					Thread.sleep(2000);
					CardLayout cardLayout = (CardLayout) cards.getLayout();
					cardLayout.show(cards, "Win Panel");
					CardLayout cardLayoutBottom = (CardLayout) bottomPanelCards.getLayout();
					cardLayoutBottom.show(bottomPanelCards, "Bottom Panel After");
					CardLayout cardLayoutTop = (CardLayout) topPanelCards.getLayout();
					cardLayoutTop.show(topPanelCards, "Top Panel After");
				}
				
				return null;
			}
		};
		worker.execute();
	}
	
	/*
	 * This method moves the water from side to side in an infinite loop.
	 */
	public void animateWater()
	{
		SwingWorker<Void, Void> worker = new SwingWorker<Void, Void>()
			{
				protected Void doInBackground() throws Exception
				{
					boolean forever = true;
					boolean always = true;
					do
					{
						do
						{
							for(int i=0; i<15; i++)
							{
								pirateShip.waterX = pirateShip.waterX + 2;
								pirateShip.repaint();
								Thread.sleep(150);
							}
							always = false;
						}
						while(always);
						do
						{
							for(int i=0; i<15; i++)
							{
								pirateShip.waterX = pirateShip.waterX - 2;
								pirateShip.repaint();
								Thread.sleep(150);
							}
							always = true;
						}
						while(always = false);
					}
					while(forever);
					return null;
				}
			};
			worker.execute();
	}
	
	/*
	 * This method moves the ship up and down in an infinite loop.
	 */
	public void animateShip()
	{
		SwingWorker<Void, Void> worker = new SwingWorker<Void, Void>()
			{
				protected Void doInBackground() throws Exception
				{
					boolean forever = true;
					boolean always = true;
					do
					{
					do
					{
						for(int i=0; i<5; i++)
						{
							pirateShip.stickY = pirateShip.stickY + 1;
							pirateShip.shipY = pirateShip.shipY + 1;
							pirateShip.repaint();
							Thread.sleep(300);
						}
						always = false;
					}
					while(always);
					do
					{
						for(int i=0; i<5; i++)
						{
							pirateShip.stickY = pirateShip.stickY - 1;
							pirateShip.shipY = pirateShip.shipY - 1;
							pirateShip.repaint();
							Thread.sleep(300);
						}
						always = true;
					}
					while(always = false);
					}
					while(forever);
					return null;
				}
			};
			worker.execute();
	}
	
	/*
	 * This method moves the shark up and down in an infinite loop.
	 */
	public void animateShark()
	{
		SwingWorker<Void, Void> worker = new SwingWorker<Void, Void>()
			{
				protected Void doInBackground() throws Exception
				{
					boolean forever = true;
					boolean always = true;
					do
					{
					do
					{
						for(int i=0; i<3; i++)
						{
							pirateShip.sharkY = pirateShip.sharkY + 1;
							pirateShip.repaint();
							Thread.sleep(300);
						}
						always = false;
					}
					while(always);
					do
					{
						for(int i=0; i<3; i++)
						{
							pirateShip.sharkY = pirateShip.sharkY - 1;
							pirateShip.repaint();
							Thread.sleep(300);
						}
						always = true;
					}
					while(always = false);
					}
					while(forever);
					return null;
				}
			};
			worker.execute();
	}
	
	/*
	 * Inner class that listens for the user input into the word JTextField. Calls the appropriate methods from HangmanModel.
	 * It also provides the appropriate animation for the stickman on incorrect guesses.
	 */
	class tryWordListener implements ActionListener
	{
		public void actionPerformed(ActionEvent event)
		{
			SwingWorker<Void, Void> worker = new SwingWorker<Void, Void>()
			{
				protected Void doInBackground() throws Exception
				{
					String tryThis = wordField.getText();
					if(mod.tryWord(tryThis))
					{
						visibleLabel.setText(mod.getHidden());
					}
					else
					{
						for(int i=0; i<10; i++)
						{
							pirateShip.stickX = pirateShip.stickX -5;
							pirateShip.repaint();
							Thread.sleep(100);
						}
					}
					guessesLeft.setText(String.valueOf(mod.guessLeft()));
					wordField.setText("");
					end();
					return null;
				}
			};
			worker.execute();
		}
	}
	
	/*
	 * Inner class that listens for the user input into the letter JTextField. Calls the appropriate methods from HangmanModel. 
	 * It also provides the appropriate animation for the stickman on incorrect guesses.
	 */
	class tryThisListener implements ActionListener
	{
		public void actionPerformed(ActionEvent event)
		{
				SwingWorker<Void, Void> worker = new SwingWorker<Void, Void>()
				{
					protected Void doInBackground() throws Exception
					{
						String str = letterField.getText();
						char tryThis = str.charAt(0);
						if(mod.tryThis(tryThis))
						{
							visibleLabel.setText(mod.getVisible());	
						}
						else
						{
							for(int i=0; i<10; i++)
							{
								pirateShip.stickX = pirateShip.stickX -1;
								pirateShip.repaint();
								Thread.sleep(100);
							}
						}
						guessesLeft.setText(String.valueOf(mod.guessLeft()));
						guessedLetters.setText(mod.getLetters());
						letterField.setText("");
						end();
						return null;
				}
			};
			worker.execute();
		}
	}
	
	/*
	 * This method listens to the yes JButton to decide whether the user wants to play again.
	 */
	class yesListener implements ActionListener
	{
		public void actionPerformed(ActionEvent event)
		{
			frame.dispose();
			mod.resetGuesses();
			go();
		}
	}
	
	/*
	 * This method listens to the no JButton to decide whether the user wants to play again.
	 */
	class noListener implements ActionListener
	{
		public void actionPerformed(ActionEvent event)
		{
			System.out.println("Thanks for playing!");
			System.out.println("Goodbye!");
			System.exit(0);
		}
	}
}

