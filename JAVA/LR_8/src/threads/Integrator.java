package threads;

public class Integrator extends Thread
{
    private final Task task;
    private final Semaphore semaphore;


    public Integrator(Task task, Semaphore semaphore)
    {
        this.task = task;
        this.semaphore=semaphore;
    }

    @Override
    public void run()
    {
        try {
            int i = 0;
            while (task.getCounter() > 0)
            {
                semaphore.startReading();
                    System.out.printf("Result(%d): %f %f %f %f\n",
                            i++,
                            task.getMinX(),
                            task.getMaxX(),
                            task.getDClock(),
                            task.toWork());
                semaphore.finishReading();
            }
        }
        catch (IllegalMonitorStateException | InterruptedException e)
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
