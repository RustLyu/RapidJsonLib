#include "JsonOperater.h"
#include <fstream>
#include <string>
#include <vector>
#include <stdarg.h>

JsonOperater::JsonOperater()
{
	bzero(path_, MAX_STR_LEN);
}

JsonOperater::~JsonOperater()
{
	valueMap_.clear();
}

bool JsonOperater::loadJson(rapidjson::Document& dom)
{
	std::ifstream in(path_);
	if (!in.is_open())
	{
		fprintf(stderr, "fail to read json file: %s\n", path_);
		return false;
	}

	std::string json_content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	in.close();

	if (dom.Parse(json_content.c_str()).HasParseError())
	{
		fprintf(stderr, "Json Fmt Error\n");
		return false;
	}
	return true;
}

bool JsonOperater::closeJson(const rapidjson::Document& dom)
{
	rapidjson::StringBuffer buf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
	dom.Accept(writer);

	const char* json_content = buf.GetString();
	fprintf(stdout, "json content: %s\n", json_content);

	std::ofstream outfile;
	outfile.open(path_);
	if (!outfile.is_open())
	{
		fprintf(stderr, "fail to open file to write: %s\n", path_);
		return false;
	}

	outfile << json_content << std::endl;
	outfile.close();
	return true;
}

bool JsonOperater::checkFatherExist(const char * f)
{
	if (valueMap_.find(f) != valueMap_.end())
	{
		return true;
	}
	return false;
}

bool JsonOperater::checkChildExist(const char* f, const char* c)
{
	if (checkFatherExist(f) && valueMap_[f].find(c) != valueMap_[f].end())
	{
		return true;
	}
	return false;
}

int JsonOperater::paraseValue(rapidjson::Value::ConstMemberIterator start, rapidjson::Value::ConstMemberIterator end, std::map<std::string, std::string>& ret)
{
	for (auto cell = start; cell != end; ++cell)
	{
		fprintf(stdout, "iter json name: %s, type: %d\n", cell->name.GetString(), cell->value.GetType());
		if (cell->value.IsInt())
		{
			std::string valueKey = cell->name.GetString();
			ret.insert(std::pair<std::string, std::string>(valueKey, std::to_string(cell->value.GetInt())));
		}
		else if (cell->value.IsString())
		{
			std::string valueKey = cell->name.GetString();
			ret.insert(std::pair<std::string, std::string>(valueKey, cell->value.GetString()));
		}
		else if (cell->value.IsFloat())
		{
			std::string valueKey = cell->name.GetString();
			ret.insert(std::pair<std::string, std::string>(valueKey, std::to_string(cell->value.GetFloat())));
		}
		else if (cell->value.IsBool())
		{
			std::string valueKey = cell->name.GetString();
			ret.insert(std::pair<std::string, std::string>(valueKey, std::to_string(cell->value.GetBool())));
		}
		else if (cell->value.IsArray() || cell->value.IsObject())
		{
			continue;
		}
	}
	return 1;
}

int JsonOperater::paraseValue(rapidjson::Value::ConstMemberIterator start, rapidjson::Value::ConstMemberIterator end, std::map<std::string, std::map<std::string, std::string>>& ret)
{
	for (auto cell = start; cell != end; ++cell)
	{
		fprintf(stdout, "iter json name: %s, type: %d\n", cell->name.GetString(), cell->value.GetType());
		if (cell->value.IsObject())
		{
			std::string valueKey = cell->name.GetString();
			ret.insert(std::pair<std::string, std::map<std::string, std::string>>(valueKey, std::map<std::string, std::string>()));
			paraseValue(cell->value.MemberBegin(), cell->value.MemberEnd(), ret[valueKey]);
		}
		else
		{
			continue;
		}
	}
	return 1;
}

int JsonOperater::loadJson()
{
	std::ifstream in(path_);
	if (!in.is_open())
	{
		fprintf(stderr, "fail to read json file: %s\n", path_);
		return -1;
	}

	std::string json_content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	in.close();

	rapidjson::Document dom;
	if (!dom.Parse(json_content.c_str()).HasParseError())
	{
		valueMap_.clear();
		paraseValue(dom.MemberBegin(), dom.MemberEnd(), valueMap_);
	}
	else
	{
		std::cout << "json value fmt error" << std::endl;
	}
	return 0;
}

int JsonOperater::GetValue(char* dst, const int n, va_list ap)
{
	int ret = -1;

	rapidjson::Document dom;
	if (loadJson(dom))
	{
		char* key = va_arg(ap, char*);
		if (!dom.HasMember(key))
			return ret;
		rapidjson::Value& s = dom[key];
		for (int i = 0; i < n - 1; ++i)
		{
			key = va_arg(ap, char*);
			if (!s.HasMember(key))
				return ret;
			s = s[key];
			if (i == (n - 2))
			{
				ret = 0;
				break;
			}
		}
		std::string str = s.GetString();
		memcpy(dst, str.c_str(), sizeof(str));
		//std::cout << dst << std::endl;
	}
	return ret;
}

