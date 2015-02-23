package uk.ac.aber.dcs.bpt.cs21120.assignment1;

import java.util.ArrayList;

public class DoubleQueue implements IManager
{

	private Queue winnerQueue;
	private Queue loserQueue;
	private Match current;
	private boolean winQueue;
		
	public DoubleQueue()
	{
		winnerQueue = new Queue(5);
		loserQueue = new Queue(5);
	}
	/**
	 * Set the players or teams to use in the competition
	 * @param players the players or teams
	 */
	public void setPlayers(ArrayList<String> players)
	{
		for(String player : players)
		{
			winnerQueue.enQ(player);
		}
	}
	    
	/**
	 * Return true if there is another match in the competition that can be fetched using nextMatch
	 * @return returns true if the competition is still going
	 */
	public boolean hasNextMatch()
	{
		if(winnerQueue.length() > loserQueue.length())
		{
			return winnerQueue.length() > 1;
		}
		else
		{
			return loserQueue.length() > 1;
		}
	}
	    
	/**
	 * Returns the nextMatch to play
	 * @return returns the next match
	 * @throws NoNextMatchException if the competition is over and no more matches
	 */
	public Match nextMatch() throws NoNextMatchException
	{
		if(winnerQueue.length() > loserQueue.length())
		{
			String player1 = (String)winnerQueue.deQ();
			String player2 = (String)winnerQueue.deQ();
			current = new Match(player1, player2);
			winQueue = true;
			return current;
		}
		else
		{
			String player1 = (String)loserQueue.deQ();
			String player2 = (String)loserQueue.deQ();
			current = new Match(player1, player2);
			winQueue = false;
			return current;
		}
	}
	    
	/** Sets the winner for the last retrieved Match
	 * 
	 * @param player1 should be true if player1 won the match, otherwise false
	 */
	public void setMatchWinner(boolean player1)
	{
		if(winQueue)
		{
			if(player1)
			{
				winnerQueue.enQ(current.player1);
				loserQueue.enQ(current.player2);
			}
			else
			{
				winnerQueue.enQ(current.player2);
				loserQueue.enQ(current.player1);
			}
		}
		else
		{
			if(player1)
			{
				loserQueue.enQ(current.player1);
			}
			else
			{
				loserQueue.enQ(current.player2);
			}
		}
		
		
	}
	    
	/** 
	 * Get the name of the player/team that finished in position n.  
	 * The returned value should be null if the competition is still running, or if the competition hasn't
	 * determined who came in place n.  e.g. a single elimination competition can only (validly) return the
	 * winner (n=0).
	 * @param n the position to return
	 * @return returns the name of the team/player, or null if competition still running or n too large
	 */
	public String getPosition(int n)
	{
		if(hasNextMatch())
		{
			return null;
		}
		else
		{
			if(n == 0) return (String)winnerQueue.front();
			else return (String)loserQueue.front();
		}
	}
}
	
	
