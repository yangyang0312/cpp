/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package pi值计算;

/**
 *
 * @author DELL
 */
public class Pi值计算 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        double pi=0.0,flag=1;
        int i=0;
        while(1/(2.0*i+1)>0.000000001)
        {
            pi+=flag/(2.0*i+1);
            flag=-flag;
            i++;
        }
        System.out.println(4*pi);
    }
    
}
