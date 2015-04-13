package cs21120.assignment2.solution;

import cs21120.assignment2.FloatImage;
import cs21120.assignment2.ISnapper;

import java.awt.Point;
import java.util.LinkedList;
import java.util.concurrent.PriorityBlockingQueue;


/**
 * This class implements the ISnapper interface from the .jar file CS21120-A2.jar
 * setSeed and getPath are implemented from the above mentioned interface.
 * mapBuilding method implements Dijkstra's shortest path algorithm.
 * I ran into an issue where the drawn line would disappear under certain circumstances. Still unresolved.
 *
 * @author Max Thomas Atkins (mta2)
 */
public class Mta2Snapper implements ISnapper
{
    //Global Variables
    private FloatImage[] fi;
    private boolean[][] nodesVisited;
    private Point[][] map;

    /**
     * This method sets the seed/start point from the current mouse position. It runs the thread to build the map.
     * @param x is the x co-ordinate of the current position
     * @param y is the y co-ordinate of the current position
     * @param neighbourEdges is an array of four FloatImages that contain node weights -- 0 = East, 1 = NorthEast,
     *                    2 = North, 3 = NorthWest
     */
    public void setSeed(int x, int y, FloatImage[] neighbourEdges)
    {
        fi = neighbourEdges; //Copy the passed array into array for this class
        int imageHeight = fi[0].getHeight(), imageWidth = fi[0].getWidth();
        final PriorityBlockingQueue<Edge> q = new PriorityBlockingQueue<Edge>();
        nodesVisited = new boolean[imageWidth][imageHeight]; //Make nodesVisited array size of image
        map = new Point[imageWidth][imageHeight]; //Make map array size of image
        q.add(new Edge(null, new Point(x,y), 0));

        //Instantiate Runnable for building the map continuously
        Runnable running = new Runnable()
        {
            @Override
            public void run()
            {
                mapBuilding(q);
            }
        };
        //Instantiate a thread with running Runnable
        Thread go = new Thread(running);
        go.start();
    }

    /**
     * This method gets the estimated shortest path as decided by mapBuilding method from the passed  point to the seed
     * point
     * @param x is the x co-ordinate of the passed position
     * @param y is the y co-ordinate of the passed position
     * @return a linked list of chosen points for the estimated shortest path
     */
    public LinkedList<Point> getPath(int x, int y)
    {
        //If the co-ords are not out of bounds
        if(checkInBounds(x, y))
        {
            //If the co-ords have been visited
            if(nodesVisited[x][y])
            {
                LinkedList<Point> allNodes = new LinkedList<Point>();
                Point nextNode = map[x][y];
                //Loop through linked list
                while(nextNode != null)
                {
                    allNodes.add(new Point(nextNode));
                    nextNode = map[nextNode.x][nextNode.y];
                }
                return allNodes;
            }
            else
            {
                return null;
            }
        }
        else
        {
            return null;
        }

    }