int JsonOperater::GetValue(int & dst, const int n, va_list ap)
{
	int ret = -1;

	rapidjson::Document dom;
	if (loadJson(dom))
	{
		char* key = va_arg(ap, char*);
		if (!dom.HasMember(key))
			return ret;
		rapidjson::Value& s = dom[key];
		for (int i = 0; i < n - 1; ++i)
		{
			key = va_arg(ap, char*);
			if (!s.HasMember(key))
				return ret;
			s = s[key];
			if (i == (n - 2))
			{
				ret = 0;
				break;
			}
		}
		dst = s.GetInt();
	}
	return ret;
}

int JsonOperater::GetValue(bool & dst, const int n, va_list ap)
{
	int ret = -1;
	rapidjson::Document dom;
	if (loadJson(dom))
	{
		char* key = va_arg(ap, char*);
		if (!dom.HasMember(key))
			return ret;
		rapidjson::Value& s = dom[key];
		for (int i = 0; i < n - 1; ++i)
		{
			key = va_arg(ap, char*);
			if (!s.HasMember(key))
				return ret;
			s = s[key];
			if (i == (n - 2))
			{
				ret = 0;
				break;
			}
		}
		dst = s.GetBool();
	}
	return ret;
}

int JsonOperater::GetValue(float & dst, const int n, va_list ap)
{
	int ret = -1;

	rapidjson::Document dom;
	if (loadJson(dom))
	{
		char* key = va_arg(ap, char*);
		if (!dom.HasMember(key))
		{
			return ret;
		}
		rapidjson::Value& s = dom[key];
		for (int i = 0; i < n - 1; ++i)
		{
			key = va_arg(ap, char*);
			if (!s.HasMember(key))
				return ret;
			s = s[key];
			if (i == (n - 2))
			{
				ret = 0;
				break;
			}
		}
		dst = s.GetFloat();
	}
	return ret;
}

int JsonOperater::AddNode(const char * dst, const int n, va_list ap)
{
	int ret = -1;

	rapidjson::Document dom;
	if (loadJson(dom))
	{
		char* key = va_arg(ap, char*);
		rapidjson::Value kC;
		rapidjson::Value vC;
		// 根节点插入
		if (n == 1)
		{
			vC.SetString(dst, strlen(dst), dom.GetAllocator());

			kC.SetString(key, strlen(key));
			dom.AddMember(kC, vC, dom.GetAllocator());
			ret = 0;
		}
		// 二级
		else if (n == 2)
		{
			std::vector<rapidjson::Value*> tmp;
			if (!dom.HasMember(key))
				return ret;
			rapidjson::Value& s = dom[key];

			char* key = va_arg(ap, char*);

			vC.SetString(dst, strlen(dst), dom.GetAllocator());

			kC.SetString(key, strlen(key));
			s.AddMember(kC, vC, dom.GetAllocator());
			ret = 0;
		}
		else
		{
			std::vector<rapidjson::Value*> tmp;
			if (!dom.HasMember(key))
				return ret;
			rapidjson::Value& s = dom[key];
			tmp.push_back(&s);

			for (int i = 0; i < n - 2; ++i)
			{
				key = va_arg(ap, char*);
				if (!(*tmp[i]).HasMember(key))
					return ret;
				rapidjson::Value& l = (*tmp[i])[key];
				tmp.push_back(&l);
				if (i == (n - 3))
				{
					vC.SetString(dst, strlen(dst), dom.GetAllocator());

					key = va_arg(ap, char*);
					kC.SetString(key, strlen(key));
					l.AddMember(kC, vC, dom.GetAllocator());
					ret = 0;
					break;
				}
			}
		}
		closeJson(dom);
	}
	return ret;
}

