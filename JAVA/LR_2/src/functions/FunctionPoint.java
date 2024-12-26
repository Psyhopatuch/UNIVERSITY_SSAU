package functions;

public class FunctionPoint {
    //Class's vars
    private double x, y;

    //Class's constructors
    public FunctionPoint(double x, double y) {
        this.x = x;
        this.y = y;
    }
    public FunctionPoint(FunctionPoint point) {
        this.x = point.getX();
        this.y = point.getY();
    }
    public FunctionPoint() {
        x = 0;
        y = 0;
    }

    //Class's set and get methods
    public double getX() {
        return x;
    }
    public void setX(double x) {
        this.x = x;
    }
    public double getY() {
        return y;
    }
    public void setY(double y) {
        this.y = y;
    }
}
