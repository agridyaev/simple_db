#include <iostream>
#include <string>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

class Date {
public:
  int GetYear() const {
	  return year;
  };
  int GetMonth() const {
	  return month;
  };
  int GetDay() const {
	  return day;
  };

  void SetYear(int new_year) {
	  year = new_year;
  }

  void SetMonth(int new_month) {
	  month = new_month;
  }

  void SetDay(int new_day) {
	  day = new_day;
  }
private:
  int year, month, day;
};

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() < rhs.GetDay();
		}
		return lhs.GetMonth() < rhs.GetMonth();
	}
	return lhs.GetYear() < rhs.GetYear();
};

istream& operator>>(istream& stream, Date& date) {
	int new_year, new_month, new_day;
	stream >> new_year;
	date.SetYear(new_year);
	stream.ignore(1);

	stream >> new_month;
	date.SetMonth(new_month);
	stream.ignore(1);

	stream >> new_day;
	date.SetDay(new_day);
	return stream;
};

ostream& operator<<(ostream& stream, const Date& date) {
	stream << setfill('0');
	stream << setw(4) << date.GetYear() << '-'
	       << setw(2) << date.GetMonth() << '-'
		   << setw(2) << date.GetDay();
	return stream;
};

class Database {
public:
  void AddEvent(const Date& date, const string& event) {
		  storage[date].insert(event);
  };
  bool DeleteEvent(const Date& date, const string& event);
  int  DeleteDate(const Date& date);

  void Find(const Date& date) const;

  void Print() const {
	  for (const auto& record : storage) {
		  for (const auto& event : record.second) {
			  cout << record.first << " " << event << endl;
		  }
	  }
  };

private:
  map<Date, set<string>> storage;
};


int main() {
  Database db;

  string command;
  while (getline(cin, command)) {

	  cin >> command;
	  if (!command.length()) {
		  continue;
	  } else {
		  if (command == "Add") {
			  Date date;
			  string event;

			  cin >> date;
			  cin >> event;

			  db.AddEvent(date, event);
		  }

		  if (command == "Print") {
			  db.Print();
		  }
	  }
  }

  return 0;
}
