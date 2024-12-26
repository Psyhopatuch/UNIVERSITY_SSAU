package functions;

import functions.meta.*;

public abstract class Functions
{
    public static Function composition(Function f1, Function f2)
    {
        return new Composition(f1, f2);
    }
    public static Function mult(Function f1, Function f2)
    {
        return new Mult(f1, f2);
    }
    public static Function scale(Function f, double scaleX, double scaleY)
    {
        return new Scale(f, scaleX, scaleY);
    }
    public static Function shift(Function f, double shiftX, double shiftY)
    {
        return new Shift(f, shiftX, shiftY);
    }
    public static Function sum(Function f1, Function f2)
    {
        return new Sum(f1, f2);
    }
    public static double integral(Function f, double minX, double maxX, double dClock)
    {
        if(minX < f.getLeftDomainBorder() || maxX > f.getRightDomainBorder())
        {
            throw new IllegalArgumentException("Cannot create TabulatedFunction: Left or right border out of the function's domain of definition");
        }
        double summ = 0;
        double curX = minX;
        while (curX+dClock <= maxX)
        {
            summ += dClock * ((f.getFunctionValue(curX) + f.getFunctionValue(curX+=dClock)) / 2);
        }
        summ+=(maxX - curX) * ((f.getFunctionValue(curX) + f.getFunctionValue(maxX)) / 2);
        return summ;
    }
}
