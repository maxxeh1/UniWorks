package uk.ac.aber.dcs.bpt.cs21120.assignment1;

public class QueueEmptyException extends RuntimeException 
{ 
	public QueueEmptyException() 
	{ 
		super("Attempt to access empty Queue"); 
	} 
}