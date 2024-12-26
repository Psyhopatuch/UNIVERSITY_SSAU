package functions.meta;

import functions.Function;

public class Composition implements Function
{
    Function externalFunction;
    Function innerFunction;
    public Composition(Function f1, Function f2)
    {
        externalFunction =f1;
        innerFunction =f2;
    }

    @Override
    public double getLeftDomainBorder()
    {
        return externalFunction.getLeftDomainBorder();
    }

    @Override
    public double getRightDomainBorder()
    {
        return externalFunction.getRightDomainBorder();
    }

    @Override
    public double getFunctionValue(double x){
        return externalFunction.getFunctionValue(innerFunction.getFunctionValue(x));
    }
}
