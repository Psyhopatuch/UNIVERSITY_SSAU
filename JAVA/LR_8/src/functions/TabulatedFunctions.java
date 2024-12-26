package functions;

import java.io.*;
import java.lang.reflect.Constructor;

public abstract class TabulatedFunctions
{
    private static TabulatedFunctionFactory factory = new ArrayTabulatedFunction.ArrayTabulatedFunctionFactory();

    public static void setTabulatedFunctionFactory(TabulatedFunctionFactory f)
    {
        factory = f;
    }

    public static TabulatedFunction createTabulatedFunction(double leftX, double rightX, int pointsCount)
    {
        return factory.createTabulatedFunction(leftX, rightX, pointsCount);
    }
    public static TabulatedFunction createTabulatedFunction(double leftX, double rightX, double[] values)
    {
        return factory.createTabulatedFunction(leftX, rightX, values);
    }
    public static TabulatedFunction createTabulatedFunction(FunctionPoint[] arr)
    {
        return factory.createTabulatedFunction(arr);
    }

    public static TabulatedFunction createTabulatedFunction(Class<?extends TabulatedFunction> TBClass, double leftX, double rightX, int pointsCount)
    {
        try
        {
            Constructor<?> constr=TBClass.getConstructor(double.class, double.class, int.class);
            return (TabulatedFunction) constr.newInstance(leftX, rightX, pointsCount);
        }
        catch (Exception e)
        {
            throw new IllegalArgumentException(e);
        }
    }
















    public static TabulatedFunction createTabulatedFunction(Class<?extends TabulatedFunction> TBClass, double leftX, double rightX, double[] arr)
    {
        try
        {
            Constructor<?extends TabulatedFunction> constr = TBClass.getConstructor(double.class, double.class, double[].class);
            return (TabulatedFunction) constr.newInstance(leftX, rightX, arr);
        }
        catch (Exception e)
        {
            throw new IllegalArgumentException(e);
        }
    }

    public static TabulatedFunction createTabulatedFunction(Class<?extends TabulatedFunction> TBClass, FunctionPoint[] arr)
    {
        try
        {
            Constructor<?extends TabulatedFunction> constr = TBClass.getConstructor(FunctionPoint[].class);
            return constr.newInstance((Object) arr);
        }
        catch (Exception e)
        {
            throw new IllegalArgumentException(e);
        }
    }


    public static TabulatedFunction tabulate(Function function, double leftX, double rightX, int pointsCount)
    {
        if(leftX < function.getLeftDomainBorder() || rightX > function.getRightDomainBorder())
        {
            throw new IllegalArgumentException("Cannot create TabulatedFunction: Left or right border out of the function's domain of definition");
        }
           double stepX = (rightX - leftX)/(pointsCount - 1);
           double curX = leftX;
           FunctionPoint[] arr = new FunctionPoint[pointsCount];

           for(int i = 0; i < pointsCount; i++)
           {
               curX = leftX + stepX*i;
               arr[i] = new FunctionPoint(curX, function.getFunctionValue(curX)) ;
           }
           return createTabulatedFunction(arr);
    }

    public static TabulatedFunction tabulate(Class<?extends TabulatedFunction> TBClass, Function function, double leftX, double rightX, int pointsCount)
    {
        if(leftX < function.getLeftDomainBorder() || rightX > function.getRightDomainBorder())
        {
            throw new IllegalArgumentException("Cannot create TabulatedFunction: Left or right border out of the function's domain of definition");
        }
        double stepX = (rightX - leftX)/(pointsCount - 1);
        double curX = leftX;
        FunctionPoint[] arr = new FunctionPoint[pointsCount];

        for(int i = 0; i < pointsCount; i++)
        {
            curX = leftX + stepX*i;
            arr[i] = new FunctionPoint(curX, function.getFunctionValue(curX)) ;
        }
        return createTabulatedFunction(TBClass, arr);
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
            return createTabulatedFunction(pointsArr);
        }
        catch (IOException ex)
        {
            System.out.println(ex.getMessage());
        }
        return null;
    }

    public static TabulatedFunction inputTabulatedFunction(Class<?extends TabulatedFunction> TBClass, InputStream in)
    {
        try (DataInputStream din = new DataInputStream(in))
        {
            int pointsCount=din.readInt();
            FunctionPoint[] pointsArr = new FunctionPoint[pointsCount];
            for (int i = 0; i < pointsCount; i++)
            {
                pointsArr[i] = new FunctionPoint(din.readDouble(), din.readDouble());
            }
            return createTabulatedFunction(TBClass, pointsArr);
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
            return createTabulatedFunction(pointArr);
        }
        catch (IOException ex)
        {
            System.out.println(ex.getMessage());
        }
        catch (IllegalArgumentException e)
        {
            System.out.println(e.getMessage());
        }
        return null;
    }
}