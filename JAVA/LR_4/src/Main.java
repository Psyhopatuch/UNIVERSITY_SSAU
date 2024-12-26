import functions.*;
import functions.basic.Cos;
import functions.basic.Exp;
import functions.basic.Log;
import functions.basic.Sin;
import functions.meta.Sum;

import java.io.*;
import java.nio.channels.ScatteringByteChannel;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) throws InappropriateFunctionPointException
    {
        Function exp = new Exp();
        TabulatedFunction tabExp=TabulatedFunctions.tabulate(exp,0,10,11);
        try(ObjectOutputStream oout=new ObjectOutputStream(new FileOutputStream("output.txt")))
        {
            oout.writeObject(tabExp);
            ObjectInputStream oin=new ObjectInputStream(new FileInputStream("output.txt"));
            TabulatedFunction readTabExp=(TabulatedFunction)oin.readObject();
            for(int i=0;i< readTabExp.getPointsCount();i++)
                System.out.println(readTabExp.getPointX(i)+" "+readTabExp.getPointY(i));
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

    }
}
