#include <stdio.h>

void betty_code(void)
{
	char operator;
	double num1;
	double num2;
	double result;

	/* Prompt for the operator */

	printf("What operator would you like to use (+, -, *, /): \n");
	scanf("%c", &operator);

	/* Prompt for num1 and num2 */

	printf("Enter num1: ");
	scanf("%lf", &num1);  /* Use %lf for double values */
	printf("Enter num2: ");
	scanf("%lf", &num2);  /* Use %lf for double values */

	switch (operator) {
		case '+':
			result = num1 + num2;
			printf("%.2f + %.2f = %.2f\n", num1, num2, result);
		break;
		case '-':
			result = num1 - num2;
			printf("%.2f - %.2f = %.2f\n", num1, num2, result);
		break;
		case '*':
			result = num1 * num2;
			printf("%.2f * %.2f = %.2f\n", num1, num2, result);
		break;
		case '/':
			if (num2 != 0) {
				result = num1 / num2;
				printf("%.2f / %.2f = %.2f\n", num1, num2, result);
		} else {
			printf("Error: Division by zero is not allowed.\n");
		}
		break;
		default:
			printf("Please enter one of the available operators.\n");
	}
}
