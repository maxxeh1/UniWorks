package testing;

import static org.junit.Assert.*;

import java.io.IOException;

import org.junit.Before;
import org.junit.Test;

import model.*;

public class HangmanModelTest
{
	private HangmanModel model;
	private WordsToGuess word;
	
	@Before
	public void setUp()
	{
		model = new HangmanModel();
		word = new WordsToGuess();
	}
	
	/*@Test
	public void addWordAndChoose()
	{
		WordsToGuess testWord = new WordsToGuess("ahoy");
		model.addWord(testWord);
		
		word.setWord("ahoy");
		WordsToGuess foundWord = word;
		assertSame("Not found the word", testWord, foundWord);
	}*/
	
	@Test 
	public void addWordAndPlaceStars()
	{
		String testWord = "ahoy";
		String stars = model.placeStars(testWord);
		assertEquals("Not replaced", stars, "****");
	}
	
	@Test
	public void addToGuessLetters()
	{
		char one = 'a';
		char two = 'b';
		model.addToGuessedLetters(one);
		model.addToGuessedLetters(two);
		assertEquals("Not entered", model.getLetters(), "a, b, ");
	}
	
	@Test
	public void loadFileAndCheck() throws IOException
	{
		model.loadWords("piratewords.txt");
		int check = model.checkWordsSize();
		assertEquals("Not the same size", check, 20);
	}
	
	@Test
	public void tryThis()
	{
		WordsToGuess testWord = new WordsToGuess("ahoy");
		model.addWord(testWord);
		model.setup();
		
		assertTrue("Not true", model.tryThis('a'));
	}
	
	@Test
	public void tryThisIncorrect()
	{
		WordsToGuess testWord = new WordsToGuess("ahoy");
		model.addWord(testWord);
		model.setup();
		
		assertFalse("Not true", model.tryThis('b'));
	}
	
	@Test
	public void tryWord()
	{
		WordsToGuess testWord = new WordsToGuess("ahoy");
		model.addWord(testWord);
		model.setup();
		assertTrue("Not true", model.tryWord("ahoy"));
	}
	
	@Test
	public void tryWordIncorrect()
	{
		WordsToGuess testWord = new WordsToGuess("ahoy");
		model.addWord(testWord);
		model.setup();
		assertFalse("Not true", model.tryWord("pirate"));
	}

}
