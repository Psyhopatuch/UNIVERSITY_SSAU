package functions;

import java.io.Serializable;

public interface TabulatedFunction extends Function, Cloneable, Serializable
 {
    
    //TF's METHODS (ArrayTabulatedFunction's methods)

     int getPointsCount();

     FunctionPoint getPoint(int index);

     double getPointX(int index);

     void setPointX(int index, double x)throws InappropriateFunctionPointException;

     double getPointY(int index);

     void setPointY(int index, double y);

     void addPoint(FunctionPoint point) throws InappropriateFunctionPointException;

     void deletePoint(int index);

     Object clone() throws CloneNotSupportedException;
}
