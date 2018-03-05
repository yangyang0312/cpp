package 素数另解;
public class 素数另解 {
    public static void main(String[] args) {
        int P=100000000;
	int i,j,co=1,N=P*2+1;
        byte a[]=new byte[P];
	for(i=0;i<P;++i)a[i]=1;
        System.out.print("2  ");
        double s=Math.sqrt(N);
    for (i=3;i<=s;i+=2)
    {
        if(a[(i-1)/2-1]==1)
        {
            for(j=(i*i-1)/2-1;j<P;j+=i)a[j] = 0;//去除掉所有素数的倍数
        }
    }
    for(i=0;i<P;++i)if(a[i]==1)
    {
        System.out.print((i+1)*2+1 + "  ");
        ++co;//素数数量统计
    }
    System.out.println();
    System.out.println(co);
    }   
}