package functions.basic;

import functions.Function;

public abstract class TrigonometricFunction implements Function
{
    public final double getLeftDomainBorder()
    {
        return Double.NEGATIVE_INFINITY;
    }
    public final double getRightDomainBorder()
    {
        return Double.POSITIVE_INFINITY;
    }
    public abstract double getFunctionValue(double x);
}
