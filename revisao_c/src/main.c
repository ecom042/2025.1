#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *os_string = NULL;
int os_int = 0;

#define CHECK_ARGUMENTS 0

/* clang-format off */
#define MY_DIV(x, y, res)  \
	do {                   \
		if (y == 0) {      \
			*res = -1;     \
		} else {           \
			*res = x / y;  \
		}                  \
	} while (0)
/* clang-format on */

/**
 * Divides two integers and stores the result in a pointer.
 *
 * @param a The dividend.
 * @param b The divisor.
 * @param[out] res Pointer to store the result.
 * @return 0 on success, -1 on division by zero.
 */
int division(int a, int b, int *res)
{
#if defined(CHECK_DIVISION)
	if (b == 0) {
		return -1;
	}
#endif
	*res = a / b;
	return 0;
}

int main(int argc, char *argv[])
{
#if defined(CONFIG_LINUX)
	os_string = "Linux";
#elif defined(CONFIG_WINDOWS)
	os_string = "Windows";
#else
	os_string = "Unknown";
#endif

	printf("Hello, %s (%d)!\n", os_string, os_int);

	if (argc != 3) {
		printf("Usage: %s <numerator> <denominator>\n", argv[0]);
		return 1;
	}

	int a = atoi(argv[1]);
	int b = atoi(argv[2]);

#if defined(CHECK_ARGUMENTS)
	if (a == 0 || b == 0) {
		printf("Error: Invalid input\n");
		return 1;
	}
#endif

	int result;
	MY_DIV(a, b, &result);
	printf("Result of division: %d\n", result);
	// int err = MY_DIV(a, b, &result);
	// if (err) {
	// 	printf("Error: Division by zero\n");
	// } else {
	// 	printf("Result of division: %d\n", result);
	// }

	return 0;
}
