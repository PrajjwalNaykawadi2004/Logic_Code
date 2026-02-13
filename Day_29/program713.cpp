// Input = 12
// Output = 1   2   3   4   6

#include<iostream>
using namespace std;

int SumFactors(int iNo)
{
    static int iCnt = 1;
    static int iSum = 0;
    
    if(iSum <= (iNo / 2))
    {
        if(iNo % iCnt == 0)
        {
            iSum = iSum + iCnt;
        }
        iCnt++;
        SumFactors(iNo);
    }

    return iSum;
}

int main()
{
    int iValue = 0 ,iRet = 0;

    cout<<"Enter number : \n";
    cin>>iValue;

    iRet = SumFactors(iValue);

    return 0;
}