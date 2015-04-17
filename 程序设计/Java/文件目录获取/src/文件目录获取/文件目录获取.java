package 文件目录获取;
import java.io.File;
import java.util.Scanner;
class fileList
{
    static void getFileList(String dir,String ex,int len)
    {
	File file=new File(dir);
	if (file.isDirectory()) 
        {  
            File[] dirFile = file.listFiles();  
	    for (File f : dirFile)
            {
                if (f.isDirectory()) 
                {
	            getFileList(f.getAbsolutePath(),ex,len);
	        }
                else 
                {  
	            if(f.getAbsolutePath().endsWith(ex))
                    {
	                System.out.println(f.getAbsolutePath().substring(len,f.getAbsolutePath().length()));
	            }
                }  
            }
        }
    }
}
public class 文件目录获取
{
    public static void main(String[]args){
	Scanner in=new Scanner(System.in);
	System.out.print("请输入目录:");
	String dir=in.nextLine();
	System.out.print("请输入后缀:");
	String ex=in.nextLine();
	if((!dir.endsWith("\\"))&&(!dir.endsWith("/")))
        {
            dir+="\\";
	}
        fileList.getFileList(dir, ex,dir.length());
    }
}