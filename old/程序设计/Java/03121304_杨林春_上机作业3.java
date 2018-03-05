package java_practice;
import java.util.*;
class Stack{
        Stack(String s){
            List list=new LinkedList();
            int i=0,l=s.length();
            for(;i<l;++i){
                if('+'==s.charAt(i)){
                    list.add(s.charAt(i+1));
                }
                if('-'==s.charAt(i)){
                    System.out.print(list.get(list.size()-1));
                    list.remove(list.size()-1);
                }
            }
            while(list.size()>0){
                System.out.print(list.size()-1);
                list.remove(list.size()-1);
            }
        }
    }
class MyArrayList{
    private String s[];
    private int size;
    private int pos;
    MyArrayList(){
        size=10;
        s=new String [size];
        pos=0;
    }
    MyArrayList(int i){
        size=i;
        pos=0;
        s=new String [size];
    }
    void increase (){
        String sr[];
        int i=size;
        size+=10;
        sr=new String [size];
        System.arraycopy(s, 0, sr, 0, i);
        s=sr;
    }
    public void add(String sr){          //add at the end
        if(pos==size)increase();
        s[pos++]=sr;
    }
    public void set(int i,String sr){
        if(pos==size)increase();
        if(i>=pos)add(sr);
        else{
            for(int j=pos;j>i;--j){
                s[j]=s[j-1];
            }
            s[i]=sr;
            ++pos;
        }
    }
    public void clear(){
        pos=0;
    }
    public boolean isEmpty(){
        return pos!=0;
    }
    public String get(int i){
        if(i>=0&&i<=pos){
            return s[i];
        }
        else
            return s[0];
    }
    public int length(){
        return pos;
    }
    public void remove(int i){
        for(int j=i;j<pos;++j){
            s[i]=s[i+1];
        }
        pos--;
    }
}
public class Java_practice {
    public static void main(String[] args) {
        String s="+U+n+c---+e+r+t---+a-+i-+n+t+y---+-+r+u--+l+e+s---";
        Stack stack=new Stack(s);
        System.out.println();
        Date date=new Date();
        long start=date.getTime();
        MyArrayList list1=new MyArrayList();
        list1.add("this ");
        list1.add("Java ");
        list1.add("practice! ");
        list1.add("XXXX");
        list1.get(3);
        list1.isEmpty();
        list1.remove(4);
        list1.set(1, "is ");
        list1.set(4,"practice!");
        for(int i=0;i<list1.length()-1;++i){
            System.out.print(list1.get(i));
        }
        System.out.println();
        list1.clear();
        long end=date.getTime();
        System.out.println("NyArrayList time:"+(end-start));
    }
}