package functions;

 public interface TabulatedFunction {
    
    //TF's METHODS (ArrayTabulatedFunction's methods)
     double getLeftDomainBorder();
     double getRightDomainBorder();

     double getFunctionValue(double x);


     int getPointsCount();

     FunctionPoint getPoint(int index);

     double getPointX(int index);

     void setPointX(int index, double x)throws InappropriateFunctionPointException;

     double getPointY(int index);

     void setPointY(int index, double y);

     void addPoint(FunctionPoint point) throws InappropriateFunctionPointException;

     void deletePoint(int index);
}
