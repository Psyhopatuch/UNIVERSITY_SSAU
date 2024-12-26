package functions.basic;

import functions.Function;

public class Log implements Function
{
    private final double logBase;
    public Log(double logBase){this.logBase = logBase;}

    @Override
    public double getLeftDomainBorder()
    {
        return 0;
    }

    @Override
    public double getRightDomainBorder()
    {
        return Double.POSITIVE_INFINITY;
    }

    @Override
    public double getFunctionValue(double x)
    {
        return Math.log(x)/Math.log(logBase);
    }
}