int JsonOperater::AddNode(const int dst, const int n, va_list ap)
{
	int ret = -1;

	rapidjson::Document dom;
	if (loadJson(dom))
	{
		char* key = va_arg(ap, char*);
		rapidjson::Value kC;
		rapidjson::Value vC;
		// 根节点插入
		if (n == 1)
		{
			vC.SetInt(dst);
			kC.SetString(key, strlen(key));
			dom.AddMember(kC, vC, dom.GetAllocator());
			ret = 0;
		}
		// 二级
		else if (n == 2)
		{
			std::vector<rapidjson::Value*> tmp;
			if (!dom.HasMember(key))
				return ret;
			rapidjson::Value& s = dom[key];
			
			vC.SetInt(dst);
			char* key = va_arg(ap, char*);
			kC.SetString(key, strlen(key));
			s.AddMember(kC, vC, dom.GetAllocator());
			ret = 0;
		}
		else
		{
			char* key = va_arg(ap, char*);
			if (!dom.HasMember(key))
				return ret;
			rapidjson::Value& s = dom[key];
			std::vector<rapidjson::Value*> tmp;
			tmp.push_back(&s);
			for (int i = 0; i < n - 2; ++i)
			{
				key = va_arg(ap, char*);
				if (!(*tmp[i]).HasMember(key))
					return ret;
				rapidjson::Value& l = (*tmp[i])[key];
				tmp.push_back(&l);
				if (i == (n - 3))
				{
					vC.SetInt(dst);

					key = va_arg(ap, char*);
					kC.SetString(key, strlen(key));
					l.AddMember(kC, vC, dom.GetAllocator());
					closeJson(dom);
					ret = 0;
					break;
				}
			}
		}
	}
	return ret;
}

int JsonOperater::AddNode(const bool dst, const int n, va_list ap)
{
	int ret = -1;

	rapidjson::Document dom;
	if (loadJson(dom))
	{
		char* key = va_arg(ap, char*);
		rapidjson::Value kC;
		rapidjson::Value vC;
		// 根节点插入
		if (n == 1)
		{
			vC.SetBool(dst);
			kC.SetString(key, strlen(key));
			dom.AddMember(kC, vC, dom.GetAllocator());
			ret = 0;
		}
		// 二级
		else if (n == 2)
		{
			std::vector<rapidjson::Value*> tmp;
			if (!dom.HasMember(key))
				return ret;
			rapidjson::Value& s = dom[key];

			vC.SetBool(dst);
			char* key = va_arg(ap, char*);
			kC.SetString(key, strlen(key));
			s.AddMember(kC, vC, dom.GetAllocator());
			ret = 0;
		}
		else
		{
			char* key = va_arg(ap, char*);
			if (!dom.HasMember(key))
				return ret;
			rapidjson::Value& s = dom[key];
			std::vector<rapidjson::Value*> tmp;
			tmp.push_back(&s);
			for (int i = 0; i < n - 2; ++i)
			{
				key = va_arg(ap, char*);
				if (!(*tmp[i]).HasMember(key))
					return ret;
				rapidjson::Value& l = (*tmp[i])[key];
				tmp.push_back(&l);
				if (i == (n - 3))
				{
					vC.SetBool(dst);

					key = va_arg(ap, char*);
					kC.SetString(key, strlen(key));
					l.AddMember(kC, vC, dom.GetAllocator());
					closeJson(dom);
					ret = 0;
					break;
				}
			}
		}
	}
	return ret;
}

int JsonOperater::AddNode(const float dst, const int n, va_list ap)
{
	int ret = -1;

	rapidjson::Document dom;
	if (loadJson(dom))
	{
		char* key = va_arg(ap, char*);
		rapidjson::Value kC;
		rapidjson::Value vC;
		// 根节点插入
		if (n == 1)
		{
			vC.SetFloat(dst);
			kC.SetString(key, strlen(key));
			dom.AddMember(kC, vC, dom.GetAllocator());
			ret = 0;
		}
		// 二级
		else if (n == 2)
		{
			std::vector<rapidjson::Value*> tmp;
			if (!dom.HasMember(key))
				return ret;
			rapidjson::Value& s = dom[key];

			vC.SetFloat(dst);
			char* key = va_arg(ap, char*);
			kC.SetString(key, strlen(key));
			s.AddMember(kC, vC, dom.GetAllocator());
			ret = 0;
		}
		else
		{
			char* key = va_arg(ap, char*);
			if (!dom.HasMember(key))
				return ret;
			rapidjson::Value& s = dom[key];
			std::vector<rapidjson::Value*> tmp;
			tmp.push_back(&s);
			for (int i = 0; i < n - 2; ++i)
			{
				key = va_arg(ap, char*);
				if (!(*tmp[i]).HasMember(key))
					return ret;
				rapidjson::Value& l = (*tmp[i])[key];
				tmp.push_back(&l);
				if (i == (n - 3))
				{
					rapidjson::Value vC;
					vC.SetFloat(dst);

					key = va_arg(ap, char*);
					rapidjson::Value kC;
					kC.SetString(key, strlen(key));
					l.AddMember(kC, vC, dom.GetAllocator());
					closeJson(dom);
					ret = 0;

					break;
				}
			}
		}
	}
	return ret;
}

