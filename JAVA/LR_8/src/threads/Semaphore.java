package threads;

public class Semaphore
{
    private boolean readyUpgrade = true;


    public synchronized void startWriting() throws InterruptedException
    {
        if (!readyUpgrade)
            wait();
    }

    public synchronized void finishWriting()
    {
        readyUpgrade = false;
        notify();
    }

    public synchronized void startReading() throws InterruptedException
    {
        if(readyUpgrade)
            wait();
    }

    public synchronized void finishReading()
    {
        readyUpgrade = true;
        notify();
    }

    public boolean getStatus()
    {
        return readyUpgrade;
    }

}
