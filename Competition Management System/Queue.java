package uk.ac.aber.dcs.bpt.cs21120.assignment1;

public class Queue 
{
	Object[] queue;
	int head;
	int tail;
	int length;
	
	public Queue(int startSize)
	{
		queue = new Object[startSize];
		head = tail = length = 0;
	}
	
	// Adds an Object to the back of the queue. 
	 public void enQ(Object o)
	 {
		 if(length == queue.length)
		 {
			 //queue = new Object[queue.length * 2];
		 }
		 queue[tail++] = o;
		 length++;
		 if(tail == queue.length)
		 {
			 tail = 0;
		 }
	 }
	 
	 // Takes an Object from the front of the queue. 
	 public Object deQ() throws QueueEmptyException
	 {
		 if(isEmpty()) throw new QueueEmptyException();
		 Object o = queue[head];
		 queue[head] = null;
		 head++;
		 if(head == queue.length)
		 {
			 head = 0;
		 }
		 length--;
		 return o;
	 }
	 
	 // Inspects the Object at the front of the queue. 
	 public Object front() throws QueueEmptyException
	 {
		 if (isEmpty()) throw new QueueEmptyException();
		 return queue[head];
	 }
	 //Returns the size of the queue 
	 public int length()
	 {
		 return length;
	 }
	 // Checks if the queue is empty 
	 public boolean isEmpty()
	 {
		 return length == 0;
	 }
	 // Remove all objects from the queue 
	 public void clear()
	 {
		 length = 0;
		 queue = new Object[queue.length];
		 head = tail = 0;
	 }
}
