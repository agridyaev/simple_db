#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <stdexcept>
#include <cctype>
#include <regex>

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

	  if (new_month < 1 || new_month > 12) {
		  string error = "Month value is invalid: " + to_string(new_month);
		  throw invalid_argument(error);
	  } else {
		  month = new_month;
	  }

	  if (new_day < 1 || new_day > 31) {
		  string error = "Day value is invalid: " + to_string(new_day);
		  throw invalid_argument(error);
	  }
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

bool DateFormatIsValid(const string& date_str) {
	bool format_valid = true;
	string error_text = "Wrong date format: ";

	regex pattern("-?\\+?\\d+--?\\+?\\d+--?\\+?\\d+");

	if (!regex_match(date_str, pattern)) {
		format_valid = false;
		cout << error_text << date_str;
	}

	return format_valid;
};

Date ReadDate(const string& date_str) {
	int new_year, new_month, new_day;
	stringstream ss (date_str);

	ss >> new_year;
	ss.ignore(1);
	ss >> new_month;
	ss.ignore(1);
	ss >> new_day;

	return Date({new_year, new_month, new_day});
}


int main() {
  Database db;

  string command;
  while (getline(cin, command)) {
	  if (!command.length()) {
		  continue;
	  } else {
		  stringstream ss(command);
		  string operation_code;
		  ss >> operation_code;

		  // TODO: Think how to avoid code duplicating on reading and validating date
		  if (operation_code == "Add") {
			  string date_str;
			  ss >> date_str;

			  if (!DateFormatIsValid(date_str)) {
				  return 0;
			  }

			  Date date;
			  try {
				  date = ReadDate(date_str);
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
			  if (!DateFormatIsValid(date_str)) {
				  return 0;
			  }

			  Date date;
			  try {
				  date = ReadDate(date_str);
			  } catch (exception& e) {
				  cout << e.what();
				  return 0;
			  }

			  string event;
			  ss >> event;
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
			  string date_str;
			  ss >> date_str;
			  
			  if (!DateFormatIsValid(date_str)) {
				  return 0;
			  }

			  Date date;
			  try {
				  date = ReadDate(date_str);
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
