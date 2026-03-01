import java.util.*;

class program809
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

        int DaySum = 0;
        int Day = 0;

        // Day with maximum consumption

        for(Day = 0; Day < 7; Day++)
        {
            DaySum = 0;
            for(i = 0; i < N; i++)
            {
                DaySum = DaySum + Arr[i][Day];
            }

            if(DaySum > MaxDayTotal)
            {
                MaxDayTotal = DaySum;
                PeakDay = Day;
            }
        }

        String DayName[] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

        System.out.println("Peak consumption day : "+PeakDay);
        System.out.println("Peak consumption day name : "+DayName[PeakDay]);

        System.out.println("Weekly consumption : ");
        for(i = 0; i < N; i++)
        {
            System.out.println("City : "+(i+1)+" : "+Weekly[i]);
        }

        // Cities more than 500 consumption
        System.out.println("Cities more than 500 consumption : ");
        for(i = 0; i < N; i++)
        {
            if(Weekly[i] > 500)
            {
                System.out.println("City : "+(i+1));
            }
        }

        sobj.close();
    }
}