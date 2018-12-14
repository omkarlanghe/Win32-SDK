using System;
using System.Runtime.InteropServices;
using AutomationServerTypeLibForDotNet;

public class CSharpAutomation
{
    public static void Main()
    {
        CMyMathClass objCMyMathClass = new CMyMathClass();
        IMyMath objIMyMath = (IMyMath)objCMyMathClass;
        int num1 = 75, num2 = 25, sum, sub;
        sum = objIMyMath.SumOfTwoIntegers(num1, num2);
        Console.WriteLine("Sum Of " + num1 + " And " + num2 + " Is " + sum);
        sub = objIMyMath.SubtractionOfTwoIntegers(num1, num2);
        Console.WriteLine("Subtraction Of " + num1 + " And " + num2 + " Is " + sub);
    }
}
