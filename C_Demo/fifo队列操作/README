## 实现队列功能的文件说明
此工程为模拟内核循环队列的例子,所有队列实现的函数全部移植自内核,可以参看相应的内核文件列表:
* 内核环形队列实现文件: `lib/kfifo.c include/linux/kfifo.h`
* 内核环形队列使用例子: samples/kfifo/Bytestream-example.c

## 各个文件功能解释

* `fifo_demo.c` 整个fifo测试的例子, 通过操作32位长度的fifo,实现数据在队列中的入队,出对,忽略元素,预览元素等
* `common.h` 队列操作中需要用到的公共文件
* `fifo_emu.c fifo_emu.h` 以emu结尾的文件模拟了队列的实现. 此为移植内核的队列实现,去除了很多不必要的函数,改造了一些应用层和内核层的差别,如果`kmalloc-->malloc`,`printk-->printf`等
* `barrier_emu.h  error_base_emu.h` 此为`fifo_emu.c fifo_emu.h`两个文件需要用到的一些变量, 仿造内核文件进行移植,同样以emu结尾,方便找到内核中相应的文件进行对比.
* Makefile 整个队列示例编译的Makefile,直接在ubuntu环境下进入到工程目录执行make命令即可. 如果时交叉编译,请另行修改此文件

## 此代码执行的输出如下:

```log
----模拟内核队列测试程序 END----
byte stream fifo test start
fifo len: 15
buf: hello
ret: 2
ret: 2
skip 1st element
queue len: 32
peek the first value in fifo : 3
item_0 = 3
item_1 = 4
item_2 = 5
item_3 = 6
item_4 = 7
item_5 = 8
item_6 = 9
item_7 = 0
item_8 = 1
item_9 = 20
item_10 = 21
item_11 = 22
item_12 = 23
item_13 = 24
item_14 = 25
item_15 = 26
item_16 = 27
item_17 = 28
item_18 = 29
item_19 = 30
item_20 = 31
item_21 = 32
item_22 = 33
item_23 = 34
item_24 = 35
item_25 = 36
item_26 = 37
item_27 = 38
item_28 = 39
item_29 = 40
item_30 = 41
item_31 = 42
test passed

```
