package 计算a出现次数;
public class 计算a出现次数 {
    public static void main(String[] args) {
        String str="Java is my favorate programming language";
        int i=0,l=str.length(),n=0;
        for(;i<l;++i)if(str.charAt(i)=='a')++n;
        System.out.println(n);
    }
}
