// OOP Approach (Specific)

#include<iostream>
using namespace std;

class Arithematic
{
    public:
        int No1;
        int No2;

    Arithematic(int A, int B)
    {
        No1 = A;
        No2 = B;
    }

    int Addition()
    {
        int Ans = 0;
        Ans = No1 + No2;
        return Ans;
    }

    int Subtraction()
    {
        int Ans = 0;
        Ans = No1 - No2;
        return Ans;
    }
};

int main()
{
   Arithematic aobj1(11,10);
   Arithematic aobj2(101,50);

   cout<<aobj1.Addition()<<"\n";
   cout<<aobj1.Subtraction()<<"\n";

   cout<<aobj2.Addition()<<"\n";
   cout<<aobj2.Subtraction()<<"\n";
   
   return 0;
}