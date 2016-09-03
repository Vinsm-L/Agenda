#include "Storage.hpp"
#include "Path.hpp"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

Storage::Storage() {
  m_dirty = 0;
  readFromFile();
}

bool Storage::readFromFile(void) {
  ifstream infile1, infile2;
  infile1.open(Path::userPath);
  if (!infile1)
    return 0;
  string str;
  while (getline(infile1, str)) {
    string a[4];
    int j = 0;
    string s = "";
    for (int i = 0; i < str.length(); i++) {
      if (str[i] == '"') {
        continue;
      }
      if (str[i] == ',') {
        a[j] = s;
        j++;
        s = "";
      } else {
        s += str[i];
      }
    }
    a[j] = s;
    str = "";
    User temp(a[0], a[1], a[2], a[3]);
    m_userList.push_back(temp);
  }
  infile1.close();
  infile2.open(Path::meetingPath);
  if (!infile2)
    return 0;
  while (getline(infile2, str)) {
    string a[5];
    int j = 0;
    string s = "";
    for (int i = 0; i < str.length(); i++) {
      if (str[i] == '"') {
        continue;
      }
      if (str[i] == ',') {
        a[j] = s;
        j++;
        s = "";
      } else {
        s += str[i];
      }
    }
    a[j] = s;
    str = "";
    vector<string> pa;
    string pati = "";
    for (int i = 0; i < a[1].length(); i++) {
      if (a[1][i] == '&') {
        pa.push_back(pati);
        pati = "";
      } else {
        pati += a[1][i];
      }
    }
    pa.push_back(pati);
    Date sta = Date::stringToDate(a[2]);
    Date end = Date::stringToDate(a[3]);
    Meeting temp(a[0], pa, sta, end, a[4]);
    m_meetingList.push_back(temp);
  }
  infile2.close();
  return 1;
}

bool Storage::writeToFile(void) {
  ofstream outfile1;
  outfile1.open(Path::userPath);
  if (!outfile1)
    return 0;
  for (auto it = m_userList.begin(); it != m_userList.end(); ++it) {
    string str = "\"" + (*it).getName() + "\"" + "," + "\"" + (*it).getPassword() + "\"" + "," + "\"" + (*it).getEmail() + "\"" + "," + "\"" + (*it).getPhone() + "\"";
    outfile1 << str << endl;
  }
  outfile1.close();
  ofstream outfile2;
  outfile2.open(Path::meetingPath);
  if (!outfile2)
    return 0;
  for (auto it = m_meetingList.begin(); it != m_meetingList.end(); ++it) {
    string str = "\"" + (*it).getSponsor() + "\"" + "," + "\"";
    if ((*it).getParticipator().size() > 0)
      str += (*it).getParticipator()[0];
    for (int i = 1; i < (*it).getParticipator().size(); i++) {
      str += "&" + (*it).getParticipator()[i];
    }
    str += "\"";
    str += ",";
    str += "\"";
    string tt = Date::dateToString((*it).getStartDate()) + "\"" + "," + "\"" + Date::dateToString((*it).getEndDate()) + "\"" + "," + "\"" + (*it).getTitle() + "\"";
    str = str + tt;
    outfile2 << str << endl;
  }
  outfile2.close();
  return 1;
}

 /**
  * get Instance of storage
  * @return the pointer of the instance
  */
  std::shared_ptr<Storage> Storage::m_instance = NULL;

  std::shared_ptr<Storage> Storage::getInstance(void) {
    if (m_instance == NULL) {
      m_instance.reset(new Storage());
    }
    return m_instance;
  }

  /**
  *   destructor
  */
  Storage::~Storage() {
    writeToFile();
    m_instance.reset();
  }

  // CRUD for User & Meeting
  // using C++11 Function Template and Lambda Expressions

  /**
  * create a user
  * @param a user object
  */
  void Storage::createUser(const User & t_user) {
    User temp = t_user;
    m_userList.push_back(temp);
    m_dirty = 1;
    writeToFile();
  }

  /**
  * query users
  * @param a lambda function as the filter
  * @return a list of fitted users
  */
  std::list<User> Storage::queryUser(std::function<bool(const User & u)> filter) const {
    list<User> temp;
    for (auto it = m_userList.begin(); it != m_userList.end(); ++it) {
      if (filter(*it)) {
        temp.push_back(*it);
      }
    }
    return temp;
  }

  /**
  * update users
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the user
  * @return the number of updated users
  */
  int Storage::updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher) {
    int num = 0;
    for (auto it = m_userList.begin(); it != m_userList.end(); ++it) {
      if (filter(*it)) {
        switcher(*it);
        num++;
      }
    }
    if (num) {
      m_dirty = 1;
      writeToFile();
    }
    return num;
  }

  /**
  * delete users
  * @param a lambda function as the filter
  * @return the number of deleted users
  */
  int Storage::deleteUser(std::function<bool(const User &)> filter) {
    int num = 0;
    for (auto it = m_userList.begin(); it != m_userList.end(); it++) {
      if (filter(*it)) {
        it = m_userList.erase(it);
        it--;
        num++;
      }
    }
    if (num) {
      m_dirty = 1;
      writeToFile();
    }
    return num;
  }

  /**
  * create a meeting
  * @param a meeting object
  */
  void Storage::createMeeting(const Meeting & t_meeting) {
    Meeting temp = t_meeting;
    m_meetingList.push_back(temp);
    m_dirty = 1;
    writeToFile();
  }

  /**
  * query meetings
  * @param a lambda function as the filter
  * @return a list of fitted meetings
  */
  std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting &)> filter) const {
    list<Meeting> temp;
    for (auto it = m_meetingList.begin(); it != m_meetingList.end(); ++it) {
      if (filter(*it)) {
        temp.push_back(*it);
      }
    }
    return temp;
  }

  /**
  * update meetings
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the meeting
  * @return the number of updated meetings
  */
  int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)> switcher) {
    int num = 0;
    for (auto it = m_meetingList.begin(); it != m_meetingList.end(); ++it) {
      if (filter(*it)) {
        switcher(*it);
        num++;
      }
    }
    if (num) {
      m_dirty = 1;
      writeToFile();
    }
    return num;
  }

  /**
  * delete meetings
  * @param a lambda function as the filter
  * @return the number of deleted meetings
  */
  int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
    int num = 0;
    for (auto it = m_meetingList.begin(); it != m_meetingList.end(); it++) {
      if (filter(*it)) {
        it = m_meetingList.erase(it);
        it--;
        num++;
      }
    }
    if (num) {
      m_dirty = 1;
      writeToFile();
    }
    return num;
  }

  /**
  * sync with the file
  */
  bool Storage::sync(void) {
    writeToFile();
    return 1;
  }
