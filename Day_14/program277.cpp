// OOP Approach

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
   Arithematic aobj(11,10);

   cout<<aobj.Addition()<<"\n";
   cout<<aobj.Subtraction()<<"\n";
   
   return 0;
}