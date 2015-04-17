package 吸血鬼数;
public class 吸血鬼数 {
    public static void main(String[] args) {
        int i,j;
        for(i=32;i<100;++i)
        {
            for(j=10;j<i;++j)
            {
                int flag=0,a=i%10,b,c=j%10,d,t,n=i*j;
                t=i;t/=10;b=t;t=j;t/=10;d=t;
                for(int m=0;m<4;++m)
                {
                    t=n%10;
                    n/=10;
                    if(t==a){a=-1;++flag;continue;}
                    if(t==b){b=-1;++flag;continue;}
                    if(t==c){c=-1;++flag;continue;}
                    if(t==d){d=-1;++flag;continue;}
                    if(0==flag)break;
                }
                if(4==flag)System.out.println(i*j);
            }
        }
    }
}
