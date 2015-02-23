package model;

public class WordsToGuess 
{
	private String word;
	
	/*
	 * Default constructor
	 */
	public WordsToGuess()
	{
		word = "unknown";
	}
	
	/*
	 * Constructor to take arguments
	 * @param w The string to add as a WordsToGuess object.
	 */
	public WordsToGuess(String w)
	{
		word = w;
	}
	
	/*
	 * This method sets the object's word value.
	 * @param newWord the string to change the word value to.
	 */
	public void setWord(String newWord)
	{
		word = newWord;
	}
	
	/*
	 * This method returns the value of the word variable of this object.
	 * @return the object's word value.
	 */
	public String getWord()
	{
		return word;
	}
	
	/*
	 * toString() method to return word value.
	 * @return the object's word value.
	 */
	public String toString()
	{
		return word;
	}
}
