

#define ERR 1
#define OK 0

struct person{
    unsigned int id;            /* 工号 */                          
    unsigned int height;        /* 高度 */
    unsigned int weight;        /* 重量 */
    struct list_head list;     /* 链表节点 */
};
