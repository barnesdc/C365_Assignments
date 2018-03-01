#include <iostream>
#include <vector>
#include <string>
using namespace std;
/*
 * Homework 1 - Comp365
Write a program that implements Large Integer operations. Your should:
"	Implement a LargeInteger class
"	Implement member functions that can input and output Large Integers
"	Implement member function that adds two Large Integers
"	Implement member function that multiplies two Large Integers
"	Write a main program that asks users to input two large integers and output the sum and product of these two numbers

Grading Standard:
"	Compiles  (20%)
"	Input and Output Large Integers (30%)
"	Adds two Large Integers (20%)
"	Multiples two Large Integers (30%)
 *
 */

class LargeInteger{

private:
    vector <uint8_t> num; //vector of single digit numbers, why single digit

public:
    // passing parameter by value is very expensive
    // pass by reference instead to pass object B,
    // Address is copied and use CONST to prevent modification of B
    // const after a function tells compiler that
    // this is a function that does not modify; i.e. "get" method
    LargeInteger(){
    }

/**********************************************************************************************************************/
//Convert string to Large Integer
    LargeInteger (string s){
        // handles very large numbers
        // read a string and push_back each individual
        int i;
        for(i = 0; i < s.length(); i++){
            uint8_t x;
            x = int(s[i]) - '0';
            num.push_back(x);
        }
        reverse(num.begin(),num.end());

    }

    // works for input of integers
//    LargeInteger(int k){
//        while(k > 0){
//            num.push_back(k%10);
//            //cout << n%10 << endl;
//            k/=10;
//    }

/**********************************************************************************************************************/
//Add Class
    LargeInteger add(const LargeInteger& B) const {
        LargeInteger sum;
        int temp, saveNum, carry = 0;
        int i;

        for(i=0; i<max(num.size(),B.num.size()); i++){

            int x = 0, y = 0;
            if (i < num.size()) {
                x = num[i];
            }
            if (i < B.num.size()){
                y = B.num[i];
            }

            cout << x<<" : " << y << endl;
            cout << endl;

            // carry flag is set
            if(carry > 0) {

                // add two vectors + carry
                // determine if greater than 9
                // if so, set carry flag
                // pop off last digit --> push last digit on to vector
                // if not, add two digits + carry
                // set carry flag back to 0
                // push last digit on to vector

                saveNum = x + y+ 1;
                if (saveNum > 9){
                    carry = 1;
                    temp = saveNum % 10;
                    sum.num.push_back(temp);
                }
                else{
                    saveNum = x + y+1;
                    carry = 0;
                    sum.num.push_back(saveNum);
                }
            }

            // carry flag is not set
            else{

                // add two vectors
                // determine if greater than 9
                // if so, set carry flag
                // pop off last digit --> push last digit on to vector
                // if not, add two digits
                // set carry flag back to 0
                // push last digit on to vector

                saveNum = x + y;
                if (saveNum > 9){
                    carry = 1;
                    temp = saveNum % 10;
                    sum.num.push_back(temp);
                }

                else{
                    saveNum = x + y;
                    carry = 0;
                    sum.num.push_back(saveNum);
                }
            }
        }
        if (carry == 1) {
            sum.num.push_back(1);
        }
        return sum;
    }

/**********************************************************************************************************************/
//Multiply class
    LargeInteger multiply(const LargeInteger& B) const{
        LargeInteger tempSum, product;      // large integer vectors to hold the value of the current sum and product
        vector <uint8_t> zeroes;            // placeholder to maintain zeroes as multiplication progresses
        int temp, saveNum, carry = 0;
        int i, j;

        for(i=0; i < num.size(); i++) {

            for(j=0;j<B.num.size(); j++){

                int x = 0, y = 0;
                x = num[i];
                y = B.num[j];

                //saveNum = (num[i] * num[j]) + carry;
                saveNum = (x * y) + carry;

                cout << x << " * " << y << " + " << carry << " = " << saveNum << endl;


                if (saveNum > 9){
                    carry = saveNum / 10;
                    saveNum = saveNum % 10;
                    tempSum.num.push_back(saveNum);
                }
                else{
                    carry = 0;
                    saveNum = saveNum % 10;
                    tempSum.num.push_back(saveNum);
                }

            }
            if (carry > 0 ) {
                tempSum.num.push_back(carry);
            }
            carry = 0;
            cout << "Tempsum ";
            tempSum.print();
            product = product.add(tempSum);
            zeroes.push_back(0);
            tempSum.num = zeroes;
            cout << "Product ";
            product.print();

        }
        return product;
    }


/**********************************************************************************************************************/
    void print() const{
        int i;
        cout << "Number : ";
        for(i=num.size()-1;i>=0;i--){
            cout << int(num[i]);
        }
        cout << endl;
    }
/**********************************************************************************************************************/
//Power

    // If n = 0, return 1
    // Otherwise, figure out how to call multiply as many times as need
    // to obtain the vector to the power of n
    LargeInteger power(int n){
        // Initializing power vector to 1 which is the first number to multiply by
        //
        LargeInteger power("1");
        int i;

        //if(n == 0) return power;

        for(i = 1; i <= n; i++){
                power = power.multiply(*this);
        }

        return power;

    }

/**********************************************************************************************************************/
//Convert large int to string

    LargeInteger toString() const{
        int i;
        string stringNum = "";
        string space = " ";
        for (i = 0; i <= num.size() -1; i++){
            stringNum = (char)num[i] + '0';
            stringNum = space + stringNum;        }
        return stringNum;
    }

/**********************************************************************************************************************/
};

//Main

int main(){

    LargeInteger A,B,C,D,E("8"),F;
    string s;


//    cout << "Enter in the first number: ";
//    cin >> s;
//    A = LargeInteger(s);
//
//    cout << "Enter in the first number: ";
//    cin >> s;
//    B = LargeInteger(s);
//
//    C = A.add(B);
//    C.print();
//
//
//    D = A.multiply(B);
//    D.print();

    F = E.power(8);
    F.toString();


  return 0;
}

