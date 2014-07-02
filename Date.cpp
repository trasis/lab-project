#include "Date.h"
#include <string>
#include <sstream>

using namespace std;

Date::Date() {}
Date::Date(int y, int m, int d, int h, int mi) {
     year_ = y;
     month_ = m;
     day_ = d;
     hour_ = h;
    minute_ = mi;
}

int Date::getYear(void) const {
  return year_;
}

void Date::setYear(int year) {
  year = year_;
}

int Date::getDay(void) const{
  return day_;
}

void Date::setDay(int day) {
  day_ = day;
}
int Date::getMonth(void) const {
  return month_;
}

void Date::setMonth(int month) {
  month_ = month;
}

int Date::getMinute(void) const {
  return minute_;
}

void Date::setMinute(int minute) {
  minute_ = minute;
}

int Date::getHour(void) const {
  return hour_;
}

void Date::setHour(int hour) {
  hour_ = hour;
}

bool Date::isValid(Date date) {
  int monthDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int monthDayFoLeap[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (date.year_ < 1000 || date.year_ > 9999) 
     return false;
  if ((date.month_ < 1) || (date.month_ > 12)) 
    return false;
  if (((date.year_ % 4 == 0) && (date.year_ % 100 != 0)) || (date.year_ % 400 == 0)) {
    if ((date.day_ < 0) || (date.day_ > monthDayFoLeap[date.month_ - 1]))
        return false;
  }
  if (date.year_ % 4 != 0) {
    if ((date.day_ < 0) || (date.day_ > monthDay[date.month_ - 1])) 
        return false;
  }
  if ((date.hour_ < 0) || (date.hour_ > 24)) 
         return false;
  if ((date.minute_ < 0) || (date.minute_ > 60)) 
         return false;
  return true;
}

Date Date::stringToDate(std::string dateString) {
  string sYear, sHour, sMinute, sMonth, sDay;
  int year, month, day, hour, minute;
  sYear = dateString.substr(0, 4);
  sMonth = dateString.substr(5, 2);
  sDay = dateString.substr(8, 2);
  sHour = dateString.substr(11, 2);
  sMinute = dateString.substr(14, 2);
  stringstream r;
  r << sYear;
  r >> year;
  r.clear();
  r << sMonth;
  r >> month;
  r.clear();
  r << sDay;
  r >> day;
  r.clear();
  r << sHour;
  r >> hour;
  r.clear();
  r << sMinute;
  r >> minute;
  return Date(year, month, day, hour, minute);
}

Date & Date::operator=(const Date& date) {
  year_ = date.year_;
  month_ = date.month_;
  day_ = date.day_;
  hour_ = date.hour_;
  minute_ = date.minute_;
}

bool Date::operator==(const Date& date) const {
  if (year_ != date.year_)
     return false;
  if (month_ != date.month_)
      return false;
  if (day_ != date.day_)
      return false;
  if (hour_ != date.hour_)
       return false;
  if (minute_ != date.minute_)
       return false;
  return true;
}

string Date::dateToString(Date date) {
  stringstream r;
  r << date.year_ << '-';
  if (date.month_ < 10) 
     r << '0';
  r << date.month_ << '-';
  if (date.day_ < 10) 
     r << '0';
  r << date.day_ << '/';
  if (date.hour_ < 10) 
     r << '0';
  r << date.hour_ << ':';
  if (date.minute_ < 10)
     r << '0';
  r << date.minute_;
  string st;
  r >> st;
  return st;
}

bool Date::operator>(const Date& date) const {
  if (year_ > date.year_)
     return true;
  if (month_ > date.month_)
     return true;
  if (day_ > date.day_)
     return true;
  if (hour_ > date.hour_)
      return true;
  if (minute_ > date.minute_)
       return true;
  return false;
}

bool Date::operator<(const Date& date) const {
  if (year_ < date.year_)
     return true;
  if (month_ < date.month_) 
     return true;
  if (day_ < date.day_) 
      return true;
  if (hour_ < date.hour_) 
      return true;
  if (minute_ < date.minute_) 
      return true;
  return false;
}
  
bool Date::operator>=(const Date& date) const {
  if ((*this > date) || (*this == date))
      return true;
  else 
    return false;
}
 
bool Date::operator<=(const Date& date) const {
  if ((*this < date) || (*this == date))
      return true;
  else 
    return false;
}
