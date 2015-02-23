package model;
import java.io.*;
import java.util.*;

public class Application 
{
	private static Scanner scan;

	//This is where everything starts. You can navigate to the text-based and the GUI-based version from here.
	public static void main(String args[]) throws IOException
	{
		scan = new Scanner(System.in);
		System.out.println("Welcome to Walk the Plank!");
		System.out.println("To play, you must work out the hidden word before the pirate walks the plank!");
		System.out.println("Please choose a game mode:" );
		System.out.println("1 - Text Based");
		System.out.println("2 - Graphical");
		try{
			int choice = scan.nextInt(); scan.nextLine();
			if(choice == 1)
			{
				HangmanModel mod = new HangmanModel();
				mod.loadWords("piratewords.txt");
				mod.run();
			}
			else if(choice == 2)
			{
				new HangmanGUI();
			}
		}
		catch(InputMismatchException e)
		{
			System.out.println("Please enter 1 or 2");
			scan.next();
		}
	}
}
