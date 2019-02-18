#include <iostream>
#include <iterator>
#include <string>
#include <vector>
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
  bool DeleteEvent(const Date& date, const string& event) {
	  size_t erased = storage[date].erase(event);
	  if (erased == 1) {
		  return true;
	  } else {
		  return false;
	  }
  };
  int  DeleteDate(const Date& date) {
	  int events_deleted = storage[date].size();
	  storage.erase(date);
	  return events_deleted;
  };

  set<string> Find(const Date& date) const {
	  set<string> events_founded;
	  if (storage.count(date) > 0) {
		  events_founded = storage.at(date);
	  }
	  return events_founded;
  };

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
	  if (!command.length()) {
		  continue;
	  } else {
		  istringstream iss(command);
		  string operation_code;
		  iss >> operation_code;

		  if (operation_code == "Add") {
			  Date date;
			  string event;

			  iss >> date;
			  iss >> event;

			  db.AddEvent(date, event);
		  } else if (operation_code == "Del") {
			  Date date;
			  string event;

			  iss >> date;
			  iss >> event;
			  if (event.size()) {
				  bool result = db.DeleteEvent(date, event);
				  if (result) {
					  cout << "Deleted successfully" << endl;
				  } else {
					  cout << "Event not found" << endl;
				  }
			  } else {
				  int events_erased = db.DeleteDate(date);
				  cout << "Deleted " << events_erased << " events" << endl;
			  }
		  } else if (operation_code == "Find") {
			  Date date;

			  iss >> date;

			  set<string> events_founded = db.Find(date);
			  for (const auto& event : events_founded) {
				  cout << event << endl;
			  }
		  } else if (operation_code == "Print") {
			  db.Print();
		  } else {
			  cout << "Unknown command: " << operation_code << endl;
		  }
	  }
  }

  return 0;
}
