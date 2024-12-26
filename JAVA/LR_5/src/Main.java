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
        double[] arr= {0,1,2,3,4,5,6,7,8,9,10};
        double[] arr2= {10,9,8,7,6,5,4,3,2,1,0};
        TabulatedFunction tabF1 = new LinkedListTabulatedFunction(0, 10, arr);
        TabulatedFunction tabF2 = new ArrayTabulatedFunction(0, 10, arr);
        try
        {
            TabulatedFunction cloneTabF1=(TabulatedFunction) tabF1.clone();
            TabulatedFunction cloneTabF2=(TabulatedFunction) tabF2.clone();
            cloneTabF1.deletePoint(4);
            cloneTabF2.deletePoint(2);
            System.out.println(tabF1.toString()+"/n");
            System.out.println(tabF2.toString());
        }
        catch(CloneNotSupportedException e)
        {
            e.getMessage();
        }
    }
}
