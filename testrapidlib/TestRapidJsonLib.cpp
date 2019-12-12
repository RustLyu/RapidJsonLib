#include <iostream>

#include "DllFunc.h"

int main()
{
	void* ctx = nullptr;
	if (!CreateContext(ctx))
	{
		DestoryContext(ctx);
		ctx = nullptr;
		return -1;
	}
	SetJsonPath(ctx, "./test.json");
	//load(ctx);
	char dst[100] = { 0 };
	//AddNode_s(ctx, "bei_jing", "LLLLSK","333");
	//ModifyNode_s(ctx, "bei_jing", "LLLLSK", "你好");
	int age = 0;
	//GetNode_i(ctx, age, 3, "SHAANXI", "Obj", "age");
	//char dst[100];
	//GetNode_s(ctx, dst, 1, "GG");
	memset(dst, 0, 100);
	GetNode_s(ctx, dst, 2, "bei_jing","address");
	//ModifyNode_s(ctx, "addNode_777_v", 1, "addnode1_key");
	//ModifyNode_s(ctx, "addNode_999_v", 2, "SHAANXI", "addnode1_key");
	//RemoveNode(ctx,1,"GG");
	//RemoveNode(ctx, 3, "SHAANXI", "Obj", "age");
	//AddNode_s(ctx, "addNode_2", 2, "SHAANXI", "addnode1_key");

	//AddNode_i(ctx, "SHAANXI", "KKKKKKKK", 11);

	std::cout << dst << std::endl;

	DestoryContext(ctx);
	ctx = nullptr;

	//std::cout << "Hello World!\n"; 
}
