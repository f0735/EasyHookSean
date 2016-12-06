// NativeApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <NativeDll.h>

#if 0
#include <iostream>     // std::cout
#include <functional>   // std::bind

using namespace std;
using namespace std::placeholders;

typedef std::function<void()> fp;
typedef std::function<int(char* a, int b)> fpsean;
typedef std::function<int()> fpsean1;
void g_fun()
{
	cout << "g_fun()" << endl;
}
int sean_fun(char* a, int b)
{
	cout << a << endl;
	return b;
}
class A
{
private:
	int bbb;
	int ccc;
public:
	static void A_fun_static()
	{
		cout << "A_fun_static()" << endl;
	}
	void A_fun()
	{
		cout << "A_fun()" << endl;
	}
	void A_fun_int(int i)
	{
		cout << "A_fun_int() " << i << endl;
	}
	int b_func(char* a, int b)
	{
		cout << a << endl;
		return b;
	}
	int c_func()
	{
		return 11;
	}

	//非静态类成员，因为含有this指针，所以需要使用bind
	void init()
	{
		fp fp1 = std::bind(&A::A_fun, this);
		fp1();
	}

	void init2()
	{
		typedef std::function<void(int)> fpi;
		//对于参数要使用占位符 std::placeholders::_1
		fpi f = std::bind(&A::A_fun_int, this, std::placeholders::_1);
		f(5);
	}
};
int main()
{
	//绑定到全局函数
	fp f2 = fp(&g_fun);
	f2();

	//绑定到类静态成员函数
	fp f1 = fp(&A::A_fun_static);
	f1();

	A().init();
	A().init2();

	fpsean tmp = fpsean(&sean_fun);
	tmp("asdf", 2);

	A a1;
	fp fp1 = std::bind(&A::A_fun, &a1);
	fp1();

	fpsean tmp1 = std::bind(&A::b_func, a1,_1,_2);
	tmp1("asdf", 2);

	fpsean1 tmp2 = std::bind(&A::c_func, &a1);
	tmp2();

	return 0;
}
#endif
int main()
{
	int i = 0;
	
	i = fnNativeDll();

	printf("%d", i);

	while (1)
	{
		Sleep(5000);
		printf("I'm Sleeping!\n");
	}

    return 0;
}

