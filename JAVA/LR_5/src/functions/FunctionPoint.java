package functions;
import java.io.Serializable;
import java.util.Objects;

public class FunctionPoint implements Serializable, Cloneable
{
    //Class's vars
    private double x, y;

    //Class's constructors
    public FunctionPoint(double x, double y)
    {
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
    public String toString() {return (String) ("("+x + "; " + y)+")";}
    public boolean equals(Object o) {return o==this||!(o instanceof FunctionPoint && ((FunctionPoint) o).getX()==this.x && ((FunctionPoint) o).getY()==this.y);}

    @Override
    public int hashCode()
    {
        int largePartX=(int)(Double.doubleToLongBits(x)>>32)<<1;
        int smallPartX=(int)(Double.doubleToLongBits(x))>>1;
        int largePartY=(int)(Double.doubleToLongBits(y)>>32);
        int smallPartY=(int)(Double.doubleToLongBits(y));
        return 907*(largePartX+smallPartX)^(largePartY+smallPartY);
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        return super.clone();
    }
}
