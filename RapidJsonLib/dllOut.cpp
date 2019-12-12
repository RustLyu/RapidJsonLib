#include "dllOut.h"
#include "JsonOperater.h"
#include <stdarg.h>

int CreateContext(void*& ctx)
{
	ctx = new JsonOperater();
	return 1;
}

int DestoryContext(void * ctx)
{
	delete ctx;
	return 1;
}

JsonOperater* ConvertPtr(void* ctx)
{
	return reinterpret_cast<JsonOperater*>(ctx);
}

void SetJsonPath(void * ctx, const char * path)
{
	ConvertPtr(ctx)->setPath(path);
}

bool load(void * ctx)
{
	return ConvertPtr(ctx)->loadJson();
}

extern "C" int ModifyNode_s(void* ctx, const char * v, int n, ...)
{
	va_list vp;
	va_start(vp, n);
	int ret = ConvertPtr(ctx)->ModifyNode(v, n, vp);
	va_end(vp);
	return ret;
}

extern "C" int ModifyNode_i(void* ctx, const int v, int n, ...)
{
	va_list vp;
	va_start(vp, n);
	int ret =ConvertPtr(ctx)->ModifyNode(v, n, vp);
	va_end(vp);
	return ret;
}

extern "C" int ModifyNode_b(void* ctx, const bool v, int n, ...)
{
	va_list vp;
	va_start(vp, n);
	int ret = ConvertPtr(ctx)->ModifyNode(v, n, vp);
	va_end(vp);
	return ret;
}

extern "C" int ModifyNode_f(void* ctx, const float v, int n, ...)
{
	va_list vp;
	va_start(vp, n);
	int ret = ConvertPtr(ctx)->ModifyNode(v, n, vp);
	va_end(vp);
	return ret;
}

extern "C" int RemoveNode(void * ctx, int n, ...)
{
	va_list vp;
	va_start(vp, n);
	int ret = ConvertPtr(ctx)->RemoveNode(n, vp);
	va_end(vp);
	return ret;
}

extern "C" int AddNode_s(void* ctx, const char * v, int n, ...)
{
	va_list vp;
	va_start(vp, n);
	int ret = ConvertPtr(ctx)->AddNode(v, n, vp);
	va_end(vp);
	return ret;
}

extern "C" int AddNode_i(void* ctx, const int v, int n, ...)
{
	va_list vp;
	va_start(vp, n);
	int ret = ConvertPtr(ctx)->AddNode(v, n, vp);
	va_end(vp);
	return ret;
}

extern "C" int AddNode_b(void* ctx, const bool v, int n, ...)
{
	va_list vp;
	va_start(vp, n);
	int ret = ConvertPtr(ctx)->AddNode(v, n, vp);
	va_end(vp);
	return ret;
}

extern "C" int AddNode_f(void* ctx, const float v, int n, ...)
{
	va_list vp;
	va_start(vp, n);
	int ret = ConvertPtr(ctx)->AddNode(v, n, vp);
	va_end(vp);
	return ret;
}

extern "C" int GetNode_s(void* ctx, char * v, int n, ...)
{
	va_list vp;
	va_start(vp, n);
	int ret = ConvertPtr(ctx)->GetValue(v, n, vp);
	va_end(vp);
	return ret;
}

extern "C" int GetNode_i(void* ctx, int & v, int n, ...)
{
	va_list vp;
	va_start(vp, n);
	int ret = ConvertPtr(ctx)->GetValue(v, n, vp);
	va_end(vp);
	return ret;
}

extern "C" int GetNode_b(void* ctx, bool & v, int n, ...)
{
	va_list vp;
	va_start(vp, n);
	int ret = ConvertPtr(ctx)->GetValue(v, n, vp);
	va_end(vp);
	return ret;
}

extern "C" int GetNode_f(void* ctx, float & v, int n, ...)
{
	va_list vp;
	va_start(vp, n);
	int ret = ConvertPtr(ctx)->GetValue(v, n, vp);
	va_end(vp);
	return ret;
}
