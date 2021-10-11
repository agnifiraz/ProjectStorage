/*
 * Class name: Fraction
 * Purpose: Serve as an object class for a fraction (a/b) in "FractionApp"
 * Coder: Agnita Paul
 * Date: 6 August 2021
 */

public class Fraction implements Comparable<Fraction>{


    //declare class properties/variable:
    private int num;
    private int den;

    //public constructor(s) here:
    public Fraction() {
        this.num = 1;
        this.den = 1;
    }

    public Fraction(int _num, int _den) {
        this.num = _num;
        this.den = _den;
    }


    //getter and setters for class properties/variables
    /*
     * Method name:     getNum()
     * Coded by:        Agnita Paul.
     * Purpose:         return/get the numerator part of the fraction.
     * @pram:           NONE.
     * @return:         int     numerator part of the fraction.
     */
    public int getNum() {
        return num;
    }

    /*
     * Method name:     getDen()
     * Coded by:        Agnita Paul.
     * Purpose:         return/get the denominator part of the fraction.
     * @pram:           NONE.
     * @return:         int     denominator part of the fraction.
     */
    public int getDen() {
        return den;
    }

    /*
     * Method name:     setNum()
     * Coded by:        Agnita Paul.
     * Purpose:         set the numerator part of the fraction.
     * @pram:           int     pass in an int value to be set as numerator for this fraction.
     * @return:         NONE
     */
    public void setNum(int num) {
        this.num = num;
    }

    /*
     * Method name:     setDen()
     * Coded by:        Agnita Paul.
     * Purpose:         set the denominator part of the fraction.
     * @pram:           int     pass in an int value to be set as denominator for "this" fraction.
     * @return:         NONE
     */
    public void setDen(int den) {
        this.den = den;
    }


    /*
     * Method name:     toDouble()
     * Coded by:        Agnita Paul.
     * Purpose:         to change the fraction into a double value.
     * @pram:           NONE.
     * @return:         double      returns "this" fraction as a double.
     */
    public double toDouble() {
        return getNum() * 1.0/getDen();
    }

    /*
     * Method name:     toReciprocal()
     * Coded by:        Agnita Paul.
     * Purpose:         to reciprocate (switch numerator and denominator) a fraction.
     * @pram:           NONE.
     * @return:         Fraction      returns the reciprocated fraction of type Fraction.
     */
    public Fraction toReciprocal() {
        return new Fraction(this.getDen(), this.getNum());
    }

    /*
     * Method name:     add()
     * Coded by:        Agnita Paul.
     * Purpose:         to add or sum 2 fractions together.
     * @pram:           Fraction      a second fraction to be added into "this" fraction.
     * @return:         Fraction      returns the sum of 2 fractions of type Fraction.
     */
    public Fraction add(Fraction f) {
        //declaring my num and den of type int.
        int num;
        int den;

        //getting num and den of arg fraction.
        int num2 = f.getNum();
        int den2 = f.getDen();

        //checking to see if the denominators of both fractions are same.
        if (den2 == this.getDen()) {
            num = this.getNum() + num2;     //if same, we add 2 numerators and set it equal to num declared above.
            den = den2;                     //and set the den to arg fraction's den (could also be "this" fraction den) and set it equal to den declared above.

            Fraction result = new Fraction(num, den); //generate a new fraction object and pass in the num and den.
            return result;                            //return the result
        } else {
            int common_d = this.den * den2;           //if den is not common, we multiply both denominators.

            int d2 = common_d/this.getDen(); //5      //divide the multiplied value with "this" fractions denominator and store the value in variable d2.
            int n1 = d2 * this.getNum(); //5 x 2      //multiply the d2 with "this" fraction's numerator to get our first numerator.

            den = common_d/den2; //4                  //divide the multiplied value with arg fraction's denominator and store the value in variable den.
            int n2 = den * num2; //4 x 6              //multiply den with arg fraction's numerator to get our second numerator.

            num = n1 + n2;                            //set our num to by adding n1 + n2.
            den = common_d;                           //set our den to common_d (multiplied value)

            Fraction result =  new Fraction(num, den); //create a new fraction object and pass in num and den
            return result;                              //return the fraction object
        }
    }

    /*
     * Method name:     multiply()
     * Coded by:        Agnita Paul.
     * Purpose:         to multiply 2 fractions together.
     * @pram:           Fraction      a second fraction to be multiplied with "this" fraction.
     * @return:         Fraction      returns the result of multiplication of 2 fractions of type Fraction.
     */
    public Fraction multiply(Fraction f) {
        //multiply the num of this fraction with arg fraction, multiply the den of this fraction with arg fraction.
        Fraction result = new Fraction(getNum() * f.getNum(), getDen() * f.getDen());

        //return the Fraction object created.
        return result;
    }

    /*
     * Method name:     equals()
     * Coded by:        Agnita Paul.
     * Purpose:         to check and see if 2 fractions are equal or not
     * @pram:           Fraction      a second fraction to be compared with "this" fraction for equality.
     * @return:         boolean       returns true if 2 fractions are equal and false if they are Not equal.
     */
    public boolean equals(Fraction f) {
        if(this.toDouble() == f.toDouble()) {   //convert the fraction to double to effectively compare them.
            return true;
        } else {
            return false;
        }
    }

    /*
     * Method name:     greaterThan()
     * Coded by:        Agnita Paul.
     * Purpose:         to find the greater fraction of two fractions
     * @pram:           Fraction      a second fraction to be compared with.
     * @return:         boolean       returns true if this fraction is greater than arg fraction else false.
     */
    public boolean greaterThan(Fraction f) {
        double fraction_1 = this.toDouble();
        double fraction_2 = f.toDouble();

        if (fraction_1 > fraction_2) {
            return true;
        } else {
            return false;
        }
    }

    public int gcd(int den1, int den2) {
        return 0;
    }

    /*
     * Method name:     lowestTerms()
     * Coded by:        Agnita Paul.
     * Purpose:         to convert this fraction into it's lowest terms.
     * @pram:           NONE.
     * @return:         Fraction      returns the fraction in it's lowest forms.
     */
    public Fraction lowestTerms() {
        int divisor = 0;

        for(int i = this.getNum(); i >= 1; i--) {
            if(this.getNum() % i == 0 && this.getDen() % i ==0) {
                divisor = i;
                break;
            }
        }

        if(divisor != 0) {
            num = this.getNum();
            den = this.getDen();

            this.setNum(num /= divisor);
            this.setDen(den /= divisor);
        }

        return new Fraction(this.getNum(), this.getDen());
    }


    @Override
    public int compareTo(Fraction o) {
        return 0;
    }

    @Override
    public String toString() {
        return num + "/" + den;
    }
}
