#ifndef _MICORBLOG_H_
#define _MICORBLOG_H_
//一下内容请仔细阅读!
/*要求*
 * 代码要有注释（变量名 函数名都干啥的 写清楚了）
 * 必须用这个俩个头文件、自己要添加跟我说
 * 链表必须用指针
 * 初始化链表需要把嵌套的链表也初始化
 * 功能函数类型和参数不能更改
 * 注意： 客户端功能要和服务器功能对应好
 * 所有代码自己测试完成再给我
 * 别把测试用的代码打上
 */
typedef struct friend	//好友
{
		int s_id;	//好友的ID
		struct friend *Prev;
		struct friend *Next;
}SFriend, *PFriend;

typedef struct comment //评论
{
		char *s_text; //评论内容
		char s_user_name[20]; //评论用户昵称
		struct comment *prev;
		struct comment *next;
}SComment, *PComment;

typedef struct microblog //发表的微博
{
		char *s_text; //微博内容
		struct comment s_comment; //评论
		int s_praise; // 赞
		struct weibo *prev;
		struct weibo *next;
}SMicroblog, *PMicroblog;

typedef struct user_basic_info // 用户基本信息
{
		int s_id;
		int s_age;
		char s_user_name [20];
		char s_passwd [20];
		char s_nick_name[20];
		char s_sex [2] ;
}SUer_basic_info, *PUser_basic_info;

typedef struct user_info
{
		struct friend* s_friend;//好友
		struct friend* s_fanc;//粉丝
	struct user_basic_info s_user_basic_info; //用户基本信息
		struct microblog* s_microblog; //发表的微博
		struct user_info*Prev;
		struct user_info *Next;
}SUser_info, *PUser_info;

PUser_info puihead;

enum{ LOGIN=1, REGISTER, SEARCH, ATTENTION, FANS, PUBLISH, FORWARD, COMMENT, VIEW };
//	登录、	注册、	 搜索、   关注、  取消关注、发表微博、转发微博、评论微博、查看用户微博

void Login(void *confd);//登录
void Register(void *confd);//注册
void Search(void *confd);//搜索
void Attention(void *confd);//关注
void Cancel_attention(void *confd);//取消关注
void Publish_microblog(void *confd);//发表微博
void Forwar_microblog(void *confd);//转发微博
void Comment_micorblog(void *confd);//评论微博
void View_micorblog(void *confd);//查看用户微博
//其他函数
#endif
