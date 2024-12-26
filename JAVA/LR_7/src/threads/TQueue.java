package threads;

public class TQueue<T>
{
    public class Container
    {
        Container prev;
        T object;
        Container next;
        private Container(){}
        private Container(Container prev, T object, Container next)
        {
            this.prev = prev;
            this.object = object;
            this.next = next;
        }
    }

    private final Container head;
    private int counter;
    private int size;


    public TQueue(int counter)
    {
        head = new Container();
        head.prev = head;
        head.next = head;
        this.counter = counter;
        this.size = 0;
    }

    public void push(T obj)
    {
        if (obj==null) throw new NullPointerException("TQueue: Object cannot be null");
       Container temp = new Container(head, obj, head.next);
       head.next.prev = temp;
       head.next = temp;
       if(head.prev == head)
           head.prev = temp;
       size++;
       counter--;
    }

    public T pop()
    {
        if(head.prev == head) throw new IllegalStateException("TQueue is empty");
        Container temp = head.prev;
        head.prev = head.prev.prev;
        head.prev.next = head;
        size--;
        return temp.object;
    }

    public void setCounter(int counter) {
        this.counter = counter;
    }

    public int getCounter()
    {
        return counter;
    }

    public int getSize()
    {
        return size;
    }

}
