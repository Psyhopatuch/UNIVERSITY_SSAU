package threads;

public class Generator extends Thread
{
    private final Task task;
    private final Semaphore semaphore;


    public Generator(Task task,Semaphore semaphore)
    {
        this.task = task;
        this.semaphore = semaphore;
    }

    @Override
    public void run()
    {
        try
        {
            int i = 0;
            while ((task.getCounter() > 0) && (!isInterrupted()))
            {
                semaphore.startWriting();
                task.updateRand();
                System.out.printf("Source(%d): %f %f %f\n",
                        i,
                        task.getMinX(),
                        task.getMaxX(),
                        task.getDClock());
                    i++;
                semaphore.finishWriting();
            }
        }
        catch(Exception e)
        {
            System.out.println("INTERRUPTED");
        }
    }

    @Override
    public void interrupt()
    {
        super.interrupt();
    }
}
