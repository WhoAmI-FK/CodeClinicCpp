#pragma once
#define MAX_FILES 5
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include <ctime>
namespace WStat {
	class Date {
	private:
		int year;
		int month;
		int day;
	public:
		std::string getDateInFormat() const {
			return (
				std::to_string(year) + "_" +
				std::to_string(month) + "_" +
				std::to_string(day)
				);
		}
		bool operator==(const Date& rhs) {
			return (year == rhs.year) && (month == rhs.month) && (day == rhs.day);
		}
		explicit Date() = default;
		explicit Date(int yyyy, int mm, int d) 
			: year(yyyy),month(mm),day(d)
		{

		}
		void setDate(int yyyy, int mm, int d) {
			year = yyyy;
			month = mm;
			day = d;
		}
		int getYear() const {
			return year;
		}
		int getMonth() const {
			return month;
		}
		int getDay() const {
			return day;
		}
		explicit Date(const Date& d) 
		{
			year = d.year;
			month = d.month;
			day = d.day;
		}
		int64_t getSecs() {

		}
		~Date() = default;
	};
	class Time {
	private:
		int hours;
		int mins;
		int secs;
	public:
		int getHours() const {
			return hours;
		}
		int getMins() const {
			return mins;
		}
		int getSecs() const {
			return secs;
		}
		std::string getTimeInFormat() const {
			// rework
			return (
				std::to_string(hours) + ":" +
				std::to_string(mins) + ":" +
				std::to_string(secs)
				);
		};
		bool operator==(const Time& rhs) {
			return (hours == rhs.hours) && (mins == rhs.mins) && (secs == rhs.secs);
		}
		explicit Time() = default;
		explicit Time(int hh, int mm, int ss)
			: hours(hh), mins(mm), secs(ss)
		{

		}
		void setTime(int hh, int mm, int ss) {
			hours = hh;
			mins = mm;
			secs = ss;
		}
		explicit Time(const Time & t)
		{
			hours = t.hours;
			mins = t.mins;
			secs = t.secs;
		}
		~Time() = default;
	};

	struct WeatherData {
		double Air_Temp; // F
		double Barometric_Press; // inHg
		double Dew_Point; //
		double Relative_Humidity; // %
		double Wind_Dir; // deg
		double Wind_Gust; // mph
		double Wind_Speed; // mph
	};

	class Parser {
	public:
		virtual std::string* parse(std::string str) = 0;
	};

	class DateParser : public Parser {
	public:
		std::string* parse(std::string str) override {
			std::string* str_arr = new std::string[3];
			*(str_arr) = str.substr(0, 4);
			*(str_arr + 1) = str.substr(5, 2);
			*(str_arr + 2) = str.substr(8, 2);
			return str_arr;
		};
	};

	class TimeParser : public Parser {
	public:
		std::string* parse(std::string str) override {
			std::string* str_arr = new std::string[3];
			*(str_arr) = str.substr(0, 2);
			*(str_arr + 1) = str.substr(3, 2);
			*(str_arr + 2) = str.substr(6, 2);
			return str_arr;
		};
	};