    /**
     * Chooses nodes along the shortest path from the current node to the seed node.
     * This is from Dijkstra's shortest path algorithm
     * @param q is the priority blocking queue used to hold edges
     */
    private void mapBuilding(PriorityBlockingQueue<Edge> q) {
        float weight;
        Edge newEdge;
        //Try catch block to catch interrupted exceptions
        try {
            //While the queue is not empty
            while (!q.isEmpty())
            {
                Edge currentEdge = q.take();
                int endX = currentEdge.end.x, endY = currentEdge.end.y;
                //Move onto next iteration if co-ords out of bounds
                if (!checkInBounds(endX, endY))
                {
                    continue;
                }
                //Move onto next iteration if node is visited
                if (nodesVisited[endX][endY])
                {
                    continue;
                }
                //Set visited flag to true (Dijkstra's Algorithm step)
                nodesVisited[endX][endY] = true;
                //Set map value to edge's to start point (Dijkstra's Algorithm step)
                map[endX][endY] = currentEdge.start;

                //Add target point's edges (Dijkstra's Algorithm step)
                //Add the eastern node as a neighbour
                weight = fi[0].get_nocheck(endX, endY);
                newEdge = new Edge(new Point(endX, endY), new Point(endX + 1,
                        endY), weight + currentEdge.weight);
                q.add(newEdge);

                //Add the north-eastern node as a neighbour
                weight = fi[1].get_nocheck(endX, endY);
                newEdge = new Edge(new Point(endX, endY), new Point(endX + 1,
                        endY + 1), weight + currentEdge.weight);
                q.add(newEdge);

                //Add the northern node as a neighbour
                weight = fi[2].get_nocheck(endX, endY);
                newEdge = new Edge(new Point(endX, endY), new Point(endX,
                        endY + 1), weight + currentEdge.weight);
                q.add(newEdge);

                //Add the north-western node as a neighbour
                weight = fi[3].get_nocheck(endX, endY);
                newEdge = new Edge(new Point(endX, endY), new Point(endX - 1,
                        endY + 1), weight + currentEdge.weight);
                q.add(newEdge);

                //Check inverse directions are not out of bounds
                if (checkInBounds(endX - 1, endY) //Western
                        && checkInBounds(endX - 1, endY - 1) // South-western
                        && checkInBounds(endX, endY - 1) //Southern
                        && checkInBounds(endX + 1, endY - 1)) // South-eastern
                {
                    //Add the western node as a neighbour
                    weight = fi[0].get_nocheck(endX - 1, endY);
                    newEdge = new Edge(new Point(endX, endY), new Point(endX - 1,
                            endY), weight + currentEdge.weight);
                    q.add(newEdge);

                    //Add the south-western node as a neighbour
                    weight = fi[1].get_nocheck(endX - 1, endY - 1);
                    newEdge = new Edge(new Point(endX, endY), new Point(endX - 1,
                            endY - 1), weight + currentEdge.weight);
                    q.add(newEdge);

                    //Add the southern node as a neighbour
                    weight = fi[2].get_nocheck(endX, endY - 1);
                    newEdge = new Edge(new Point(endX, endY), new Point(endX,
                            endY - 1), weight + currentEdge.weight);
                    q.add(newEdge);

                    //Add the south-eastern node as a neighbour
                    weight = fi[3].get_nocheck(endX + 1, endY - 1);
                    newEdge = new Edge(new Point(endX, endY), new Point(endX + 1,
                            endY - 1), weight + currentEdge.weight);
                    q.add(newEdge);
                }
            }
        }
        //Catch interrupted exception
        catch (InterruptedException ie)
        {
            ie.printStackTrace();
        }
    }

    /**
     * Method to check if co-ordinates are out of bounds
     * @param x is the x co-ordinate to check
     * @param y is the y co-ordinate to check
     * @return true if co-ordinates are out of bounds, false if not
     */
    private boolean checkInBounds(int x, int y)
    {
        return x < map.length
                && y < map[0].length
                && x >= 0
                && y >= 0
                ;
    }

    /**
     * Inner class representing an Edge. This holds a start point, an end point and a weight.
     * This implements the Comparable to allow for comparing of two Edges.
     */
    private class Edge implements Comparable<Edge>
    {
        private Point start, end;
        private float weight;

        //Constructor
        public Edge(Point s, Point e, float w)
        {
            this.start = s;
            this.end = e;
            this.weight = w;
        }

        /**
         * Required by Comparable
         * Compares this Edge to a passed edge.
         * @param e is an Edge to compare to this Edge
         * @return An int to say whether this Edge's weight is greater than, less than or equal to passed Edge
         */
        public int compareTo(Edge e)
        {
            if(this.weight > e.weight)
            {
                return 1;
            }
            else if (this.weight < e.weight)
            {
                return -1;
            }
            else
            {
                return  0;
            }
        }
    }
}
