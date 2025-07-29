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
int arr4[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
// string de C
char name[] = "Fulano de Tal";
char name2[] = {'F', 'u', 'l', 'a', 'n', 'o', ' ', 'd', 'e', ' ', 'T', 'a', 'l', '\0'};

// Array de bytes
char name3[] = {'F', 'u', 'l', 'a', 'n', 'o', ' ', 'd', 'e', ' ', 'T', 'a', 'l', ' ', ' '};
char name4[] = "agora foi";
//   Array
//   Ponteiros
uint8_t bytes[100];

// bitfield
struct config {
	uint16_t res1: 3;
	uint16_t acc_en: 1;
	uint16_t res2: 1;
	uint16_t led_en: 1;
	uint16_t res3: 16;
};

struct payload {
	uint16_t level: 4;
	uint16_t temp: 5;             /* 18 + temp */
	uint16_t last_fill_hour: 5;   /* 24 hours  */
	uint16_t last_fill_minute: 2; /* 0, 15, 30, 45 minutes */
};

union payload_data {
	struct payload payload;
	uint8_t bytes[2];
} p;

union variant {
	char c;
	short s;
	int i;
	bool b;
	float f;
};

struct calc {
	enum {
		ADD,
		SUB,
		DIV,
		MULT,
		MINUS
	} __attribute__((packed)) op;
	bool flag1;
	bool flag2;
	bool flag3;
	union {
		struct {
			int a;
			int b;
		};
		struct {
			int u;
		};
	};
} __attribute__((aligned(16)));

int op(struct calc *c)
{
	switch (c->op) {
	case ADD:
		return c->a + c->b;
	case SUB:
		return c->a - c->b;
	case DIV:
		return c->a / c->b;
	case MULT:
		return c->a * c->b;
	case MINUS:
		return -c->u;
	}
}

typedef union variant variant_t;

union variant var = {.s = 200};
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

int get_arr4_element(int row, int col)
{
	int *p4 = (int *)arr4;
	return p4[row * 3 + col];
}

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

	// struct row row[] = {{.col0 = 1, .col1 = 2, .col2 = 3},
	// 		    {.col0 = 4, .col1 = 5, .col2 = 6},
	// 		    {.col0 = 7, .col1 = 8, .col2 = 9}};

	// row[0].col0 = 10;
	// row[0].col1 = 20;
	// row[0].col2 = 30;
	printf("value %d\n", get_arr4_element(1, 1));

	printf("sizeof struct point %zu\n", sizeof(struct point));

	uint8_t c1 = ACC_ENABLED | LED_ENABLED;
	struct config cfg = {.acc_en = 1, .led_en = 0};

	printf("Config %#.02x\n", *((uint8_t *)&cfg));
	return 0;
}
