package functions.meta;

import functions.Function;

public class Scale implements Function
{
    double xScale;
    double yScale;
    Function ScaledFunc;

    public Scale(Function ScaledFunc, double xScale, double yScale)
    {
        this.ScaledFunc = ScaledFunc;
        this.xScale = xScale;
        this.yScale = yScale;
    }

    @Override
    public double getLeftDomainBorder()
    {
        return ScaledFunc.getLeftDomainBorder() * xScale;
    }

    @Override
    public double getRightDomainBorder()
    {
        return ScaledFunc.getRightDomainBorder() * xScale;
    }

    @Override
    public double getFunctionValue(double x)
    {
        return ScaledFunc.getFunctionValue(x * xScale) * yScale;
    }
}
