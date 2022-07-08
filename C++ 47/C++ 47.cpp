#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


class Applier {
	friend class Company;
	string _name = "", _speciality = "", _text = "";
	int _age = 0;

public:

	Applier() = default;

	Applier(string name, int age, string speciality, string text)
	{
		_name = name;
		_age = age;
		_speciality = speciality;
		_text = text;
	}

	void show()
	{
		cout << "Name : " << _name << endl;
		cout << "Age : " << _age << endl;
		cout << "Speciality : " << _speciality << endl;
		cout << "Description : " << _text << endl;
	}

	friend ostream& operator<<(ostream& out, Applier a);
};

ostream& operator<<(ostream& out, Applier a)
{
	out << "Name : " << a._name << endl;
	out << "Age : " << a._age << endl;
	out << "Speciality : " << a._speciality << endl;
	out << "Description : " << a._text << endl;

	return out;
}


class Company {
	vector<Applier*> appliers;
	size_t oldSize;

public:

	Company() : oldSize(), appliers() {}

	Company(vector<Applier*> _appliers)
	{
		appliers = _appliers;
	}

	void hireUp(Applier* cv)
	{
		appliers.push_back(cv);
	}

	void showAllCV()
	{
		for (size_t i = 0; i < appliers.size(); i++)
			cout << *appliers[i] << endl;
	}


	void writeToFile(string filename)
	{
		ofstream file;
		file.open(filename, ios::app);
		if (!file.is_open())
			throw exception("File isn't open.....(\n");
		else
			for (size_t i = 0; i < appliers.size(); i++)
				file << appliers[i]->_name << ' ' << appliers[i]->_age << ' ' << appliers[i]->_speciality << ' ' << appliers[i]->_text << endl;
		file.close();
	}

	void writeToFile(string filename, Applier* app)
	{
		ofstream file;
		file.open(filename, ios::app);
		if (!file.is_open())
			throw exception("File isn't open.....(\n");
		else
			file << app->_name << ' ' << app->_age << ' ' << app->_speciality << ' ' << app->_text << endl;
		file.close();
	}


	void readToFile(string filename)
	{
		ifstream file(filename, ios::in);
		if (!file.is_open())
			throw exception("File isn't open.....(\n");

		file.seekg(0);
		Applier app;

		while (!file.eof())
		{
			file >> app._name >> app._age >> app._speciality >> app._text;
			if (file.peek() != '\n')
				break;
			cout << app << endl;
		}

		file.close();
	}
};






int main() {
	Applier* cv1 = new Applier("Ceyhun", 18, "IT", "Empty1");
	Applier* cv2 = new Applier("Sebine", 17, "Designer", "Empty2");
	Applier* cv3 = new Applier("Ulvi", 23, "Programmer", "Empty3");


	vector<Applier*> appliers;
	try
	{
		Company company(appliers);
		// company.hireUp(cv1);
		// company.hireUp(cv2);
		// 
		// company.writeToFile("company.txt");

		//company.showAllCV();


		company.hireUp(cv1);
		company.hireUp(cv2);


		company.writeToFile("f.txt");

		company.readToFile("f.txt");

		company.hireUp(cv3);

		company.writeToFile("f.txt", cv3);
		company.readToFile("f.txt");
	}
	catch (const std::exception& ex)
	{
		cout << ex.what();
	}
	

	


}