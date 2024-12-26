package functions.meta;

import functions.Function;

public class Shift implements Function
{
    double xShift;
    double yShift;
    Function ShiftedFunc;

    public Shift(Function ShiftedFunc, double xShift, double yShift)
    {
        this.ShiftedFunc = ShiftedFunc;
        this.xShift = xShift;
        this.yShift = yShift;
    }

    @Override
    public double getLeftDomainBorder()
    {
        return ShiftedFunc.getLeftDomainBorder() + xShift;
    }

    @Override
    public double getRightDomainBorder()
    {
        return ShiftedFunc.getRightDomainBorder() + xShift;
    }

    @Override
    public double getFunctionValue(double x)
    {
        return ShiftedFunc.getFunctionValue(x + xShift) + yShift;
    }
}
