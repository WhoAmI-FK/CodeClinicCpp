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
		virtual void parse(std::string str) = 0;
	};

	class DateParser : public Parser {
	public:
		void parse(std::string str) override {

		};
	};

	class TimeParser : public Parser {
	public:
		void parse(std::string str) override {

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
				while (getline(fileStat, line)) {
					DataSet temp_storage;
					std::string toOutput;
					file_parser fileParser(line);
					fileParser >> toOutput;
					
					
					
					
					/*
					std::cout << toOutput << std::endl;
					fileParser >> toOutput;
					std::cout << toOutput << std::endl;
					fileParser >> toOutput;
					std::cout << toOutput << std::endl;
					fileParser >> toOutput;
					std::cout << toOutput << std::endl;
					fileParser >> toOutput;
					std::cout << toOutput << std::endl;
					fileParser >> toOutput;
					std::cout << toOutput << std::endl;
					fileParser >> toOutput;
					std::cout << toOutput << std::endl;
					fileParser >> toOutput;
					std::cout << toOutput << std::endl;
					fileParser >> toOutput;
					std::cout << toOutput << std::endl;
					*/
				}
				fileStat.close();
			}
			else throw std::runtime_error("Unable to open file");
		}

	};
};