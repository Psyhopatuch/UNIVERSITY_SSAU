package functions.meta;

import functions.Function;

public class Sum implements Function
{
    Function Function1;
    Function Function2;
    public Sum(Function f1, Function f2)
    {
        Function1=f1;
        Function2=f2;
    }

    @Override
    public double getLeftDomainBorder()
    {
        return Function1.getLeftDomainBorder()<Function2.getLeftDomainBorder()?
                Function2.getLeftDomainBorder():Function1.getLeftDomainBorder();
    }

    @Override
    public double getRightDomainBorder()
    {
        return Function1.getRightDomainBorder()<Function2.getRightDomainBorder()?
                Function1.getRightDomainBorder():Function2.getRightDomainBorder();
    }

    @Override
    public double getFunctionValue(double x){
        return Function1.getFunctionValue(x)+Function2.getFunctionValue(x);
    }
}
