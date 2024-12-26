package functions;

import java.io.*;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Objects;

public class ArrayTabulatedFunction implements TabulatedFunction, Externalizable, Cloneable
{
    //Class's vars
    private FunctionPoint[] pointArr;
    private int pointsCount = 0;

    //Class's constructors
    public ArrayTabulatedFunction() {}

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
        while(pointsCount!=objects.length && objects[pointsCount]!=null)
            pointsCount++;
        int i=pointsCount-1;
        while(i > 0 && objects[i].getX() < objects[--i].getX());
        if(i <= 0)
        {
            throw new IllegalArgumentException("Cannot create TabulatedFunction: Left x should be greater than right x or number of values should be at least 2");
        }
        this.pointArr = objects;
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

    @Override
    public String toString()
    {
        StringBuilder str = new StringBuilder();
        str.append("{").append(pointArr[0].toString());
        for(int i=1; i < pointsCount; i++)
        {
            str.append(", ").append(pointArr[i].toString());
        }
        str.append("}");
        return str.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof TabulatedFunction)) return false;
        if (o instanceof ArrayTabulatedFunction temp) {
            if (temp.pointsCount != this.pointsCount) return false;
            for (int i = 0; i < this.pointsCount; ++i) {
                if (!temp.pointArr[i].equals(this.pointArr[i])) return false;
            }
        } else {
            if (((TabulatedFunction) o).getPointsCount() != this.getPointsCount()) return false;
            for (int i = 0; i < this.pointsCount; ++i) {
                if (!((TabulatedFunction) o).getPoint(i).equals(this.pointArr[i])) return false;
            }
        }
        return true;
    }

    @Override
    public int hashCode()
    {
        int hash = Objects.hash(pointsCount);
        for(int i=0; i < pointsCount; i++)
            hash ^=pointArr[i].hashCode()*i;
        return hash;
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        return new ArrayTabulatedFunction((FunctionPoint[]) pointArr.clone());
    }

    public Iterator<FunctionPoint> iterator()
    {
        return new Iterator<>()
        {
            private int index = 0;

            @Override
            public boolean hasNext()
            {
                return pointsCount > index;
            }

            @Override
            public FunctionPoint next() {
                if (pointsCount <= index) throw new NoSuchElementException();
                return pointArr[index++];
            }

            @Override
            public void remove() {
                throw new UnsupportedOperationException();
            }
        };
    }

    public static class ArrayTabulatedFunctionFactory implements TabulatedFunctionFactory
    {

        @Override
        public TabulatedFunction createTabulatedFunction(double leftX, double rightX, int pointsCount)
        {
            return new ArrayTabulatedFunction(leftX, rightX, pointsCount);
        }

        @Override
        public TabulatedFunction createTabulatedFunction(double leftX, double rightX, double[] values)
        {
            return new ArrayTabulatedFunction(leftX, rightX, values);
        }

        @Override
        public TabulatedFunction createTabulatedFunction(FunctionPoint[] arr)
        {
            return new ArrayTabulatedFunction(arr);
        }
    }
}