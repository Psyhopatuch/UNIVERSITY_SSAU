import functions.*;
import functions.basic.*;
import threads.*;
import static java.lang.Thread.sleep;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main
{

    public static void main(String[] args)
    {
        TabulatedFunction f = TabulatedFunctions.createTabulatedFunction(ArrayTabulatedFunction.class,0,1,10);
        System.out.println(f.getClass());
        f = TabulatedFunctions.createTabulatedFunction(LinkedListTabulatedFunction.class,0,1,10);
        System.out.println(f.getClass());
    }

    private static void nonThread()
    {
        Task task = new Task();
        while (task.getCounter()>0)
        {
            task.updateRand();
            System.out.printf("Source: %f %f %f\n",
                    task.getMinX(),
                    task.getMaxX(),
                    task.getDClock());
            System.out.printf("Result: %f %f %f %f\n",
                    task.getMinX(),
                    task.getMaxX(),
                    task.getDClock(),
                    task.toWork());
        }
    }

    private static void simpleThread()
    {
        Task task=new Task();
        Thread generatorT = new Thread(new SimpleGenerator(task));
        Thread integratorT = new Thread(new SimpleIntegrator(task));
        generatorT.start();
        integratorT.start();
    }

    private static void complicatedThread()
    {
        Task task=new Task();
        Semaphore semaphore=new Semaphore();
        Thread generatorT = new Generator(task,semaphore);
        Thread integratorT = new Integrator(task,semaphore);
        generatorT.start();
        integratorT.start();

        try
        {
            sleep(50);
            generatorT.interrupt();
            integratorT.interrupt();
        }
        catch (InterruptedException e)
        {
            System.out.println(e.getMessage());
        }
    }
}