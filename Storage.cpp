#include "Storage.h"
#include <fstream>
#include <functional>
#include <iostream>

using namespace std;

Storage* Storage::instance_ = 0;

Storage::Storage() {
  readFromFile("Agenda.data");
}

void Storage::createUser(const User& newUser) {
  userList_.push_back(newUser);
}

void Storage::createMeeting(const Meeting& newMeeting) {
  meetingList_.push_back(newMeeting);
}



Storage* Storage::getInstance(void) {
  if (instance_ == 0)
   instance_ = new Storage;
  return instance_;
}

Storage::~Storage() {
  sync();
  Storage::instance_ = 0;
}

list<User> Storage::queryUser(function<bool(const User&)> filter) {
  list<User> cUser;
  list<User>::iterator iter;
  for (iter = userList_.begin(); iter != userList_.end(); iter++) {
    if (filter(*iter)) 
      cUser.push_back(*iter);
  }
  return cUser;
}

int Storage::updateUser(function<bool(const User&)> filter, function<void(User&)> switcher) {
  list<User>::iterator iter;
  int count = 0;
  for (iter = userList_.begin(); iter != userList_.end(); ++iter) {
    if (filter(*iter)) {
      switcher(*iter);
      count++;
    }
  }
  return count;
}

int Storage::deleteUser(function<bool(const User&)> filter) {
  list<User>::iterator iter;
  int count = 0;
  for (iter = userList_.begin(); iter != userList_.end(); iter++) {
    if (filter(*iter)) {
      list<User>::iterator next = iter;
      next++;
      userList_.erase(iter);
      iter = next;
      count++;
    }
  }
  return count;
}

list<Meeting> Storage::queryMeeting(function<bool(const Meeting&)> filter) {
  list<Meeting> cMeeting;
   list<Meeting>::iterator iter;
  for (iter = meetingList_.begin(); iter != meetingList_.end(); iter++) {
    if (filter(*iter)) 
      cMeeting.push_back(*iter);
  }
  return cMeeting;
}

int Storage::updateMeeting(function<bool(const Meeting&)> filter, function<void(Meeting&)> switcher) {
  list<Meeting>::iterator iter;
  int count = 0;
 for (iter = meetingList_.begin(); iter != meetingList_.end(); iter++) {
    if (filter(*iter)) {
      switcher(*iter);
      count++;
    }
  }
  return count;
}

int Storage::deleteMeeting(function<bool(const Meeting&)> filter) {
  list<Meeting>::iterator iter;
  int count = 0;
for (iter = meetingList_.begin(); iter != meetingList_.end(); iter++) {
    if (filter(*iter)) {
      list<Meeting>::iterator next = iter;
      next++;
      meetingList_.erase(iter);
      iter = next;
      count++;
    }
  }
  return count;
}

bool Storage::sync() {
    if (writeToFile("Agenda.Data")) 
      return true;
    else 
      return false;
}

bool Storage::readFromFile(const char *fpath) {
  fstream infile(fpath);
  if (!infile)
     return false;
   if (infile.peek() == EFO) {
       infile.close();
       return true; 
   }
  string r;
  getline(infile, r);
  int num = r[r.size() - 2] - '0';
  for (int i = 0; i < num; ++i) {
    getline(infile, r);
    int s = 0;
    string name = "";
    while (r[s] != '\"') {
       s++;
    }
    s++;
    while (r[s] != '\"') {
      name += r[s];
      s++;
    }
    s++;
    string password = "";
    while (r[s] != '\"'){
       s++;
    }
    s++;
    while (r[s] != '\"') {
      password += r[s];
      s++;
    }
    s++;
    string email = "";
    while (r[s] != '\"') {
       s++;
    }
    s++;
    while (r[s] != '\"') {
      email += r[s];
      s++;
    }
    s++;
    string phone = "";
    while (r[s] != '\"'){
          s++;
    }
    s++;
    while (r[s] != '\"') {
      phone += r[s];
      s++;
    }
    createUser(User(name, password, email, phone));
  }
  getline(infile, r);
  num = r[r.size() - 2]-'0';
  for (int i = 0; i < num; ++i) {
    int s = 0;
    getline(infile, r);
    while (r[s] != '\"'){
        s++;
    }
    s++;
    string sponsor = "";
    while (r[s] != '\"') {
      sponsor += r[s];
      s++;
    }
    s++;
    while (r[s] != '\"') s++;
    s++;
    string participator = "";
    while (r[s] != '\"') {
      participator += r[s];
      s++;
    }
    s++;
    while (r[s] != '\"'){
      s++;
    }
    s++;
    string sdate = "";
    while (r[s] != '\"') {
      sdate += r[s];
      s++;
    }
    s++;
    Date sd = Date::stringToDate(sdate);
    while (r[s] != '\"'){
       s++;
    }
    s++;
    string edate = "";
    while (r[s] != '\"') {
      edate += r[s++];
    }
    Date ed = Date::stringToDate(edate);
    s++;
    while (r[s] != '\"'){
          s++;
    }
    s++;
    string title = "";
    while (r[s] != '"') {
      title += r[s++];
    }
    createMeeting(Meeting(sponsor, participator, sd, ed, title));
  }
  infile.close();
  return true;
}

bool Storage::writeToFile(const char *fpath) {
  FILE *fp;
  if ((fp=fopen(fpath,"w+")) == NULL) {
      return false;
   }
  fclose(fp);
  fstream out(fpath);
  if (!out) {
        return false;
  }
  int size = userList_.size();
  out << "{collection:\"User\", total:" << size << '}' << endl;
  list<User>::iterator iter;
  for (iter = userList_.begin(); iter != userList_.end(); iter++) {
    out << "{name:" << '\"' << iter->getName() << "\",password:\""
    << iter->getPassword() << "\",email:\"" << iter->getEmail()
    << "\",phone:\"" << iter->getPhone() << "\"}" << endl;
  }
  size = meetingList_.size();
  out << "{collection:\"Meeting\",total:" << size << '}' << endl;
  list<Meeting>::iterator iter2;
  for (iter2 = meetingList_.begin(); iter2 != meetingList_.end(); iter2++) {
    out << "{sponsor:" << '\"' << iter2->getSponsor() << 
    "\",participator: \"" << iter2->getParticipator() << "\",sdate:\"" << Date::dateToString(iter2->getStartDate()) << "\",edate:\"" << Date::dateToString(iter2->getEndDate()) << "\",title:\""
<< iter2->getTitle() << "\"}" << endl;
  }
  out.close();
  return true;
}



