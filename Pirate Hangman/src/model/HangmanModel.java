package model;

import java.io.*;
import java.util.*;

public class HangmanModel implements GameModelInterface
{
	//Variable Declaration
	private ArrayList<WordsToGuess> words;
	private String currentLetters;
	private ArrayList<Character> guessedLetters;
	private int guessesLeft;
	private Random randomGenerator  = new Random();
	private String chosenWord;
	private Scanner scan;
	
	/*
	 * Constructor for HangmanModel
	 */
	public HangmanModel()
	{
		words = new ArrayList<WordsToGuess>();
		guessedLetters = new ArrayList<Character>();
		//guessedLetters = new ArrayList<String>();
		guessesLeft = 10;
		scan = new Scanner(System.in);
	}
	
	/*
	 * This method sets up two of the most important aspects of the code. This method is used in both text-based and 
	 * GUI-based version of the game. Primarily allows HangmanGUI class to do this.
	 */
	public void setup()
	{
		chosenWord = randomWord();
		placeStars(chosenWord);
	}
	
	/*
	 * This method resets the guessesLeft variable to 10. Primarily allows HangmanGUI class to do this.
	 */
	public void resetGuesses()
	{
		guessesLeft = 10;
	}
	
	/*
	 * This method runs the text-based version of the game. 
	 */
	public void run() 
	{
		setup();
		//This do while loops allows the user to try letters or words. Ends if guessesLeft == 0 or there are no more stars left.
		do
		{
			
			System.out.println("Here is your word: ");
			System.out.println(getVisible());
			
				System.out.println("Please choose to enter a letter (Enter 1) or the phrase (Enter 2): ");
				try{
				int choice = scan.nextInt(); scan.nextLine();
				if(choice == 1)
				{
					System.out.println("Please enter a letter: ");
					try
					{
						char letter = scan.next("[a-zA-Z]").charAt(0);
						if(tryThis(letter) == false)
						{
							
							System.out.println("Unlucky! Keep going.");
							System.out.println("You have "+guessesLeft+" guesses left.");
							System.out.println("You have used: " + getLetters());
						}
						else
						{
							System.out.println("Well done! Your letter was correct.");
							System.out.println("You have used: " + getLetters());
						}
					}
					catch (InputMismatchException e)
					{
						System.out.println("You must enter a single letter.");
						scan.next();
					}
				}
				if(choice == 2)
				{
					System.out.println("Please enter your guess (Include the punctuation shown!): ");
					String word = scan.nextLine();
					if(tryWord(word) == false)
					{
						System.out.println("Unlucky! Keep going.");
						System.out.println("You have "+ guessesLeft +" guesses left.");
					}
					else
					{
						System.out.println("Well done! Your word was correct.");
						break;
					}
				}
			}
			catch(InputMismatchException exc)
			{
				System.out.println("Please enter 1 or 2.");
				scan.next();
			}
		}
		while(currentLetters.contains("*")&&(guessesLeft > 0));
		boolean repeat = false;
		//This do while loop runs after the user has won or lost. It allows the user to play again if they wish.
		do{
			if(guessesLeft == 0)
			{
				try
				{
					System.out.println("Unlucky. You lose. The word was "+getHidden()+" Would you like to try again? Yes (Enter 1) or No? (Enter 2)");
					int choice = scan.nextInt();
					playAgain(choice);
					repeat = true;
				}
				catch(InputMismatchException e)
				{
					System.out.println("Please enter 1 or 2.");
					scan.next();
				}
			}
			else
			{
				try
				{
					System.out.println("Well done! You win!");
					System.out.println("Your score was: "+(10-guessesLeft)+".");
					System.out.println("Would you like to try again? Yes (Enter 1) or No? (Enter 2)");
					int choice = scan.nextInt();
					playAgain(choice);
					repeat = true;
				}
				catch(InputMismatchException e)
				{
					System.out.println("Please enter 1 or 2.");
					scan.next();
				}
			}
		}
		while(repeat == false);
	}	

	/*
	 * This method is used by the text-based version of the game to allow the user to play again.
	 * @param choice Takes user inputted integer restricted to a 1 or 2 to choose an option
	 */
	public void playAgain(int choice)
	{
		if(choice == 1)
		{
			resetGuesses();
			System.out.println("Good luck!");
			run();
		}
		else if(choice == 2)
		{
			System.out.println("Thanks for playing!");
			System.exit(0);
		}
	}
	
