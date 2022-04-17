#pragma once
#include <string>
#include <iostream>
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
		virtual std::string* parse(std::string str) = 0;
	};

	class DateParser : public Parser {
	public:
		std::string* parse(std::string str) override {

		};
	};

	class TimeParser : public Parser {
	public:
		std::string* parse(std::string str) override {

		};
	};

	class WeatherStatistics {
	private:
		Time _time;
		Date _date;
		WeatherData _data;
		Parser* _parser;
	public:
		double computeCoeff() {

		}
		bool isValidDateTime()
		{

		}
		void loadData()
		{

		}

	};
};