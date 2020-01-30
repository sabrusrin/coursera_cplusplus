#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cctype>
using namespace std;

// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
	public:
		Date():year{1}, month{1}, day{1}	{}
		Date(int new_year, int new_month, int new_day)	{
			year = new_year;
			if (new_month < 1 || new_month > 12)
				throw runtime_error("Month value is invalid: " \
										+ to_string(new_month));
			else
				month = new_month;
			if (new_day < 1 || new_day > 31)
				throw runtime_error("Day value is invalid: " \
										+ to_string(new_day));
			else
				day = new_day;
		}
		int GetYear() const	{
			return (year);
		}
		int GetMonth() const	{
			return (month);
		}
		int GetDay() const	{
			return (day);
		}
	private:
		int	year;
		int	month;
		int	day;
};

bool operator<(const Date& lhs, const Date& rhs)	{
	if (lhs.GetYear() != rhs.GetYear())
		return (lhs.GetYear() < rhs.GetYear());
	else if (lhs.GetMonth() != rhs.GetMonth())
		return (lhs.GetMonth() < rhs.GetMonth());
	else
		return (lhs.GetDay() < rhs.GetDay());
}

istream&	operator>>(istream& stream, Date& date)	{
	int	new_year, new_month, new_day;
	int	minus_count = 0;
	string str;

	stream >> str;
	runtime_error	err("Wrong date format: " + str);
	stringstream	ss(str);
	for (const auto& c : str)	{
		if (c == '-')
			++minus_count;
		else
			minus_count = 0;
		if (minus_count > 2)
			throw err;
		if (isdigit(c) || c == '-' || c == '+')
			continue;
		else
			throw err;
	}
	minus_count = count(str.begin(), str.end(), '-');
	if (minus_count < 2 || minus_count > 5)
		throw err;
	ss >> new_year;
	ss.ignore(1);
	ss >> new_month;
	ss.ignore(1);
	int c = ss.peek();
	if (c == EOF)
		throw err;
	ss >> new_day;
	date = {new_year, new_month, new_day};
	return (stream);
}

ostream&	operator<<(ostream& stream, const Date& date)	{
	stream << setw(4);
	stream << setfill('0');
	stream << date.GetYear();
	stream << '-';
	stream << setw(2);
	stream << date.GetMonth();
	stream << '-';
	stream << setw(2);
	stream << date.GetDay();
	return (stream);
}

class Database {
	public:
		void AddEvent(const Date& date, const string& event)	{
			db[date].insert(event);
		}
		bool DeleteEvent(const Date& date, const string& event)	{
			if (db.count(date) == 0 || db.at(date).count(event) == 0)	{
				cout << "Event not found" << endl;
				return (false);
			}
			db[date].erase(event);
			cout << "Deleted successfully" << endl;
			return (true);
		}
		int  DeleteDate(const Date& date)	{
			int num = 0;
			if (db.count(date) == 0)
				return (num);
			num = db[date].size();
			db[date].clear();
			return (num);
		}
		bool Find(const Date& date) const	{
			if (db.count(date) == 0)
				return (false);
			for (const auto& event : db.at(date))	{
				cout << event << endl;
			}
			return (true);
		}
		void Print() const {
			for (const auto& day : db)
				for (const auto& event : day.second)	{
					cout << day.first << " " << event << endl;
				}
		}
	private:
		map<Date, set<string>>	db;
};

void	Add(Database& db, istream& stream)	{
	Date date;
	string event;

	stream >> date >> event;
	db.AddEvent(date, event);
}

void	Del(Database& db, istream& stream)	{
	string event;
	Date date;

	stream >> date >> event;
	if (event.size() == 0)
		cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
	else
		db.DeleteEvent(date, event);

}

void	Find(Database& db, istream& stream)	{
	Date date;

	stream >> date;
	db.Find(date);
}

int main(void) {
	Database db;
	string command;

	while (getline(cin, command))	{
		stringstream	line(command);
		string	key;
		line >> key;
		try	{
			if (key == "Add")
				Add(db, line);
			else if (key == "Del")
				Del(db, line);
			else if (key == "Find")
				Find(db, line);
			else if (key == "Print")
				db.Print();
			else if (key.size() == 0)
				;
			else
				cout << "Unknown command: " << key << endl;
		}
		catch (runtime_error& err)	{
			cout << err.what() << endl;
			return (0);
		}
	}

	return (0);
}
