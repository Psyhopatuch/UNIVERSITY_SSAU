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
}
