// Generator_Sandbox.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <json.hpp>
#include <vector>

using namespace std;
using json = nlohmann::json;

class Config_Data {
public:
	Config_Data();
	Config_Data(string filename);
	void ParseConfig_(json contents);

	json data_;
	vector<string> titles_;
	vector<string> names_;
	vector<string> surnames_;
private:
	ifstream i;
};

void Config_Data::ParseConfig_(json contents)
{
	for (auto&[key, value] : contents.items())
	{
		if (value.is_object())
		{
			ParseConfig_(value);
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
		if (key == "Surnames")
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

Config_Data::Config_Data(){}

Config_Data::Config_Data(string filename) {
	i = ifstream(filename);
	i >> data_;

	ParseConfig_(data_);
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

	void setName(string arg);
};

Name_Title::Name_Title()
{
	Create_();
}

void Name_Title::Create_()
{
	setName_("Geovanni");
}

void Name_Title::getInfo_()
{
	cout << "This is a Name: Title" << endl;
}

class Character
{
public:
	Character();
	list<Name*> name_;
};

Character::Character() {}

int main()
{
	Config_Data data("config.json");
	Character first;
	first.name_.push_back(new Name_Title);

	cout << data.data_["Note"] << endl;
	cout << data.data_["Config"] << endl;
	cout << first.name_.back()->getName_() << endl;
	cout << first.name_.back()->getOrigin_() << endl;

	getchar();
    return 0;
}

