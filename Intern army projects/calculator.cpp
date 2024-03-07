#include <iostream>
using namespace std;
int main()
{
   char op;
   float num1,num2;
   cout<<"Enter any two numbers:";
   cin>>num1>>num2;
   cout<<"Enter operator either + (for addition) or - (for subtraction) or * (for multiplication) or / (for division):";
   cin>>op;
   switch(op){
       case'+':
       cout<<num1+num2;
       break;
       case'-':
       cout<<num1-num2;
       break;
       case'*':
       cout<<num1*num2;
       break;
       case'/':
       cout<<num1/num2;
       break;
       default:
       cout<<"oops! Operator is invalid enter a new operator again.";
       break;
   }
   
    return 0;
}
