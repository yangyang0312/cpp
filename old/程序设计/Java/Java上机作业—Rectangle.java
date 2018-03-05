class Point 
{
    public double x;
    public double y;
    public Point()
    {
        x=0.0;
        y=0.0;
    }
    public Point(double xx,double yy)
    {
        x=xx;
        y=yy;
    }
    public double distance(Point p)
    {
        return Math.sqrt((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y));
    }
}
class Rectangle 
{
    public double width;
    public double height;
    public Point p;
    public Rectangle()
    {
        width=0.0;
        height=0.0;
        p=new Point();
    }
    public Rectangle(double w,double h)
    {
        width=w;
        height=h;
        p=new Point();
    }
    public Rectangle(double w,double h,double a,double b)
    {
        width=w;
        height=h;
        p=new Point(a,b);
    }
    public double getArea()
    {
        return width*height;
    }
    public double getPerimeter()
    {
        return 2*(width+height);
    }
    public boolean bPointIn(Point p1)
    {
        return p1.x>=p.x&&p1.x<=(p.x+width)&&p1.y>=p.y&&p1.y<=(p.y+height);
    }
    public boolean bRectangleIn(Rectangle r)
    {
        return bPointIn(r.p)&&bPointIn(new Point(r.p.x+r.width,r.p.y+r.width));//左下点和有上点是否在矩形内部
    }
}