#ifndef DLL_OUT_H
#define DLL_OUT_H

#ifdef RapidJson_Export
#define RapidJson_API __declspec(dllexport)
#else
#define RapidJson_API __declspec(dllimport)
#endif

//class JsonOperater;

extern "C" RapidJson_API int CreateContext(void*& ctx);
extern "C" RapidJson_API int DestoryContext(void* ctx);

extern "C" RapidJson_API void SetJsonPath(void* ctx, const char* path);

//extern "C" RapidJson_API bool load(void* ctx);

extern "C" RapidJson_API int ModifyNode_s(void* ctx, const char* v, int n, ...);
extern "C" RapidJson_API int ModifyNode_i(void* ctx, const int v, int n, ...);
extern "C" RapidJson_API int ModifyNode_b(void* ctx, const bool v, int n, ...);
extern "C" RapidJson_API int ModifyNode_f(void* ctx, const float v, int n, ...);

extern "C" RapidJson_API int RemoveNode(void* ctx, int n, ...);

extern "C" RapidJson_API int AddNode_s(void* ctx, const char* v, int n, ...);
extern "C" RapidJson_API int AddNode_i(void* ctx, const int v, int n, ...);
extern "C" RapidJson_API int AddNode_b(void* ctx, const bool v, int n, ...);
extern "C" RapidJson_API int AddNode_f(void* ctx, const float v, int n, ...);

extern "C" RapidJson_API int GetNode_s(void* ctx, char* v, int n, ...);
extern "C" RapidJson_API int GetNode_i(void* ctx, int& v, int n, ...);
extern "C" RapidJson_API int GetNode_b(void* ctx, bool& v, int n, ...);
extern "C" RapidJson_API int GetNode_f(void* ctx, float& v, int n, ...);

#endif // DLL_OUT_H