	/*
	 * This method allows the user to try a single character and see the letter placed in the output or guessesLeft to decrement.
	 * @param letter A user inputted character that they believe is in the chosen word.
	 * @return true if correct
	 * @return false if incorrect
	 */
	public boolean tryThis(char letter)
	{
		boolean check = false;
		for (int i=0; i<chosenWord.length(); i++)
		{
			char c = chosenWord.charAt(i);      
			if(c == letter)
			{
				char[] currentLettersChar = currentLetters.toCharArray();
				currentLettersChar[i] = c;
				currentLetters = String.valueOf(currentLettersChar);
				check = true;
			}
		}
		if(check)
		{
			guessedLetters.add(letter);
			return true;
		}
		else
		{
			guessesLeft = guessesLeft -1;
			guessedLetters.add(letter);
			return false;
		}
	}
	
	/*
	 * This method allows the user to guess the entire chosen phrase. If they get it right, they win, if not, guessesLeft 
	 * decrements by 5.
	 * @param word The user inputted phrase they wish to try.
	 * @return true if correct.
	 * @return false if incorrect.
	 */
	public boolean tryWord(String word)
	{
		if(word.equals(chosenWord))
		{
			return true;
		}
		else
		{
			guessesLeft = guessesLeft -5;
			return false;
		}
	}
	
	/*
	 * This method returns the chosen word for the current instance of the application.
	 * @return the chosen word.
	 */
	public String getHidden()
	{
		return chosenWord;
	}
	
	/*
	 * This method returns the guesses the user has left.
	 * @return the value of the current application instance's guessesLeft int variable.
	 */
	public int guessLeft()
	{
		return guessesLeft;
	}
	
	/*
	 * This method returns the contents of the guessedLetters ArrayList with a little formatting to separate each character.
	 * This uses StringBuilder to build a string from a set of chars.
	 * @return the toString of StringBuilder. 
	 */
	public String getLetters()
	{
		StringBuilder sb = new StringBuilder();
		for(char c : guessedLetters) 
		{
			sb.append(c + ", ");
		}
		return sb.toString();
	}
	
	/*
	 * This method returns what the user is supposed to see. After placeStars() has run, this method holds *'s equal to the
	 * length of the chosen word.
	 * @return the currently visible word for the user to guess, holding all correctly guessed letters.
	 */
	public String getVisible()
	{
		return currentLetters;
	}
	
	/*
	 * This method loads in a textfile of pirate words for the randomWord() method to choose one from.
	 * @param fileName This is the file name of the textfile loaded in. By default "piratewords.txt".
	 */
	public void loadWords(String fileName) throws IOException
	{
		boolean check = true;
		do
		{
			try
			{
				Scanner infile = new Scanner(new InputStreamReader
						(new FileInputStream(fileName)));
				int num = infile.nextInt(); infile.nextLine();
				for (int i=0; i<num; i++)
				{
					String word = infile.nextLine();
					WordsToGuess w = new WordsToGuess(word);
					words.add(w);
				}
				infile.close();
			}
			catch(IOException ex)
			{
				System.out.println("Could not find file");
				scan.next();
				check = false;
			}
		}
		while(check == false);
	}
	
	/*
	 * This method fetches a randomly chosen word using a random int from the size of the ArrayList words. It then finds an
	 * object at the index of that number, and uses toString() to convert into a string.
	 * @return The randomly chosen word.
	 */
	public String randomWord() 
    {
		int randomNo = randomGenerator.nextInt(words.size());
		String chosenWord = words.get(randomNo).toString();
		return chosenWord;
    }
	
	/*
	 * This method takes the chosen word and replaces all letters with *'s, leaving punctuation.
	 * @param wordToGuess The chosen word.
	 * @return The String containing the *'s for the chosen word.
	 */
	public String placeStars(String wordToGuess)
	{
		currentLetters = wordToGuess.replaceAll("[a-zA-Z]", "*");
		return currentLetters;
	}
	
	//Test Methods
	/*
	 * This method adds a word to the ArrayList words.
	 * @param w A WordsToGuess object to add.
	 */
	public void addWord(WordsToGuess w)
	{
		words.add(w);
	}
	
	/*
	 * This method adds a character to the ArrayList guessedLetters.
	 * @param c The character to add.
	 */
	public void addToGuessedLetters(char c)
	{
		guessedLetters.add(c);
	}
	
	/*
	 * This method checks the size of the ArrayList words.
	 * @return the size of the ArrayList words.
	 */
	public int checkWordsSize()
	{
		return words.size();
	}
	
	/*
	 * This method prints out all words in the ArrayList words.
	 */
	public void printWords()
	{
		System.out.println("Your loaded words are: ");
		for (WordsToGuess w: words)
		{
			System.out.println(w.getWord());
		}
	}
}
