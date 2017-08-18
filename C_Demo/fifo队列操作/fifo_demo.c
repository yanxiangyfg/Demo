/**
* 文件功能: 
* @总体功能介绍:	移植内核kfifo.h中的链表实现到fifo_emu.h中,以便应用层程序能使用内核官方定义的链表
* @fifo_emu.h: 对内核kfifo.h文件的移植,主要是链表结构以及操作例程
* @fifo_demo.h: 业务逻辑相关的头文件
* @参考: samples/kfifo/Bytestream-example.c

* 作者: 杨佛根
* 日期: 2017.08.17
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h> 
/**
* 模拟内核队列实现的头文件 "fifo_emu.h"
*/
#include "fifo_emu.h"

#define FIFO_SIZE	32

static struct kfifo test;

static const unsigned char expected_result[FIFO_SIZE] = {
	 3,  4,  5,  6,  7,  8,  9,  0,
	 1, 20, 21, 22, 23, 24, 25, 26,
	27, 28, 29, 30, 31, 32, 33, 34,
	35, 36, 37, 38, 39, 40, 41, 42,
};


static int testfunc(void)
{
	unsigned char	buf[6];
	unsigned char	i, j;
	unsigned int	ret;

	printf("byte stream fifo test start\n");

	/* put string into the fifo */
	kfifo_in(&test, "hello", 5);

	/* put values into the fifo */
	for (i = 0; i != 10; i++)
		kfifo_put(&test, &i);

	/* show the number of used elements */
	printf("fifo len: %u\n", kfifo_len(&test));

	/* get max of 5 bytes from the fifo */
	i = kfifo_out(&test, buf, 5);
	printf("buf: %.*s\n", i, buf);

	/* get max of 2 elements from the fifo */
	ret = kfifo_out(&test, buf, 2);
	printf("ret: %d\n", ret);
	/* and put it back to the end of the fifo */
	ret = kfifo_in(&test, buf, ret);
	printf("ret: %d\n", ret);

	/* skip first element of the fifo */
	printf("skip 1st element\n");
	kfifo_skip(&test);

	/* put values into the fifo until is full */
	for (i = 20; kfifo_put(&test, &i); i++)
		;

	printf("queue len: %u\n", kfifo_len(&test));

	/* show the first value without removing from the fifo */
	if (kfifo_peek(&test, &i))
		printf("peek the first value in fifo : %d\n", i);

	/* check the correctness of all values in the fifo */
	j = 0;
	while (kfifo_get(&test, &i)) {
		printf("item_%d = %d\n", j, i);
		if (i != expected_result[j++]) {
			printf("value mismatch: test failed\n");
			return -EIO;
		}
	}
	if (j != ARRAY_SIZE(expected_result)) {
		printf("size mismatch: test failed\n");
		return -EIO;
	}
	printf("test passed\n");

	return 0;
}



int main(int argc, char *argv[]) {

	int ret;
	printf("----模拟内核队列测试程序 END----\n");
	
	
	ret = kfifo_alloc(&test, FIFO_SIZE);
	if (ret) {
		printf("error kfifo_alloc\n");
		return ret;
	}
	
	if (testfunc() < 0) {
		kfifo_free(&test);
		return -EIO;
	}

	
	
}
