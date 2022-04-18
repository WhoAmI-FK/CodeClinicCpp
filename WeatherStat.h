#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
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
		explicit Date(const Date& d) 
		{
			year = d.year;
			month = d.month;
			day = d.day;
		}
		~Date() = default;
	};
	class Time {
	private:
		int hours;
		int mins;
		int secs;
	public:
		std::string getTimeInFormat() const {
			// rework
			return (
				std::to_string(hours) + ":" +
				std::to_string(mins) + ":" +
				std::to_string(secs)
				);
		};
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
		double computeCoeff() {

		}
		bool isValidDateTime()
		{

		}
		void loadData()
		{
			std::string line;
			reader fileStat("stats/Environmental_Data_Deep_Moor_2012.txt");
			if (fileStat.is_open()) {
				getline(fileStat, line); // reading dummyLine
				while (getline(fileStat, line)) {
					DataSet* temp_storage = new DataSet();
					std::string toOutput;
					file_parser fileParser(line);
					fileParser >> toOutput;
					// complete parser
					_parser = new DateParser();
					try{
					std::string* parsedItem = _parser->parse(toOutput);
					temp_storage->_date.setDate(std::stoi(parsedItem[0]), std::stoi(parsedItem[1]), std::stoi(parsedItem[2]));
					delete _parser;
					_parser = new TimeParser();
					fileParser >> toOutput;
					parsedItem = _parser->parse(toOutput);
					temp_storage->_time.setTime(std::stoi(parsedItem[0]),std::stoi(parsedItem[1]),std::stoi(parsedItem[2]));
					fileParser >> temp_storage->_data.Air_Temp;
					fileParser >> temp_storage->_data.Barometric_Press;
					fileParser >> temp_storage->_data.Dew_Point;
					fileParser >> temp_storage->_data.Relative_Humidity;
					fileParser >> temp_storage->_data.Wind_Dir;
					fileParser >> temp_storage->_data.Wind_Gust;
					fileParser >> temp_storage->_data.Wind_Speed;
					stats.push_back(*temp_storage);
					delete temp_storage;
					}catch(std::exception e){
						std::cout << e.what() << std::endl;
					}
					
				}
				fileStat.close();
			}
			else throw std::runtime_error("Unable to open file");
		}

	};
};