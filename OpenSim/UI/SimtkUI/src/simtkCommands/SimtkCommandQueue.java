package simtkCommands;

import java.util.LinkedList;
import java.util.Observable;

/**
 * <p>Title: UI for Simtk Prototype</p>
 *
 * <p>Description: UI for Simtk Prototype</p>
 *
 * <p>Copyright: Copyright (c) 2004</p>
 *
 * <p>Company: Stanford University</p>
 * Implementation of a Queue to support command processing. The underlying
 * datastructure is actually a LinkedList. This list is NOT SYNCHRONIZIED
 */
public class SimtkCommandQueue extends Observable{
  private LinkedList queue;

  public SimtkCommandQueue() {
    queue = new LinkedList();
  }
  public void enQueue(Object obj) {
    synchronized(this){
      queue.addLast(obj);
    }
    this.setChanged();
    notifyObservers();
  }
  public Object deQueue() {
    return queue.removeFirst();
  }

  public boolean hasMoreCommands()
  {
    boolean hasMore = false;
    synchronized(this){
      hasMore = (!queue.isEmpty());
    }
    return hasMore;
  }
}
