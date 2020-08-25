
/**
 * Write a description of class OptInJava here.
 *
 * @author Chris Bate
 * @version 24-08-2020
 */

//import java.lang.*;

public class OptInJava{
    /**
     * Constructor for objects of class OptInJava
     */
    public static void main(String[] args){
        System.out.println("\nHello\n");
        OptInJava a = new OptInJava();
        System.out.println(a.turnPoint(1,2,-4,0));System.out.println();
        System.out.println(a.solvQuad(1, 2, -4, 0));
    }

    private void printEq(double a, double b, double c){
        if(b>=0 &  c>=0){
            System.out.printf("of: %sx^2 + %sx + %s \n", a, b, c);
        }
        else{
            System.out.printf("of: %sx^2 + %sx + %s \n", a, b, c);
        }
    }

    private double solvQuad(double a, double b, double c, double start){
        System.out.printf("Root ");
        printEq(a, b, c);
        int i = 0;
        double x0 = start - (a*start*start + b*start + c) / (2*a*start + b);
        while(Math.abs(x0-start) > 0.000001){
            i ++;
            start = x0;
            x0 = start - (a*start*start + b*start + c) / (2*a*start + b);
            if(Math.abs(x0) == Double.POSITIVE_INFINITY){
                System.out.println("Divergent");
                break;
            }
        }
        System.out.printf("Iterations: %s\n", i);
        return x0;
    }

    private double turnPoint(double a, double b, double c, double start){
        System.out.printf("Turning point ");
        printEq(a, b, c);
        int i = 0;
        double x0 = start - (2*a*start + b) / (2*a);
        while(Math.abs(x0-start) > 0.0000001){
            i ++;
            start = x0;
            x0 = start - (2*start + b) / (2*a);
            if(Math.abs(x0) == Double.POSITIVE_INFINITY){
                System.out.println("Divergent");
                break;
            }
        }
        System.out.printf("Iterations: %s\n", i);
        return x0;
    }
}
