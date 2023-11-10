#include <stdio.h>
  2
  3 int main()
  4 {
	char operator;
	double num1;
	double num2;
	double result;
  9
	printf("What operator would you like to use(+, -, *, /):\n");
	scanf("%c", &operator);
 12
 13	printf("Enter num1:\t");
 14	scanf("%lf", &num1);
 15
 16	printf("Enter num2: \t");
 17	scanf("%lf", &num2);
 18
 19	switch(operator)
 20	{
 21	case '+':
 22		result = num1 + num2;
 23		printf("%.2lf + %.2lf = %.2lf\n", num1, num2, result);
 24     break;
 25	case '-':
 26		result = num1 - num2;
 27		printf("%.2lf - %.2lf = %.2lf\n", num1, num2, result);
 28	break;
 29	case '*':
 30		result = num1 * num2;
 31		printf("%.2lf * %.2lf = %.2lf\n", num1, num2, result);
 32	break;
 33	case '/':
 34		result = num1 / num2;
 35		printf("%.2lf / %.2lf = %.2lf\n", num1, num2, result);
 36		break;
 37
 38	default:
 39	printf("Please enter one of the available operators\n");
 40	}
	return 0;
}


