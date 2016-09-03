#include "Date.hpp"
#include <iostream>
#include <sstream>
using namespace std;
/*int m_year;
  int m_month;
  int m_day;
  int m_hour;
  int m_minute; */
  
  Date::Date() {
    m_year = 0;
    m_month = 0;
    m_day = 0;
    m_hour = 0;
    m_minute = 0;
  }

  
  Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) {
  	m_year = t_year;
  	m_month = t_month;
  	m_day = t_day;
  	m_hour = t_hour;
  	m_minute = t_minute;
  }

 
  Date::Date(std::string dateString) {
    if (dateString.length() != 16) {
      m_year = 0;
      m_month = 0;
      m_day = 0;
      m_hour = 0;
      m_minute = 0;
      return;
    }
    if (dateString[4] != '-'||dateString[7] != '-'||dateString[10] != '/'||dateString[13] != ':') {
      m_year = 0;
      m_month = 0;
      m_day = 0;
      m_hour = 0;
      m_minute = 0;
      return;
    }
    for (int i = 0; i < 16; i++) {
      if (i != 4&&i != 7&&i != 10&&i != 13) {
        if (dateString[i] < '0'||dateString[i] > '9') {
          m_year = 0;
          m_month = 0;
          m_day = 0;
          m_hour = 0;
          m_minute = 0;
          return;
        }
      }
    }
  	Date temp = Date::stringToDate(dateString);
    m_year = temp.m_year;
    m_month = temp.m_month;
    m_day = temp.m_day;
    m_hour = temp.m_hour;
    m_minute = temp.m_minute;
  }
  
  int Date::getYear(void) const {
  	return m_year;
  }

 
  void Date::setYear(const int t_year) {
  	m_year = t_year;
  }

  
  int Date::getMonth(void) const {
  	return m_month;
  }

  
  void Date::setMonth(const int t_month) {
  	m_month = t_month;
  }

  
  int Date::getDay(void) const {
  	return m_day;
  }

  
  void Date::setDay(const int t_day) {
  	m_day = t_day;
  }

  
  int Date::getHour(void) const {
  	return m_hour;
  }

  
  void Date::setHour(const int t_hour) {
  	m_hour = t_hour;
  }

  
  int Date::getMinute(void) const {
  	return m_minute;
  }

  
  void Date::setMinute(const int t_minute) {
  	m_minute = t_minute;
  }

  
  bool Date::isValid(const Date t_date) {
  	if (t_date.getYear() < 1000 || t_date.getYear() > 9999) {
  		return 0;
  	}
  	if (t_date.getMonth() < 1 || t_date.getMonth() > 12) {
  		return 0;
  	}
  	if (t_date.getMonth() == 1 ||t_date.getMonth() == 3||t_date.getMonth() == 5||t_date.getMonth() == 7||t_date.getMonth() == 8||t_date.getMonth() == 10||t_date.getMonth() == 12) {
  		if (t_date.getDay() > 31||t_date.getDay() < 1) {
  			return 0;
  		}
  	}
  	if (t_date.getMonth() == 4||t_date.getMonth() == 6||t_date.getMonth() == 9||t_date.getMonth() == 11) {
  		if (t_date.getDay() > 30||t_date.getDay() < 1) {
  			return 0;
  		}
  	}
  	if (t_date.getMonth() == 2) {
  		if ((t_date.getYear() % 4 == 0&&t_date.getYear() % 100 != 0) || t_date.getYear() % 400 == 0) {
  			if (t_date.getDay() > 29||t_date.getDay() < 1) {
  				return 0;
  			}
  	} else {
  		if (t_date.getDay() > 28||t_date.getDay() < 1) {
  			return 0;
  		}
  	}
  }
    if (t_date.getHour() < 0||t_date.getHour() > 23) {
    	return 0;
    }
    if (t_date.getMinute() < 0||t_date.getMinute() > 59) {
    	return 0;
    }
    return 1;
}

  /**
  * @brief convert a string to date, if the format is not correct return
  * 0000-00-00/00:00
  * @return a date
  */
  Date Date::stringToDate(const std::string t_dateString) {
  	if (t_dateString.length() != 16) {
  		Date tmp;
      return tmp;
  	}
    if (t_dateString[4] != '-'||t_dateString[7] != '-'||t_dateString[10] != '/'||t_dateString[13] != ':') {
      Date tmp;
      return tmp;
    }
    for (int i = 0; i < 16; i++) {
      if (i != 4&&i != 7&&i != 10&&i != 13) {
        if (t_dateString[i] < '0'||t_dateString[i] > '9') {
          Date tmp;
          return tmp;
        }
      }
    }
  	int a[5];
  	int j = 0;
  	string str = "";
  	for (int i = 0; i < 16; i++) {
  		if (t_dateString[i] == '-'||t_dateString[i] == '/'||t_dateString[i] == ':') {
  			stringstream ss;
  			ss << str;
  			ss >> a[j];
  			j++;
  			str = "";
  		} else {
  			str += t_dateString[i];
  		}
  	}
    stringstream ss;
    ss << str;
    ss >> a[j];
  	Date temp(a[0], a[1], a[2], a[3], a[4]);
  	return temp;
  }

  /**
  * @brief convert a date to string, if the format is not correct return
  * 0000-00-00/00:00
  */
  std::string Date::dateToString(Date t_date) {
    if (!Date::isValid(t_date)) {
      return "0000-00-00/00:00";
    }
  	stringstream ss;
  	string str[5];
  	string date = "";
  	ss << t_date.getYear();
  	ss >> str[0];
  	stringstream a;
  	a << t_date.getMonth();
  	a >> str[1];
  	stringstream b;
  	b << t_date.getDay();
  	b >> str[2];
  	stringstream c;
  	c << t_date.getHour();
  	c >> str[3];
  	stringstream d;
  	d << t_date.getMinute();
  	d >> str[4];
  	date = str[0]+"-";
    if (str[1].length() < 2) {
      date += "0";
    }
    date += str[1] + "-";
    if (str[2].length() < 2) {
      date += "0";
    }
    date += str[2] + "/";
    if (str[3].length() < 2) {
      date += "0";
    }
    date += str[3] + ":";
    if (str[4].length() < 2) {
      date += "0";
    }
    date += str[4];
  	return date;
  }

  /**
  *  @brief overload the assign operator
  */
  Date & Date::operator=(const Date &t_date) {
  	m_year = t_date.m_year;
  	m_month = t_date.m_month;
  	m_day = t_date.m_day;
  	m_hour = t_date.m_hour;
  	m_minute = t_date.m_minute;
  	return *this;
  }

  /**
  * @brief check whether the CurrentDate is equal to the t_date
  */
  bool Date::operator==(const Date &t_date) const {
  	if (m_year != t_date.m_year) {
  		return 0;
  	}
  	if (m_month != t_date.m_month) {
  		return 0;
  	}
  	if (m_day != t_date.m_day) {
  		return 0;
  	}
  	if (m_hour != t_date.m_hour) {
  		return 0;
  	}
  	if (m_minute != t_date.m_minute) {
  		return 0;
  	}
  	return 1;
  }

  /**
  * @brief check whether the CurrentDate is  greater than the t_date
  */
  bool Date::operator>(const Date &t_date) const {
  	if (m_year > t_date.m_year) {
      return 1;
    } else if (m_year == t_date.m_year) {
      if (m_month > t_date.m_month) {
        return 1;
      } else if (m_month == t_date.m_month) {
        if (m_day > t_date.m_day) {
          return 1;
        } else if (m_day == t_date.m_day) {
          if (m_hour > t_date.m_hour) {
            return 1;
          } else if (m_hour == t_date.m_hour) {
            if (m_minute > t_date.m_minute) {
              return 1;
            } else {
              return 0;
            }
          } else {
            return 0;
          }
        } else {
          return 0;
        }
      } else {
        return 0;
      }
    } else {
      return 0;
    }
  }

  /**
  * @brief check whether the CurrentDate is  less than the t_date
  */
  bool Date::operator<(const Date &t_date) const {
  	if (*this > t_date||*this == t_date) {
      return 0;
    }
    return 1;
  }

  /**
  * @brief check whether the CurrentDate is  greater or equal than the t_date
  */
  bool Date::operator>=(const Date &t_date) const {
  	if (*this > t_date || *this == t_date) {
  		return 1;
  	}
  	return 0;
  }

  /**
  * @brief check whether the CurrentDate is  less than or equal to the t_date
  */
  bool Date::operator<=(const Date &t_date) const {
  	if (*this < t_date || *this == t_date) {
  		return 1;
  	}
  	return 0;
  }
