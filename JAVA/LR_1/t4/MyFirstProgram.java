class MyFirstClass {
	public static void main(String[] s) {
    MySecondClass o = new MySecondClass();
    int i, j;
    for (i = 1; i <= 8; i++) {
	    for(j = 1; j <= 8; j++) {
		    o.SetI(i);
		    o.SetJ(j);
		    System.out.print(o.Summ());
		    System.out.print(" ");
	    }
	System.out.println();
    }
	}
}

class MySecondClass {
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
  public MySecondClass(){i=0;j=0;}
}
