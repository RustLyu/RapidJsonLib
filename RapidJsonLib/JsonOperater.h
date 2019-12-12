#ifndef JSON_OPERATER_H
#define JSON_OPERATER_H

#define MAX_STR_LEN 100
#define bzero(str, size) memset(str, 0, size)

#include <iostream>
#include <map>

#include "../include/rapidjson/document.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/stringbuffer.h"

class JsonOperater
{
public:
	explicit JsonOperater();
	~JsonOperater();

public:
	void setPath(const char* path)
	{
		memcpy(path_, path, strlen(path)+1);
	}

	int loadJson();

	int GetValue(char* dst, const int n, va_list ap);
	int GetValue(int& dst, const int n, va_list ap);
	int GetValue(bool& dst, const int n, va_list ap);
	int GetValue(float& dst, const int n, va_list ap);

	int AddNode(const char* dst, const int n, va_list ap);
	int AddNode(const int dst, const int n, va_list ap);
	int AddNode(const bool dst, const int n, va_list ap);
	int AddNode(const float dst, const int n, va_list ap);

	int ModifyNode(const char* dst, const int n, va_list ap);
	int ModifyNode(const int dst, const int n, va_list ap);
	int ModifyNode(const bool dst, const int n, va_list ap);
	int ModifyNode(const float dst, const int n, va_list ap);

	int RemoveNode(const int n, va_list ap);

private:
	char path_[MAX_STR_LEN];
	std::map<std::string, std::map<std::string, std::string>> valueMap_;

private:
	bool checkFatherExist(const char* f);
	bool checkChildExist(const char* f, const char* c);
	bool loadJson(rapidjson::Document& dom);
	bool closeJson(const rapidjson::Document& dom);
	int paraseValue(rapidjson::Value::ConstMemberIterator start, rapidjson::Value::ConstMemberIterator end, std::map<std::string, std::string>& ret);
	int paraseValue(rapidjson::Value::ConstMemberIterator start, rapidjson::Value::ConstMemberIterator end, std::map<std::string, std::map<std::string, std::string>>& ret);
};

#endif // JSON_OPERATER_H
