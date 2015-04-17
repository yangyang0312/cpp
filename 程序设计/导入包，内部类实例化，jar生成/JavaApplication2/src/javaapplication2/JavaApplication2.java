package javaapplication2;

import java.util.*;

public class JavaApplication2 {

    public static void main(String[] args) {
        Random rand = new Random(47);
        int[] a = new int[rand.nextInt(30)];
        for (int i = 0; i < a.length; ++i) {
            a[i] = rand.nextInt(1000);
        }
        System.out.println(a.length);
        System.out.println(Arrays.toString(a));
    }

    public class Book {

        boolean co = false;

        public Book(boolean co) {
            co = co;
        }

        public void ci() {
            co = false;
            System.out.println("xxxxxxxx");

        }

        protected void finalize() {
            if (co) {
                System.out.println("Error");
            }
        }
    }
}