	struct DataSet {
		Time _time;
		Date _date;
		WeatherData _data;
	};
	class WeatherStatistics {
	private:
		std::vector<DataSet> stats;
		Parser* _parser;
	public:
		typedef std::ifstream reader;
		typedef std::stringstream file_parser;
		typedef std::vector<DataSet>::iterator iterator;
		typedef const Date& const_date;
		typedef const Time& const_time;
		typedef DataSet* data;
		double computeCoeff(data ds, data de) {
			std::tm t1;
			std::tm t2;
			t1.tm_year = ds->_date.getYear() - 1900;
			t2.tm_year = de->_date.getYear() - 1900;
			t1.tm_mon = ds->_date.getMonth() - 1;
			t2.tm_mon = de->_date.getMonth() - 1;
			t1.tm_mday = ds->_date.getDay();
			t2.tm_mday = de->_date.getDay();
			t1.tm_hour = ds->_time.getHours();
			t2.tm_hour = de->_time.getHours();
			t1.tm_min = ds->_time.getMins();
			t2.tm_min = de->_time.getMins();
			t1.tm_sec = ds->_time.getSecs();
			t2.tm_sec = de->_time.getSecs();
			double result = std::difftime(mktime(&t2), mktime(&t1));
			return static_cast<double>((
				(de->_data.Barometric_Press - ds->_data.Barometric_Press)
				/
				result
				));
		}
		DataSet* isValidDateTime(const_date _d, const_time _t)
		{
			if (!stats.empty()) {
				for (iterator i = stats.begin(); i != stats.end(); ++i) {
					if (i->_date == _d && i->_time == _t) {
						return &(*i);
					}
				}
			}
			else {
				assert("Error vector is empty");
			}
			return nullptr;
		}
		void showStat() {
			this->loadData();
			Date* START_DATE, *END_DATE;
			Time* START_TIME, *END_TIME;
			std::string* temp_arr;
			std::string str;
			std::cout << "\n\nEnter START DATE as yyyy_mm_dd: ";
			std::cin >> str;
			_parser = new DateParser();
			temp_arr = _parser->parse(str);
			START_DATE = new Date(std::stoi(temp_arr[0]), std::stoi(temp_arr[1]), std::stoi(temp_arr[2]));
			delete[] temp_arr;
			delete _parser;
			// load to date	
			std::cout << "\n\nEnter START TIME as hh:mm:ss (24-hour): ";
			std::cin >> str;
			_parser = new TimeParser();
			temp_arr = _parser->parse(str);
			START_TIME = new Time(std::stoi(temp_arr[0]), std::stoi(temp_arr[1]), std::stoi(temp_arr[2]));
			delete[] temp_arr;
			delete _parser;
			std::cout << "\n\nEnter END DATE as yyyy_mm_dd: ";
			std::cin >> str;
			_parser = new DateParser();
			temp_arr = _parser->parse(str);
			END_DATE = new Date(std::stoi(temp_arr[0]), std::stoi(temp_arr[1]), std::stoi(temp_arr[2]));
			delete[] temp_arr;
			delete _parser;
			std::cout << "\n\nEnter END TIME as hh:mm:ss (24-hour): ";
			std::cin >> str;
			_parser = new TimeParser();
			temp_arr = _parser->parse(str);
			END_TIME = new Time(std::stoi(temp_arr[0]), std::stoi(temp_arr[1]), std::stoi(temp_arr[2]));
			delete[] temp_arr;
			delete _parser;
			data sStat = isValidDateTime(*START_DATE, *START_TIME);
			data eStat = isValidDateTime(*END_DATE, *END_TIME);
			if (sStat != nullptr && eStat != nullptr) {
				// proceed
				std::cout << "Coefficient: " << computeCoeff(sStat, eStat) * 24 * 60 * 60 << " inHg/day" << std::endl;
			}
			else std::cout << "Invalid Date Time";
		}	

		void displayData()
		{
			for (iterator it = stats.begin(); it != stats.end(); ++it) {
				std::cout << "--------------\n";
				std::cout << it->_date.getDateInFormat() << std::endl;
				std::cout << it->_time.getTimeInFormat() << std::endl;
				std::cout << it->_data.Air_Temp << " F\n";
				std::cout << it->_data.Barometric_Press << " inHg\n";
				std::cout << it->_data.Dew_Point << std::endl; 
				std::cout << it->_data.Relative_Humidity << " %\n";
				std::cout << it->_data.Wind_Dir << " deg\n";
				std::cout << it->_data.Wind_Gust << " mph\n";
				std::cout << it->_data.Wind_Speed << " mph\n";
				std::cout << "--------------\n";
			}
		}
		void loadData()
		{
			std::string line;
			std::string file_name = "stats/Environmental_Data_Deep_Moor_2012.txt";
			for (size_t i = 2; i <= MAX_FILES; ++i) {
				file_name.replace(38, 1, std::string(std::to_string(i)).c_str());
				std::cout << "Loading " << file_name << std::endl;
				reader fileStat(file_name);
				if (fileStat.is_open()) {
					getline(fileStat, line); // reading dummyLine
					while (getline(fileStat, line)) {

						DataSet* temp_storage = new DataSet();
						std::string toOutput;
						file_parser fileParser(line);
						fileParser >> toOutput;
						// complete parser
						_parser = new DateParser();
						try {
							std::string* parsedItem = _parser->parse(toOutput);
							temp_storage->_date.setDate(std::stoi(parsedItem[0]), std::stoi(parsedItem[1]), std::stoi(parsedItem[2]));
							delete _parser;
							_parser = new TimeParser();
							fileParser >> toOutput;
							parsedItem = _parser->parse(toOutput);
							temp_storage->_time.setTime(std::stoi(parsedItem[0]), std::stoi(parsedItem[1]), std::stoi(parsedItem[2]));
							fileParser >> temp_storage->_data.Air_Temp;
							fileParser >> temp_storage->_data.Barometric_Press;
							fileParser >> temp_storage->_data.Dew_Point;
							fileParser >> temp_storage->_data.Relative_Humidity;
							fileParser >> temp_storage->_data.Wind_Dir;
							fileParser >> temp_storage->_data.Wind_Gust;
							fileParser >> temp_storage->_data.Wind_Speed;
							stats.push_back(*temp_storage);
							delete temp_storage;
						}
						catch (std::exception e) {
							std::cout << e.what() << std::endl;
						}

					}
					fileStat.close();
				}
				else throw std::runtime_error("Unable to open file");
			}
		}
	};
};