package functions;

public class TabulatedFunction {
    //Class's vars
    private FunctionPoint[] pointArr;
    private int pointsCount;



    //Class's constructors
    public TabulatedFunction(double leftX, double rightX, int pointsCount){
        pointArr = new FunctionPoint[pointsCount * 2];
        this.pointsCount = pointsCount;
        double stepX = (rightX-leftX) / (pointsCount - 1);
        double curX;
        for (int i=0; i < pointsCount; i++){
            curX = leftX + stepX * i;
            //System.out.println(i + ")" + " CurX = " + curX);
            pointArr[i] = new FunctionPoint(curX, 0);
        }
    }
    public TabulatedFunction(double leftX, double rightX, double[] values){
        pointArr = new FunctionPoint[values.length * 2];
        pointsCount = values.length;
        double stepX = (rightX-leftX) / (pointsCount - 1);
        double curX;
        for (int i=0; i < pointsCount; i++){
            curX = leftX + stepX * i;
            //System.out.println(i + ")" + " CurX = " + curX);
            pointArr[i] = new FunctionPoint(curX, values[i]);
        }
    }

    //Class's set and get methods
    public double getLeftDomainBorder(){
       return pointArr[0].getX();
    }

    public double getRightDomainBorder(){
        return pointArr[pointsCount-1].getX();
    }

    public double getFunctionValue(double x) {
        if(x>getRightDomainBorder()||x<getLeftDomainBorder())
            return Double.NaN;
        int i=0;
        while(pointArr[i].getX() <= x && i < this.getPointsCount() - 1){i++;}
        return ((pointArr[i-1].getY()-pointArr[i].getY())/(pointArr[i-1].getX()-pointArr[i].getX()))*(x-pointArr[i-1].getX())+pointArr[i-1].getY();
    }

    public int getPointsCount(){
        return pointsCount;
    }

    public FunctionPoint getPoint(int index) {
        return pointArr[index];
    }

    public void setPoint(int index, FunctionPoint point) {
        if(pointArr[index+1].getX()<point.getX()||pointArr[index-1].getX()>point.getX())
            return;
        pointArr[index] = point;
    }

    double getPointX(int index){
        return pointArr[index].getX();
    }

    public void setPointX(int index, double x){

        if((index != pointsCount - 1 && pointArr[index + 1].getX() < x) || (index != 0 && pointArr[index - 1].getX() > x))
            return;
        pointArr[index].setX(x);
    }

    public double getPointY(int index){
        return pointArr[index].getY();
    }

    public void setPointY(int index, double y){
        pointArr[index].setY(y);
    }

    //Class's add and del methods
    private void swapPoints(int index1, int index2){
        FunctionPoint temp1 = pointArr[index1];
        pointArr[index1] = pointArr[index2];
        pointArr[index2] = temp1;
    }

    public void deletePoint(int index){
        pointArr[index]=null;
        for(int i=index; i < pointsCount - 1; i++)
        {
            pointArr[i]=pointArr[i+1];
        }
        pointsCount--;
    }

    public void addPoint(FunctionPoint point){
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
