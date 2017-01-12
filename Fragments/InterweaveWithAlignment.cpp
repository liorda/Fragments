// following
// http://stackoverflow.com/questions/40524189/deconstruct-array-of-structs-with-natvis

#include <stdio.h>

#define A(t) __declspec(align(t))

struct C
{
	int a;
	int b;
	int c;
	int junk;
};

A(16) struct D
{
	int z;
};

A(16) struct DB {
	int junk;
	int z;
};

A(16) struct DC {
	int junk[2];
	int z;
};

typedef union
{
	D da;
	DB db;
	DC dc;
} Ui;

typedef union
{
	C c[50];
	Ui d[50];
} U;

//C c[50] = {0};
U u = { 0 };

void MainInterweaveWithAlignment()
{
	for (int i = 0; i < 50; ++i)
	{
		u.c[i].a = i;
		u.c[i].b = 2 * i;
		u.c[i].c = 3 * i;
	}

	// all a's
	for (int i = 0; i < 50; ++i)
	{
		printf("a[%d]: %d\n", i, u.d[i].da.z);
	}
	// all b's
	for (int i = 0; i < 50; ++i)
	{
		printf("b[%d]: %d\n", i, u.d[i].db.z);
	}
	// all c's
	for (int i = 0; i < 50; ++i)
	{
		printf("c[%d]: %d\n", i, u.d[i].dc.z);
	}
}