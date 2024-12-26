import functions.FunctionPoint;
import functions.TabulatedFunction;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args)
    {
        double[] arr=new double[5];
        for(int i=0;i<arr.length;i++){
            arr[i]=Math.random();
        }
        TabulatedFunction function=new TabulatedFunction(-2,2,arr);
        for(int i=0;i<arr.length;i++){
            System.out.println(") x:" + i + "; y: " + function.getPointY(i) + ";");
        }
        function.deletePoint(3);
        for(int i=0;i< function.getPointsCount();i++){
            System.out.println(") x:" + i + "; y: " + function.getPointY(i) + ";");
        }
    }
}