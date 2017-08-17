/**
* 文件功能: 
* @总体功能介绍:	移植内核list.h中的链表实现到list_emu.h中,以便应用层程序能使用内核官方定义的链表
* @list_emu.h: 对内核list.h文件的移植,主要是链表结构以及操作例程
* @list_demo.h: 业务逻辑相关的头文件
* 
* 作者: 杨佛根
* 日期: 2017.08.17
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h> 
/**
* 模拟内核链表实现的头文件 "list_emu.h"
*/
#include "list_emu.h"
#include "list_demo.h"



int main(int argc, char *argv[]) {
	

	int temp = 0;
	struct person *mPerson = NULL;
	struct person *tmp, *tmp_storage, tmp_mov;
	struct list_head *pos, *pos_tmp;
	pthread_mutex_t mutex;
	pthread_mutex_init (&mutex,NULL);
	
	/**
	* 三个链表头的定义 与 初始化
	*/
	struct person kp_person;   	
	struct person height_person;
	struct person weight_person;
	
	INIT_LIST_HEAD(&kp_person.list);
	INIT_LIST_HEAD(&height_person.list);
	INIT_LIST_HEAD(&weight_person.list);
	
	
	printf("----模拟内核链表测试程序 BEGIN----\n");

	/**
	* 此处为手动创建链表数据的代码,暂且注释
	*/	
	#if 0
	char ch1[10], ch2[10], ch3[10], ch4[10];
	while(0 != strcmp("done",ch4)){
		printf("----请输入工号----:\n");
		scanf("%s",ch1);
		printf("----请输入身高----:\n");
		scanf("%s",ch2);
		printf("----请输入重量----:\n");
		scanf("%s",ch3);
		
		mPerson = (struct person*)malloc(sizeof(mPerson));
		mPerson->id = atoi(ch1);
		mPerson->height = atoi(ch2);
		mPerson->weight = atoi(ch3);		

		printf("----生成的一条数据为: id=%d, height=%d, weight=%d  ----:\n", mPerson->id, mPerson->height, mPerson->weight);
		
		//链表的节点增加: 方法一: list_add_tail(new, head), 作用是添加new节点：将new添加到head之前，即将new添加到环形链表的末尾
		//链表的节点增加: 方法二: list_add(new, head), 作用是添加new节点：将new添加到head之后，是new称为head的后继节点
		printf("----加入kp_person_list链表----\n");
		list_add_tail(&mPerson->list, &kp_person.list);
		printf("----kp_person 工号:%d 高度=%d, 重量=%d----:\n", kp_person->id, kp_person->height, kp_person->weight);
		printf("----完成请输入done,继续请输入任意字符----:\n");
		scanf("%s",ch4);
	}
	#endif
	
	
	int id, height = 165, weight = 80;
	for (id = 81222; height< 210; height += 10, weight += 5, id +=5){
		mPerson = (struct person*)malloc(sizeof(mPerson));
		mPerson->id = id;
		mPerson->height = height;
		mPerson->weight = weight;
		
		/**
		* 这里如果用 "list_add_tail(&mPerson->list, &kp_person.list);" 会出现内存段错误,暂时为发现原因
		*/
		list_add(&mPerson->list, &kp_person.list);
	}
	
	
	
	/**
	* 链表的遍历方法一:list_for_each
	*/
	list_for_each(pos, &kp_person.list){
		tmp = list_entry(pos, struct person, list); 
		printf("----list_for_each 工号:%d 高度=%d, 重量=%d----:\n", tmp->id, tmp->height, tmp->weight);
		sleep(1);
	}
		
	/**
	* 链表的遍历方法二:list_for_each_entry
	* list_for_each_entry相对于list_for_each的使用更加简洁
	*/
	list_for_each_entry(tmp, &kp_person.list, list){ 
		printf("----list_for_each_entry 工号:%d 高度=%d, 重量=%d----:\n", tmp->id, tmp->height, tmp->weight);		
		sleep(1);
	}
	
	pthread_mutex_lock (&mutex);
	
	
	list_for_each_safe(pos, pos_tmp, &kp_person.list){
		tmp = list_entry(pos, struct person, list); 
		if(200 < tmp->height){
			/**
			* 链表删除操作
			*/
			printf("----去除高度>200的人的链表: 工号:%d 高度=%d, 重量=%d----:\n", tmp->id, tmp->height, tmp->weight);
			list_del(&tmp->list);
		}else if(180 < tmp->height){
			/**
			* 链表移动操作
			*/
			printf("----创建高度>180的人的链表: 工号:%d 高度=%d, 重量=%d----:\n", tmp->id, tmp->height, tmp->weight);
			list_move_tail(&tmp->list, &height_person.list);
		}
		sleep(1);
	}
	
	/**
	* 链表的删除方法: list_del
	* 链表的移动方法: list_move_tail
	* 遍历时如果有删除操作,需要用安全函数: list_for_each_entry_safe
	*/
	list_for_each_entry_safe(tmp, tmp_storage, &kp_person.list, list){	
		if(85 <= tmp->weight){
			/**
			*  list_move_tail等效于如下两句, 这里涉及到链表的删除, 移动
			*  list_del(&tmp->list);
			*  list_add_tail(&tmp->list, &height_person.list);
			*/
			printf("----创建重量>85的数据链表: 工号:%d 高度=%d, 重量=%d----:\n", tmp->id, tmp->height, tmp->weight);
			list_move_tail(&tmp->list, &weight_person.list);
		}
	}

	pthread_mutex_unlock(&mutex);
	
	printf("\n");
	printf("----各类型链表创建成功,开始打印 ... ----:\n");
	printf("\n");
	
	list_for_each_entry(tmp, &kp_person.list, list){ 
		printf("----kp list_for_each_entry 工号:%d 高度=%d, 重量=%d----:\n", tmp->id, tmp->height, tmp->weight);		
		sleep(1);
	}
	
	printf("\n");
	list_for_each_entry(tmp, &height_person.list, list){ 
		printf("----height list_for_each_entry 工号:%d 高度=%d, 重量=%d----:\n", tmp->id, tmp->height, tmp->weight);		
		sleep(1);
	}
	
	
	
	printf("\n");
	list_for_each_entry(tmp, &weight_person.list, list){ 
		printf("----weight list_for_each_entry 工号:%d 高度=%d, 重量=%d----:\n", tmp->id, tmp->height, tmp->weight);		
		sleep(1);
	}
	
	printf("\n");
	printf("----模拟内核链表测试程序 END----\n");
	
}
