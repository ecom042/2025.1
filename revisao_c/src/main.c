#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
// #include <zephyr/kernel.h>
//  Tipos primitivos

// float f;  // i32
// double d; // i64

// int i; // i32

// uint64_t x = 10;
// int8_t v = 200; // [-128,127]
// bool b = true;

// char c = '?'; // (0x3F);
// char name[] = "John Doe";

// Operações bitwise
//                                             end
//                                              |
int32_t arr[4] = {5, 4, 3, 2}; //{}
int32_t arr2[] = {true, false, false, true};
bool arr3[3][3] = {{true, false, false}, {true, false, false}, {true, false, false}};

// string de C
char name[] = "Fulano de Tal";
char name2[] = {'F', 'u', 'l', 'a', 'n', 'o', ' ', 'd', 'e', ' ', 'T', 'a', 'l', '\0'};

// Array de bytes
char name3[] = {'F', 'u', 'l', 'a', 'n', 'o', ' ', 'd', 'e', ' ', 'T', 'a', 'l', ' ', ' '};
char name4[] = "agora foi";
//   Array
//   Ponteiros
uint8_t bytes[100];
// Estruturas
// Union

#define BIT(n) (1 << n)

#define LED_ENABLED BIT(5)
#define ACC_ENABLED BIT(3)

struct point {
	int x;  // 0 // 4
	char c; // 2 // 1
	short s;
	short s2;
	// padding 2
	char c2;
	int y; // 1 // 4
	// padding 7
	int64_t f; // 8
} __attribute__((packed));

struct point point1 = {10, 20};
struct point point2 = {30, 40};

int main(int argc, char *argv[])
{
	int32_t *temp = arr;
	for (int i = 0; i < 4; ++i) {
		printf("arr[%d] = %d\n", i, temp[i]);
	}

	int32_t *iter = arr;
	int32_t *end = arr + 4;
	for (; iter < end; ++iter) {
		printf("arr[%d] = %d\n", (int)(iter - arr), *iter);
	}

	// TODO: navegar pelo array usando aritimética de ponteiros

	printf("name size: %zu\n", strlen(name));
	printf("name size: %zu\n", strlen(name2));
	printf("name size: %zu\n", strlen(name3));

	int a = 0x0F; // 0000.0001 >> 1 = 0000.0000
	int b = 0xF0; // !(0000.0000) = 1
		      // ~0000.0000

	uint8_t config = ACC_ENABLED; // 0010.1000

	if (config & LED_ENABLED) {
		//
	} else {
		config = config | LED_ENABLED;
	}

	config = config & (~LED_ENABLED);

	int c = a || b; // +
	int d = a && b; // *

	printf("a = 0x%02X\n", a);
	printf("b = 0x%02X\n", b);
	printf("c = 0x%02X\n", c);
	printf("a & b = 0x%02X\n", a & b);
	printf("a | b = %d\n", a | b);
	printf("a ^ b = %d\n", a ^ b);
	printf("~a = %d\n", ~a);
	printf("~b = %d\n", ~b);
	printf("a << 2 = %d\n", a << 2);
	printf("a >> 2 = %d\n", a >> 2);
	printf("b << 2 = %d\n", b << 2);
	printf("b >> 2 = %d\n", b >> 2);

	int x = 10;
	int y = 100;
	int *p = &x;
	*p = 15;
	// p = &y;
	*(p - 1) = 25;

	printf("x = %d, &x = %p, y = %d, &y = %p, p = %p, &y - &x = %d\n", x, &x, y, &y, p,
	       (int)(&x - &y));

	// bool *p3 = arr3;
	// p3[0][1] = 30;
	// arr3[0][1] = 30;

	printf("sizeof struct point %zu\n", sizeof(struct point));

	return 0;
}
