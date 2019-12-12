#ifndef SUPER_VALUE_H
#define SUPER_VALUE_H

#include <map>
#include <vector>

template<class kType, class vType>
class KV
{
public:
	KV()
	{}
	~KV()
	{}
	void setValue(vType value)
	{
		value_ = value;
	}

	vType& getValue()
	{
		return value_;
	}

	void setType(kType type)
	{
		type_ = type;
	}

private:
	kType type_;
	vType value_;
};

class jValue_SS :public KV<std::string, std::string>
{
public:
	jValue_SS()
	{}
	~jValue_SS()
	{}
};

class jValue_SI :public KV<std::string, int>
{
public:
	jValue_SI()
	{}
	~jValue_SI()
	{}
};

class jValue_SF :public KV<std::string, float>
{
public:
	jValue_SF()
	{}
	~jValue_SF()
	{}
};

class jValue_SB :public KV<std::string, bool>
{
public:
	jValue_SB()
	{}
	~jValue_SB()
	{}
};

class jValue_SV :public KV<std::string, std::vector<float>>
{
public:
	jValue_SV()
	{}
	~jValue_SV()
	{}
};

class jValue_SVV :public KV<std::string, std::vector<std::vector<float>>>
{
public:
	jValue_SVV()
	{}
	~jValue_SVV()
	{}
};

class jValue_SM :public KV<std::string, std::map<std::string, void*>>
{
public:
	jValue_SM()
	{}
	~jValue_SM()
	{}
};

#endif // SUPER_VALUE_H