int JsonOperater::ModifyNode(const char * dst, const int n, va_list ap)
{
	int ret = -1;
	rapidjson::Document dom;
	if (loadJson(dom))
	{
		char* key = va_arg(ap, char*);
		std::vector<rapidjson::Value*> tmp;
		if (!dom.HasMember(key))
			return ret;
		rapidjson::Value& s = dom[key];
		tmp.push_back(&s);
		if (n == 1)
		{
			s.SetString(dst, strlen(dst), dom.GetAllocator());
		}
		else
		{
			for (int i = 0; i < n - 1; ++i)
			{
				key = va_arg(ap, char*);
				if (!(*tmp[i]).HasMember(key))
					return ret;
				rapidjson::Value& l = (*tmp[i])[key];
				tmp.push_back(&l);
				if (i == (n - 2))
				{
					l.SetString(dst, strlen(dst), dom.GetAllocator());
				}
			}
		}
		closeJson(dom);
		ret = 0;

	}
	return ret;
}

int JsonOperater::ModifyNode(const int dst, const int n, va_list ap)
{
	int ret = -1;
	rapidjson::Document dom;
	if (loadJson())
	{
		std::vector<rapidjson::Value*> tmp;
		char* key = va_arg(ap, char*);
		if (!dom.HasMember(key))
			return ret;
		rapidjson::Value& s = dom[key];
		tmp.push_back(&s);
		if (n == 1)
		{
			s.SetInt(dst);
		}
		else
		{
			for (int i = 0; i < n - 1; ++i)
			{
				key = va_arg(ap, char*);
				if (!(*tmp[i]).HasMember(key))
					return ret;
				rapidjson::Value& l = (*tmp[i])[key];
				tmp.push_back(&l);
				if (i == (n - 2))
				{
					l.SetInt(dst);

				}
			}
		}
		closeJson(dom);
		ret = 0;
	}
	return 0;
}

int JsonOperater::ModifyNode(const bool dst, const int n, va_list ap)
{
	int ret = -1;
	rapidjson::Document dom;
	if (loadJson(dom))
	{
		std::vector<rapidjson::Value*> tmp;
		char* key = va_arg(ap, char*);
		if (!dom.HasMember(key))
			return ret;
		rapidjson::Value& s = dom[key];
		tmp.push_back(&s);
		if (n == 1)
		{
			s.SetBool(dst);
		}
		else
		{
			for (int i = 0; i < n - 1; ++i)
			{
				key = va_arg(ap, char*);
				if (!(*tmp[i]).HasMember(key))
					return ret;
				rapidjson::Value& l = (*tmp[i])[key];
				tmp.push_back(&l);
				if (i == (n - 2))
				{
					l.SetBool(dst);
				}
			}
		}
		closeJson(dom);
		ret = 0;
	}
	return ret;
}

int JsonOperater::ModifyNode(const float dst, const int n, va_list ap)
{
	int ret = -1;
	rapidjson::Document dom;
	if (loadJson(dom))
	{
		std::vector<rapidjson::Value*> tmp;
		char* key = va_arg(ap, char*);
		if (!dom.HasMember(key))
		{
			return ret;
		}
		rapidjson::Value& s = dom[key];
		tmp.push_back(&s);
		if (n == 1)
		{
			s.SetFloat(dst);
		}
		else
		{
			for (int i = 0; i < n - 1; ++i)
			{
				key = va_arg(ap, char*);
				if (!(*tmp[i]).HasMember(key))
					return ret;
				rapidjson::Value& l = (*tmp[i])[key];
				tmp.push_back(&l);
				if (i == (n - 2))
				{
					l.SetFloat(dst);
				}
			}
		}

		closeJson(dom);
		ret = 0;
	}
	return ret;
}

int JsonOperater::RemoveNode(const int n, va_list ap)
{
	int ret = -1;

	rapidjson::Document dom;
	if (loadJson(dom))
	{
		std::vector<rapidjson::Value*> tmp;
		char* key = va_arg(ap, char*);
		if (!dom.HasMember(key))
		{
			return ret;
		}
		rapidjson::Value& s = dom[key];
		tmp.push_back(&s);
		if (n == 1)
		{
			dom.RemoveMember(key);
			closeJson(dom);
			ret = 0;
		}

		for (int i = 0; i < n - 2; ++i)
		{
			key = va_arg(ap, char*);
			if (!(*tmp[i]).HasMember(key))
			{
				return ret;
			}
			rapidjson::Value& l = (*tmp[i])[key];
			tmp.push_back(&l);
			if (i == (n - 3))
			{
				key = va_arg(ap, char*);
				l.RemoveMember(key);
				closeJson(dom);
				ret = 0;
			}

		}
	}
	return ret;
}
