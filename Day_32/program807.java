import java.util.*;

class program807
{
    public static void main(String A[])
    {
        Scanner sobj = new Scanner(System.in);

        System.out.println("Enter number of cities : ");
        int N = sobj.nextInt();

        if(N <= 0)
        {
            System.out.println("Invalid Input");
            return;
        }

        int Arr[][] = new int[N][7];
        int i = 0, j = 0, No = 0;

        System.out.println("Enter electricity consumption of each city : ");

        for(i = 0; i < N; i++)
        {
            System.out.println("Enter consumption of city : "+(i+1));
            for(j = 0; j < 7; j++)
            {
                No = sobj.nextInt();
                if(No < 0)
                {
                    System.out.println("Invalid Input");
                    return;
                }
                Arr[i][j] = No;
            }
        }

        int Weekly[] = new int[7];
        int HighestCity = 0;
        int MaxWeekly = 0;

        int PeakDay = 0;
        int MaxDayTotal = 0;
        int Sum = 0;

        // Weekly total + Highest consumption
        for(i = 0; i < N; i++)
        {
            Sum = 0;
            for(j = 0; j < 7; j++)
            {
                Sum = Sum + Arr[i][j];
            }
            Weekly[i] = Sum;

            if(Sum > MaxWeekly)
            {
                MaxWeekly = Sum;
                HighestCity = i;
            }
        }

        System.out.println("Highesh consumption : City "+HighestCity);
        System.out.println("Highest consumption : "+MaxWeekly);

        sobj.close();
    }
}