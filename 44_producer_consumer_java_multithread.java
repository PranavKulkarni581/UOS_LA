import java.util.*;
class BoundedBuffer {
    private final Queue<Integer> q = new LinkedList<>();
    private final int capacity;
    public BoundedBuffer(int cap){ capacity=cap; }
    public synchronized void produce(int v) throws InterruptedException {
        while(q.size()==capacity) wait();
        q.add(v); notifyAll();
    }
    public synchronized int consume() throws InterruptedException {
        while(q.isEmpty()) wait();
        int v=q.remove(); notifyAll(); return v;
    }
}
class Producer implements Runnable {
    BoundedBuffer b; int id;
    Producer(BoundedBuffer b,int id){ this.b=b; this.id=id; }
    public void run(){
        try{ for(int i=0;i<10;i++){ b.produce(i); System.out.println("P"+id+" produced "+i); Thread.sleep(200);} }catch(Exception e){}
    }
}
class Consumer implements Runnable {
    BoundedBuffer b; int id;
    Consumer(BoundedBuffer b,int id){ this.b=b; this.id=id; }
    public void run(){
        try{ for(int i=0;i<10;i++){ int v=b.consume(); System.out.println("C"+id+" consumed "+v); Thread.sleep(400);} }catch(Exception e){}
    }
}
public class producer_consumer_mt {
    public static void main(String[] args){
        BoundedBuffer b = new BoundedBuffer(5);
        new Thread(new Producer(b,1)).start();
        new Thread(new Producer(b,2)).start();
        new Thread(new Consumer(b,1)).start();
        new Thread(new Consumer(b,2)).start();
    }
}
