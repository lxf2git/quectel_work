#include"main.h"  //"fun1.h" <unistd.h>
//#include"fun1.h"  //stdio void fun1()

  static int a=100;
int main()
{
	printf("i am main\n");	
	fun1();
	
	printf("good bye main\n");
	exit(0);
}
