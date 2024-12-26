package myfirstpackage;
public class MySecondClass {
  private int i, j;
  
  public void SetI(int i) {
    this.i = i;
  }
  public void SetJ(int j) {
    this.j = j;
  }
  public int Summ() {
    return i + j;
  }
  public MySecondClass(){i = 0; j = 0;}
}
