#include <iostream>
#include <fstream>
#include <string>

#include "../include/rapidjson/document.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/stringbuffer.h"

#include "SuperValue.h"
#include <vector>
#include <map>

//int test_rapidjson_parse()
//{
//#ifdef _MSC_VER
//	const char* file_name = "./src.json";
//#else
//	const char* file_name = "testdata/json.data";
//#endif
//	std::ifstream in(file_name);
//	if (!in.is_open())
//	{
//		fprintf(stderr, "fail to read json file: %s\n", file_name);
//		return -1;
//	}
//
//	std::string json_content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
//	in.close();
//
//	rapidjson::Document dom;
//	if (!dom.Parse(json_content.c_str()).HasParseError())
//	{
//		if (dom.HasMember("name") && dom["name"].IsString())
//		{
//			fprintf(stdout, "name: %s\n", dom["name"].GetString());
//		}
//
//		if (dom.HasMember("address") && dom["address"].IsString())
//		{
//			fprintf(stdout, "address: %s\n", dom["address"].GetString());
//		}
//
//		if (dom.HasMember("age") && dom["age"].IsInt())
//		{
//			fprintf(stdout, "age: %d\n", dom["age"].GetInt());
//		}
//
//		const char* tmp = "xxx";
//		if (!dom.HasMember(tmp))
//		{
//			fprintf(stdout, "Warning: it has no member: %s\n", tmp);
//		}
//
//		if (dom.HasMember("value1") && dom["value1"].IsArray())
//		{
//			const rapidjson::Value& arr = dom["value1"];
//			for (int i = 0; i < arr.Size(); ++i)
//			{
//				const rapidjson::Value& tmp = arr[i];
//
//				fprintf(stdout, "value1:\ni = %d:", i);
//				for (int j = 0; j < tmp.Size(); ++j)
//				{
//					if (tmp[j].IsInt())
//						fprintf(stdout, "%d, ", tmp[j].GetInt());
//					if (tmp[j].IsFloat())
//						fprintf(stdout, "%.1f, ", tmp[j].GetFloat());
//				}
//				fprintf(stdout, "\n");
//			}
//		}
//
//		if (dom.HasMember("value2") && dom["value2"].IsArray())
//		{
//			const rapidjson::Value& arr = dom["value2"];
//
//			fprintf(stdout, "value2: ");
//			for (int i = 0; i < arr.Size(); ++i)
//			{
//				fprintf(stdout, "%.2f, ", arr[i].GetFloat());
//			}
//			fprintf(stdout, "\n");
//		}
//
//		if (dom.HasMember("bei_jing") && dom["bei_jing"].IsObject())
//		{
//			const rapidjson::Value& obj = dom["bei_jing"];
//
//			if (obj.HasMember("address") && obj["address"].IsString())
//			{
//				fprintf(stdout, "address: %s\n", obj["address"].GetString());
//			}
//
//			if (obj.HasMember("car") && obj["car"].IsBool())
//			{
//				fprintf(stdout, "car: %d\n", obj["car"].GetBool());
//			}
//
//			if (obj.HasMember("cat") && obj["cat"].IsBool())
//			{
//				fprintf(stdout, "cat: %d\n", obj["cat"].GetBool());
//			}
//		}
//
//		if (dom.HasMember("shan_dong") && dom["shan_dong"].IsObject())
//		{
//			const rapidjson::Value& obj = dom["shan_dong"];
//
//			if (obj.HasMember("address") && obj["address"].IsString())
//			{
//				fprintf(stdout, "address: %s\n", obj["address"].GetString());
//			}
//
//			if (obj.HasMember("value1") && obj["value1"].IsArray())
//			{
//				const rapidjson::Value& arr = obj["value1"];
//				for (int i = 0; i < arr.Size(); ++i)
//				{
//					//std::cout << "1111" << std::endl;
//					for (auto cell = arr[i].MemberBegin(); cell != arr[i].MemberEnd(); ++cell)
//					{
//						fprintf(stdout, "iter json name: %s, type: %s\n", cell->name.GetString(), cell->value.GetString());
//						//std::cout << cell.first << "===" << cell.second << std::endl;
//					}
//					//std::cout << arr[i].FindMember << std::endl;
//				}
//
//				/*if (arr[0].HasMember("ji_nan") && arr[0]["ji_nan"].IsString())
//				{
//					fprintf(stdout, "ji_nan: %s\n", arr[0]["ji_nan"].GetString());
//				}
//
//				if (arr[0].HasMember("tai_an") && arr[0]["tai_an"].IsString())
//				{
//					fprintf(stdout, "tai_an: %s\n", arr[0]["tai_an"].GetString());
//				}*/
//			}
//		}
//	}
//	else
//	{
//		fprintf(stderr, "fail to parse json file: %s\n", file_name);
//		return -1;
//	}
//
//	// iter json
//	for (rapidjson::Value::ConstMemberIterator iter = dom.MemberBegin(); iter != dom.MemberEnd(); ++iter)
//	{
//		fprintf(stdout, "iter json name: %s, type: %d\n", iter->name.GetString(), iter->value.GetType());
//	}
//
//	return 0;
//}
//
//int test_rapidjson_write()
//{
//	rapidjson::StringBuffer buf;
//	rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
//
//	writer.StartObject();
//
//	writer.Key("name"); writer.String("spring");
//	writer.Key("address"); writer.String("北京");
//	writer.Key("age"); writer.Int(30);
//
//	writer.Key("value1");
//	writer.StartArray();
//	writer.StartArray();
//	writer.Double(23); writer.Double(43); writer.Double(-2.3); writer.Double(6.7); writer.Double(90);
//	writer.EndArray();
//
//	writer.StartArray();
//	writer.Int(-9); writer.Int(-19); writer.Int(10); writer.Int(2);
//	writer.EndArray();
//
//	writer.StartArray();
//	writer.Int(-5); writer.Int(-55);
//	writer.EndArray();
//	writer.EndArray();
//
//	writer.Key("value2");
//	writer.StartArray();
//	writer.Double(13.3); writer.Double(1.9); writer.Double(2.10);
//	writer.EndArray();
//
//	writer.Key("bei_jing");
//	writer.StartObject();
//	writer.Key("address"); writer.String("海淀");
//	writer.Key("car"); writer.Bool(false);
//	writer.Key("cat"); writer.Bool(true);
//	writer.EndObject();
//
//	writer.Key("shan_dong");
//	writer.StartObject();
//	writer.Key("address"); writer.String("济南");
//	writer.Key("value1");
//	writer.StartArray();
//	writer.Key("ji_nan"); writer.String("趵突泉");
//	writer.Key("tai_an"); writer.String("泰山");
//	writer.EndArray();
//	writer.EndObject();
//
//	writer.EndObject();
//
//	const char* json_content = buf.GetString();
//	fprintf(stdout, "json content: %s\n", json_content);
//
//#ifdef _MSC_VER
//	const char* file_name = "./out.json";
//#else
//	const char* file_name = "testdata/out.json";
//#endif
//	std::ofstream outfile;
//	outfile.open(file_name);
//	if (!outfile.is_open())
//	{
//		fprintf(stderr, "fail to open file to write: %s\n", file_name);
//		return -1;
//	}
//
//	outfile << json_content << std::endl;
//	outfile.close();
//
//	return 0;
//}
//
//int modifyMember(std::string key, std::string value)
//{
//	const char* file_name = "./src.json";
//	std::ifstream in(file_name);
//	if (!in.is_open())
//	{
//		fprintf(stderr, "fail to read json file: %s\n", file_name);
//		return -1;
//	}
//
//	std::string json_content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
//	in.close();
//
//	rapidjson::Document dom;
//	if (!dom.Parse(json_content.c_str()).HasParseError())
//	{
//		rapidjson::Value& s = dom[key.c_str()];
//		s.SetString(value.c_str(), value.size(), dom.GetAllocator());
//
//
//		/*rapidjson::Value keyV(key.c_str(), dom.GetAllocator());
//		dom.AddMember(keyV, s, dom.GetAllocator());*/
//
//		rapidjson::StringBuffer SB;
//		rapidjson::Writer<rapidjson::StringBuffer> writer(SB);
//		dom.Accept(writer);
//
//		std::cout << SB.GetString() << std::endl;
//	}
//	return 0;
//}
//
//int deleteMember(std::string key)
//{
//	const char* file_name = "./src.json";
//	std::ifstream in(file_name);
//	if (!in.is_open())
//	{
//		fprintf(stderr, "fail to read json file: %s\n", file_name);
//		return -1;
//	}
//
//	std::string json_content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
//	in.close();
//
//	rapidjson::Document dom;
//	if (!dom.Parse(json_content.c_str()).HasParseError())
//	{
//		dom.RemoveMember(key.c_str());
//
//		rapidjson::StringBuffer SB;
//		rapidjson::Writer<rapidjson::StringBuffer> writer(SB);
//		dom.Accept(writer);
//
//		std::cout << SB.GetString() << std::endl;
//	}
//	in.close();
//	return 0;
//}
//
//int addMember(std::string key, std::string value)
//{
//	const char* file_name = "./src.json";
//	std::ifstream in(file_name);
//	if (!in.is_open())
//	{
//		fprintf(stderr, "fail to read json file: %s\n", file_name);
//		return -1;
//	}
//
//	std::string json_content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
//	in.close();
//
//	rapidjson::Document dom;
//	if (!dom.Parse(json_content.c_str()).HasParseError())
//	{
//		rapidjson::Document::AllocatorType& allocator = dom.GetAllocator();
//		rapidjson::Value name;
//		name.SetString(value.c_str(), value.size());
//
//		rapidjson::Value keyV;
//		keyV.SetString(key.c_str(), key.size());
//
//		dom.AddMember(keyV, name, allocator);
//
//		rapidjson::StringBuffer SB;
//		rapidjson::Writer<rapidjson::StringBuffer> writer(SB);
//		dom.Accept(writer);
//
//		std::cout << SB.GetString() << std::endl;
//	}
//	in.close();
//	return 0;
//}
//
//int findMember(std::string key)
//{
//	return 0;
//}
//
//void paraseValue(rapidjson::Value::ConstMemberIterator start, rapidjson::Value::ConstMemberIterator end, std::vector<void*>& ret)
//{
//	for (auto cell = start; cell != end; ++cell)
//	{
//		fprintf(stdout, "iter json name: %s, type: %d\n", cell->name.GetString(), cell->value.GetType());
//		if (cell->value.IsArray())
//		{
//			if (cell->value[0].IsArray())
//			{
//				jValue_SVV* c = new jValue_SVV();
//				c->getValue().resize(cell->value.Size());
//				for (int i = 0; i < cell->value.Size(); ++i)
//				{
//					if (cell->value[i].IsArray())
//					{
//						c->setType(cell->name.GetString());
//						const rapidjson::Value& v = cell->value[i];
//						for (int j = 0; j < v.Size(); ++j)
//						{
//							c->getValue()[i].push_back(v[j].GetFloat());
//						}
//
//					}
//				}
//				ret.push_back(c);
//			}
//			else if (cell->value[0].IsObject())
//			{
//				for (int i = 0; i < cell->value.Size(); ++i)
//					paraseValue(cell->value[i].MemberBegin(), cell->value[i].MemberEnd(), ret);
//			}
//			else
//			{
//				jValue_SV* c = new jValue_SV();
//				c->setType(cell->name.GetString());
//
//				for (int i = 0; i < cell->value.Size(); ++i)
//				{
//					c->getValue().push_back(cell->value[i].GetFloat());
//				}
//				ret.push_back(c);
//			}
//			jValue_SV* c = new jValue_SV();
//			c->setType(cell->name.GetString());
//			c->getValue().resize(cell->value.Size());
//		}
//		else if (cell->value.IsInt())
//		{
//			jValue_SI* v = new jValue_SI();
//			v->setType(cell->name.GetString());
//			v->setValue(cell->value.GetInt());
//			ret.push_back(v);
//		}
//		else if (cell->value.IsString())
//		{
//			jValue_SS* v = new jValue_SS();
//			v->setType(cell->name.GetString());
//			v->setValue(cell->value.GetString());
//			ret.push_back(v);
//		}
//		else if (cell->value.IsFloat())
//		{
//			jValue_SF* v = new jValue_SF();
//			v->setValue(cell->value.GetFloat());
//			ret.push_back(v);
//		}
//		else if (cell->value.IsBool())
//		{
//			jValue_SB* v = new jValue_SB();
//			v->setType(cell->name.GetString());
//			v->setValue(cell->value.GetBool());
//			ret.push_back(v);
//		}
//		else if (cell->value.IsObject())
//		{
//			paraseValue(cell->value.MemberBegin(), cell->value.MemberEnd(), ret);
//		}
//	}
//}
//
//void paraseValue(rapidjson::Value::ConstMemberIterator start, rapidjson::Value::ConstMemberIterator end, std::map<std::string, void*>& ret)
//{
//	for (auto cell = start; cell != end; ++cell)
//	{
//		fprintf(stdout, "iter json name: %s, type: %d\n", cell->name.GetString(), cell->value.GetType());
//		if (cell->value.IsArray())
//		{
//			if (cell->value[0].IsArray())
//			{
//				jValue_SVV* c = new jValue_SVV();
//				c->getValue().resize(cell->value.Size());
//				for (int i = 0; i < cell->value.Size(); ++i)
//				{
//					if (cell->value[i].IsArray())
//					{
//						c->setType(cell->name.GetString());
//						const rapidjson::Value& v = cell->value[i];
//						for (int j = 0; j < v.Size(); ++j)
//						{
//							c->getValue()[i].push_back(v[j].GetFloat());
//						}
//					}
//				}
//				std::string valueKey = cell->name.GetString();
//				jValue_SM* l = new jValue_SM();
//				l->getValue().insert(std::pair<std::string, void*>(valueKey, c));
//				ret.insert(std::pair<std::string, void*>(valueKey, l));
//			}
//			else if (cell->value[0].IsObject())
//			{
//				for (int i = 0; i < cell->value.Size(); ++i)
//				{
//					jValue_SM* v = new jValue_SM();
//					v->setType(cell->name.GetString());
//					std::string valueKey = cell->name.GetString();
//					ret.insert(std::pair<std::string, void*>(valueKey, v));
//					paraseValue(cell->value[i].MemberBegin(), cell->value[i].MemberEnd(), v->getValue());
//				}
//			}
//			else
//			{
//				jValue_SV* c = new jValue_SV();
//				c->setType(cell->name.GetString());
//
//				for (int i = 0; i < cell->value.Size(); ++i)
//				{
//					c->getValue().push_back(cell->value[i].GetFloat());
//				}
//				std::string valueKey = cell->name.GetString();
//				ret.insert(std::pair<std::string, void*>(valueKey, c));
//			}
//			jValue_SV* c = new jValue_SV();
//			c->setType(cell->name.GetString());
//			c->getValue().resize(cell->value.Size());
//		}
//		else if (cell->value.IsInt())
//		{
//			jValue_SI* v = new jValue_SI();
//			v->setType(cell->name.GetString());
//			v->setValue(cell->value.GetInt());
//			std::string valueKey = cell->name.GetString();
//			ret.insert(std::pair<std::string, void*>(valueKey, v));
//		}
//		else if (cell->value.IsString())
//		{
//			jValue_SS* v = new jValue_SS();
//			v->setType(cell->name.GetString());
//			v->setValue(cell->value.GetString());
//			std::string valueKey = cell->name.GetString();
//			ret.insert(std::pair<std::string, void*>(valueKey, v));
//		}
//		else if (cell->value.IsFloat())
//		{
//			jValue_SF* v = new jValue_SF();
//			v->setValue(cell->value.GetFloat());
//			std::string valueKey = cell->name.GetString();
//			ret.insert(std::pair<std::string, void*>(valueKey, v));
//		}
//		else if (cell->value.IsBool())
//		{
//			jValue_SB* v = new jValue_SB();
//			v->setType(cell->name.GetString());
//			v->setValue(cell->value.GetBool());
//			std::string valueKey = cell->name.GetString();
//			ret.insert(std::pair<std::string, void*>(valueKey, v));
//		}
//		else if (cell->value.IsObject())
//		{
//			jValue_SM* v = new jValue_SM();
//			v->setType(cell->name.GetString());
//			std::string valueKey = cell->name.GetString();
//			ret.insert(std::pair<std::string, void*>(valueKey, v));
//			paraseValue(cell->value.MemberBegin(), cell->value.MemberEnd(), v->getValue());
//		}
//	}
//}
//
//void paraseValue(rapidjson::Value::ConstMemberIterator start, rapidjson::Value::ConstMemberIterator end, std::map<std::string, std::string>& ret)
//{
//	for (auto cell = start; cell != end; ++cell)
//	{
//		fprintf(stdout, "iter json name: %s, type: %d\n", cell->name.GetString(), cell->value.GetType());
//		if (cell->value.IsInt())
//		{
//			std::string valueKey = cell->name.GetString();
//			ret.insert(std::pair<std::string, std::string>(valueKey, std::to_string(cell->value.GetInt())));
//		}
//		else if (cell->value.IsString())
//		{
//			std::string valueKey = cell->name.GetString();
//			ret.insert(std::pair<std::string, std::string>(valueKey, cell->value.GetString()));
//		}
//		else if (cell->value.IsFloat())
//		{
//			std::string valueKey = cell->name.GetString();
//			ret.insert(std::pair<std::string, std::string>(valueKey, std::to_string(cell->value.GetFloat())));
//		}
//		else if (cell->value.IsBool())
//		{
//			std::string valueKey = cell->name.GetString();
//			ret.insert(std::pair<std::string, std::string>(valueKey, std::to_string(cell->value.GetBool())));
//		}
//		else if (cell->value.IsArray() || cell->value.IsObject())
//		{
//			continue;
//		}
//	}
//}
//
//void paraseValue(rapidjson::Value::ConstMemberIterator start, rapidjson::Value::ConstMemberIterator end, std::map<std::string, std::map<std::string, std::string>>& ret)
//{
//	for (auto cell = start; cell != end; ++cell)
//	{
//		fprintf(stdout, "iter json name: %s, type: %d\n", cell->name.GetString(), cell->value.GetType());
//		if (cell->value.IsObject())
//		{
//			std::string valueKey = cell->name.GetString();
//			ret.insert(std::pair<std::string, std::map<std::string, std::string>>(valueKey, std::map<std::string, std::string>()));
//			paraseValue(cell->value.MemberBegin(), cell->value.MemberEnd(), ret[valueKey]);
//		}
//		else
//		{
//			continue;
//		}
//	}
//}
//
//int loadJson(std::vector<void*>& value)
//{
//	const char* file_name = "./src.json";
//	std::ifstream in(file_name);
//	if (!in.is_open())
//	{
//		fprintf(stderr, "fail to read json file: %s\n", file_name);
//		return -1;
//	}
//
//	std::string json_content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
//	in.close();
//
//	rapidjson::Document dom;
//	if (!dom.Parse(json_content.c_str()).HasParseError())
//	{
//		paraseValue(dom.MemberBegin(), dom.MemberEnd(), value);
//	}
//	else
//	{
//		std::cout << "json value fmt error" << std::endl;
//	}
//	return 0;
//}
//
//int loadJson(std::map<std::string, void*>& value)
//{
//	const char* file_name = "./src.json";
//	std::ifstream in(file_name);
//	if (!in.is_open())
//	{
//		fprintf(stderr, "fail to read json file: %s\n", file_name);
//		return -1;
//	}
//
//	std::string json_content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
//	in.close();
//
//	rapidjson::Document dom;
//	if (!dom.Parse(json_content.c_str()).HasParseError())
//	{
//		paraseValue(dom.MemberBegin(), dom.MemberEnd(), value);
//	}
//	else
//	{
//		std::cout << "json value fmt error" << std::endl;
//	}
//	return 0;
//}
//
//int loadJson(std::map<std::string, std::map<std::string, std::string>>& value)
//{
//	const char* file_name = "./src.json";
//	std::ifstream in(file_name);
//	if (!in.is_open())
//	{
//		fprintf(stderr, "fail to read json file: %s\n", file_name);
//		return -1;
//	}
//
//	std::string json_content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
//	in.close();
//
//	rapidjson::Document dom;
//	if (!dom.Parse(json_content.c_str()).HasParseError())
//	{
//		paraseValue(dom.MemberBegin(), dom.MemberEnd(), value);
//	}
//	else
//	{
//		std::cout << "json value fmt error" << std::endl;
//	}
//	return 0;
//}
//
//int main()
//{
//	/*modifyMember("name", "lsk");
//	deleteMember("address");
//	addMember("lsk", "777");*/
//	std::vector<void*> value;
//	std::map<std::string, void*> valueMap;
//	std::map<std::string, std::map<std::string, std::string>> lsk;
//
//	loadJson(value);
//	loadJson(valueMap);
//	loadJson(lsk);
//
//	/*auto c = ((jValue_SM*)valueMap["shan_dong"])->getValue();
//	auto cA = ((jValue_SM*)c["value1"])->getValue()["ji_nan"];
//	auto last = ((jValue_SS*)cA)->getValue();*/
//
//	//std::cout << ((jValue_SM*)valueMap["shan_dong"])->getValue() << std::endl;
//	/*for (auto c : ((jValue_SM*)valueMap["shan_dong"])->getValue())
//	{
//		for (auto l : c.second)
//		{
//		}
//	}*/
//	//for (auto c : value)
//	//{
//	//	//std::cout << ((jValue_SS*)c)->getValue() << std::endl;
//	//	delete c;
//	//}
//	std::cout << "hello world" << std::endl;
//}

 //dllmain.cpp : 定义 DLL 应用程序的入口点。
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}