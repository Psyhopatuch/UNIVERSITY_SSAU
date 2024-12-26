package functions;

import java.io.*;

public abstract class TabulatedFunctions
{
    public static TabulatedFunction tabulate(Function function, double leftX, double rightX, int pointsCount)
    {
        if(leftX < function.getLeftDomainBorder() || rightX > function.getRightDomainBorder())
        {
            throw new IllegalArgumentException("Cannot create TabulatedFunction: Left or right border out of the function's domain of definition");
        }
           double stepX = (rightX - leftX)/(pointsCount-1);
           double curX = leftX;
           FunctionPoint[] arr = new FunctionPoint[pointsCount];

           for(int i = 0; i < pointsCount; i++)
           {
               curX = leftX + stepX*i;
               arr[i] = new FunctionPoint(curX, function.getFunctionValue(curX)) ;
           }
           return new ArrayTabulatedFunction(arr);
    }
    public static void outputTabulatedFunction(TabulatedFunction function, OutputStream out)
    {
        try (DataOutputStream dout = new DataOutputStream(out))
        {
            int pointsCount = function.getPointsCount();
            dout.writeInt(pointsCount);
            for (int i = 0; i < pointsCount; i++)
            {
                dout.writeDouble(function.getPointX(i));
                dout.writeDouble(function.getPointY(i));
            }
        }
        catch (IOException ex)
        {
            System.out.println(ex.getMessage());
        }
    }
    public static TabulatedFunction inputTabulatedFunction(InputStream in)
    {
        try (DataInputStream din = new DataInputStream(in))
        {
            int pointsCount=din.readInt();
            FunctionPoint[] pointsArr = new FunctionPoint[pointsCount];
            for (int i = 0; i < pointsCount; i++)
            {
                pointsArr[i] = new FunctionPoint(din.readDouble(), din.readDouble());
            }
            return new ArrayTabulatedFunction(pointsArr);
        }
        catch (IOException ex)
        {
            System.out.println(ex.getMessage());
        }
        return null;
    }
    public static void writeTabulatedFunction(TabulatedFunction function, Writer out)
    {
        try (BufferedWriter bout = new BufferedWriter(out))
        {
            int pointsCount = function.getPointsCount();
            bout.write(String.valueOf(pointsCount) + " ");
            for (int i = 0; i < pointsCount; i++)
            {
                bout.write(function.getPointX(i) + " " + function.getPointY(i) + " ");
            }
        }
        catch (IOException ex)
        {
            System.out.println(ex.getMessage());
        }
        System.out.println();
    }
    public static TabulatedFunction readTabulatedFunction(Reader in)
    {
        try
        {
            StreamTokenizer sTok = new StreamTokenizer(in);
            sTok.nextToken();
            int pointsCount = (int) sTok.nval;
            FunctionPoint[] pointArr = new FunctionPoint[pointsCount];
            for (int i = 0; sTok.nextToken() != StreamTokenizer.TT_EOF; i++)
            {
                double x = sTok.nval;
                sTok.nextToken();
                pointArr[i] = new FunctionPoint(x, sTok.nval);
            }
            return new ArrayTabulatedFunction(pointArr);
        }
        catch (IOException ex)
        {
            System.out.println(ex.getMessage());
        }
        catch (IllegalArgumentException e)
        {
            e.printStackTrace();
        }
        return null;
    }
}