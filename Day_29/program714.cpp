// Input = 12
// Output = 1   2   3   4   6

#include<iostream>
using namespace std;

bool CheckPerfect(int iNo)
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
        CheckPerfect(iNo);
    }

    if(iSum == iNo)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    int iValue = 0;
    bool bRet = false;

    cout<<"Enter number : \n";
    cin>>iValue;

    bRet = CheckPerfect(iValue);

    if(bRet == true)
    {
        cout<<"Its a perfect number\n";
    }
    else
    {
        cout<<"Its not a perfect number\n";
    }

    return 0;
}