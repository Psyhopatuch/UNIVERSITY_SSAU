import functions.*;


//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) throws InappropriateFunctionPointException
    {
        double[] arr={-25,-5,0,5,25};
       TabulatedFunction function1=new ArrayTabulatedFunction(0,7,arr);
       TabulatedFunction function2=new LinkedListTabulatedFunction(0,7,arr);
        FunctionPoint newPoint=new FunctionPoint(6,36);
        function1.addPoint(newPoint);
        function2.addPoint(newPoint);

        boolean temp=true;
       for(int i=0;i<function1.getPointsCount();i++)
       {

           if(function1.getPointY(i)!=function2.getPointY(i)||function1.getPointX(i)!=function2.getPointX(i))
               temp=false;

       }
        System.out.println(temp);
    }
}