// Generator_Sandbox.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <json.hpp>
#include <vector>
#include <exception>

using namespace std;
using json = nlohmann::json;

class Config_Data {
public:
	static Config_Data* getInstance();
	bool openConfigFile_(string configFile);
	auto access_(string key);
	auto& operator << (string key) { return data_[key];  };

private:
	Config_Data() {};
	Config_Data(Config_Data const&) {};
	Config_Data& operator= (Config_Data const&) {};
	Config_Data& operator() (string key) {};

	void parseConfig_(json contents);

	static Config_Data* singleton_;
	ifstream i;
	json data_;
	vector<string> titles_;
	vector<string> names_;
	vector<string> surnames_;
};

Config_Data* Config_Data::singleton_ = 0;

auto Config_Data::access_(string key)
{
	return data_[key];
}

void Config_Data::parseConfig_(json contents)
{
	for (auto&[key, value] : contents.items())
	{
		if (value.is_object())
		{
			parseConfig_(value);
		}

		if (key == "Titles")
		{
			if (value.is_array()) {
				for (auto & slot : value)
				{
					titles_.push_back(slot);
				}
			}
			else if (value.is_string()) {
				titles_.push_back(value);
			}
		}
		else if (key == "Names")
		{
			if (value.is_array()) {
				for (auto & slot : value)
				{
					names_.push_back(slot);
				}
			}
			else if (value.is_string()) {
				names_.push_back(value);
			}
		}
		else if (key == "Surnames")
		{
			if (value.is_array()) {
				for (auto & slot : value)
				{
					surnames_.push_back(slot);
				}
			}
			else if (value.is_string()) {
				surnames_.push_back(value);
			}
		}
	}
}

Config_Data* Config_Data::getInstance()
{
	if (!singleton_)
		singleton_ = new Config_Data();

	return singleton_;
}

bool Config_Data::openConfigFile_(string filename) {
	try
	{
		std::ifstream i(filename);
		i >> data_;

		parseConfig_(data_);
	}
	catch (exception& e)
	{
		cout << "Standard exception: " << e.what() << endl;
	}

	return true;
}

class Name
{
public:
	string getName_() { return name_; };
	virtual void getInfo_() {};

	virtual void setName_(string arg) {};

private:
	string name_;
};

class Name_Title : public Name
{
public:
	Name_Title();
	void Create_();

	void getInfo_();

	void setName_(string arg);
};

Name_Title::Name_Title()
{
	Create_();
}

void Name_Title::Create_()
{
	setName_("");
}

void Name_Title::getInfo_()
{
	cout << "This is a Name: Title" << endl;
}

void Name_Title::setName_(string arg)
{
	
 }

class Character
{
public:
	Character();
	list<Name*> name_;
};

Character::Character() {};

int main()
{
	Config_Data* config = Config_Data::getInstance();
	config->openConfigFile_("config.json");
	Character first;
	first.name_.push_back(new Name_Title);

	cout << config->access_("Note") << endl;
	cout << (*config << "Note") << endl;
	//cout << data.data_["Config"] << endl;
	cout << first.name_.back()->getName_() << endl;

	getchar();
    return 0;
}