#include <iostream>
#include <string>
#include <map>
#include <set>
#include <iomanip>
#include <stdexcept>

using namespace std;

class Date {
public:
  Date() {
	  year = 0;
	  month = 0;
	  day = 0;
  };

  Date(int new_year, int new_month, int new_day) {
	  year = new_year;
	  month = new_month;
	  day = new_day;
  };

  int GetYear() const {
	  return year;
  };
  int GetMonth() const {
	  return month;
  };
  int GetDay() const {
	  return day;
  };

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
	  if (storage.count(date)) {
		  if (storage[date].count(event)) {
		  	  storage[date].erase(event);
		  	  return true;
		  }
	  }
	  return false;
  };

  int DeleteDate(const Date& date) {
	  int events_deleted = 0;
	  if (storage.count(date)) {
		  events_deleted = storage[date].size();
		  storage.erase(date);
	  }
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

Date ParseDate(const string& date_str) {
	int year, month, day;
	char sep1, sep2;
	stringstream ss (date_str);

	ss >> year >> sep1 >> month >> sep2 >> day;

	if (sep1 != '-' || sep2 != '-') {
		throw invalid_argument("Wrong date format: " + date_str);
	}

	if (ss.fail()) {
		throw invalid_argument("Wrong date format: " + date_str);
	}

	if (ss.peek() != EOF) {
		throw invalid_argument("Wrong date format: " + date_str);
	}

	if (month < 1 || month > 12) {
    	throw invalid_argument("Month value is invalid: " + to_string(month));
    }

	if (day < 1 || day > 31) {
		throw invalid_argument("Day value is invalid: " + to_string(day));
	}

	return Date({year, month, day});
}


int main() {
  // Test comment
  Database db;

  string command;
  while (getline(cin, command)) {
	  if (!command.length()) {
		  continue;
	  } else {
		  stringstream ss(command);
		  string operation_code;
		  ss >> operation_code;

		  if (operation_code == "Add") {
			  string date_str;
			  ss >> date_str;

			  Date date;
			  try {
				  date = ParseDate(date_str);
			  } catch (exception& e) {
				  cout << e.what();
				  return 0;
			  }

			  string event;
			  ss >> event;

			  db.AddEvent(date, event);
		  } else if (operation_code == "Del") {
			  string date_str;
			  ss >> date_str;

			  Date date;
			  try {
				  date = ParseDate(date_str);
			  } catch (exception& e) {
				  cout << e.what();
				  return 0;
			  }

			  string event;
			  ss >> event;
			  if (event.size()) {
				  if (db.DeleteEvent(date, event)) {
					  cout << "Deleted successfully" << endl;
				  } else {
					  cout << "Event not found" << endl;
				  }
			  } else {
				  int events_erased = db.DeleteDate(date);
				  cout << "Deleted " << events_erased << " events" << endl;
			  }
		  } else if (operation_code == "Find") {
			  string date_str;
			  ss >> date_str;
			  
			  Date date;
			  try {
				  date = ParseDate(date_str);
			  } catch (exception& e) {
				  cout << e.what();
				  return 0;
			  }

			  set<string> events_founded = db.Find(date);
			  for (const auto& event : events_founded) {
				  cout << event << endl;
			  }
		  } else if (operation_code == "Print") {
			  db.Print();
		  } else {
			  cout << "Unknown command: " << operation_code;
			  return 0;
		  }
	  }
  }

  return 0;
}
