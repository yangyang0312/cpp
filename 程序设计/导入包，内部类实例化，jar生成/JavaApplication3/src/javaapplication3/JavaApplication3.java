package javaapplication3;
import javaapplication2.*;
public class JavaApplication3 
{
    public static void main(String[] args) 
    {
        JavaApplication2 a=new JavaApplication2();
        JavaApplication2.Book book=a.new Book(true);
        book.ci();
        JavaApplication2.main(args);
    }
}
//导入包，内部类实例化，jar生成