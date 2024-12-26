package functions;

import java.io.*;

public class ArrayTabulatedFunction implements TabulatedFunction, Externalizable
{
    //Class's vars
    private FunctionPoint[] pointArr;
    private int pointsCount;

    //Class's constructors
    public ArrayTabulatedFunction() {}

    @Override
    public void writeExternal(ObjectOutput oout) throws IOException {
        oout.writeInt(pointsCount);
        for(int i=0; i<pointsCount; i++)
        {
           oout.writeDouble(pointArr[i].getX());
            oout.writeDouble(pointArr[i].getY());
        }
    }

    @Override
    public void readExternal(ObjectInput oin) throws IOException, ClassNotFoundException
    {
        pointsCount=oin.readInt();
        pointArr=new FunctionPoint[pointsCount*2];
        for(int i=0; i<pointsCount; i++)
        {
            pointArr[i]=new FunctionPoint(oin.readDouble(),oin.readDouble());
        }
    }

    public ArrayTabulatedFunction(double leftX, double rightX, int pointsCount)
    {
        this(leftX,rightX, new double[pointsCount]);
    }

    public ArrayTabulatedFunction(double leftX, double rightX, double[] values)
    {
        if(leftX >= rightX)
        {
            throw new IllegalArgumentException("Cannot create TabulatedFunction: Left x should be greater than right x");
        }
        if (values.length < 2)
        {
            throw new IllegalArgumentException("Cannot create TabulatedFunction: Number of values should be at least 2");
        }
        pointArr = new FunctionPoint[values.length * 2];
        pointsCount = values.length;
        double stepX = (rightX-leftX) / (pointsCount - 1);

        for (int i=0; i < pointsCount; i++)
        {
            //System.out.println(i + ")" + " CurX = " + curX);
            pointArr[i] = new FunctionPoint(leftX + stepX * i, values[i]);
        }
    }

    public ArrayTabulatedFunction(FunctionPoint[] objects)
    {
        int i = objects.length - 1;
        while(i > 0 && objects[i].getX() < objects[--i].getX());
        if(i <= 0)
        {
            throw new IllegalArgumentException("Cannot create TabulatedFunction: Left x should be greater than right x or number of values should be at least 2");
        }
        this.pointArr = objects;
        pointsCount = objects.length;
    }

    //Class's set and get methods
    public double getLeftDomainBorder()
    {
       return pointArr[0].getX();
    }

    public double getRightDomainBorder()
    {
        return pointArr[pointsCount-1].getX();
    }

    public double getFunctionValue(double x)
    {
        if(x>getRightDomainBorder()||x<getLeftDomainBorder())
            return Double.NaN;
        int i=0;
        while(pointArr[i].getX() <= x && i < this.getPointsCount() - 1){i++;}
        //System.out.println("IL: " + pointArr[i-1].getX() + "; I:" + pointArr[i].getX());
        return ((pointArr[i-1].getY()-pointArr[i].getY())/(pointArr[i-1].getX()-pointArr[i].getX()))*(x-pointArr[i-1].getX())+pointArr[i-1].getY();
    }

    public int getPointsCount()
    {
        return pointsCount;
    }

    public FunctionPoint getPoint(int index)
    {
        if( index < 0 || index > pointsCount-1) {
            throw new FunctionPointIndexOutOfBoundsException("Cannot get: Index out of bounds");
        }
        return pointArr[index];
    }

    public void setPoint(int index, FunctionPoint point) throws InappropriateFunctionPointException
    {
        if(index < 0 || index > pointsCount - 1) {
            throw new FunctionPointIndexOutOfBoundsException("Cannot set: Index out of bounds");
        }
        if(pointArr[index+1].getX()<point.getX()||pointArr[index - 1].getX()>point.getX()){
            throw new InappropriateFunctionPointException("Cannot set:  Incorrect function point");
        }
        pointArr[index] = point;
    }

    public double getPointX(int index)
    {
        if( index < 0 || index > pointsCount - 1) {
            throw new FunctionPointIndexOutOfBoundsException("Cannot get: Index out of bounds");
        }
        return pointArr[index].getX();
    }

    public void setPointX(int index, double x) throws InappropriateFunctionPointException
    {
        if(index < 0 || index > pointsCount - 1) {
            throw new FunctionPointIndexOutOfBoundsException("Cannot set: Index out of bounds");
        }
        if((index != pointsCount - 1 && pointArr[index + 1].getX() < x) || (index != 0 && pointArr[index - 1].getX() > x)) {
            throw new InappropriateFunctionPointException("Cannot set: Incorrect function point");
        }
        pointArr[index].setX(x);
    }

    public double getPointY(int index)
    {
        if(index < 0 || index > pointsCount-1){
            throw new FunctionPointIndexOutOfBoundsException("Cannot get: Index out of bounds");
        }
        return pointArr[index].getY();
    }

    public void setPointY(int index, double y)
    {
        if(index < 0 || index > pointsCount-1) {
            throw new FunctionPointIndexOutOfBoundsException("Cannot set: Index out of bounds");
        }
        pointArr[index].setY(y);
    }

    //Class's add and del methods
    private void swapPoints(int index1, int index2)
    {
        FunctionPoint temp1 = pointArr[index1];
        pointArr[index1] = pointArr[index2];
        pointArr[index2] = temp1;
    }

    public void deletePoint(int index)
    {
        if(index < 0 || index > pointsCount-1) {
            throw new FunctionPointIndexOutOfBoundsException("Cannot delete: Index out of bounds");
        }
        if(pointsCount<3){
            throw new IllegalStateException("Cannot delete: Too many points");
        }
        while (index < pointsCount - 1)
            pointArr[index] = pointArr[++index];
        pointArr[index] = null;
        pointsCount--;
    }

    public void addPoint(FunctionPoint point) throws InappropriateFunctionPointException
    {
        for(int i=0; i < pointsCount; i++){
            if (pointArr[i].getX()==point.getX()){
                throw new InappropriateFunctionPointException("Cannot add: Found duplicate point");
            }
        }
        if(pointsCount == pointArr.length){
            FunctionPoint[] newPointArr = new FunctionPoint[pointsCount * 2];
            System.arraycopy(pointArr, 0, newPointArr, 0, pointsCount);
            pointArr = newPointArr;
        }
        pointArr[pointsCount] = point;
        int i = pointsCount;
        while(i > 0 && pointArr[i--].getX() < pointArr[i].getX()){
            swapPoints(i, i + 1);
        }
        pointsCount++;
    }

}