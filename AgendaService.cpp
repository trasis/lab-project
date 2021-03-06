#include"AgendaService.h"
#include<iostream>
#include<functional>
using std::function;
using std::endl;
using std::cout;

AgendaService::AgendaService() {
    storage_ = Storage::getInstance();
}
AgendaService::~AgendaService() {
     delete storage_;
}
bool AgendaService::userLogIn(std::string userName, std::string password) {
     function<bool(const User&)> k = [userName, password](const User& user) {
       if (user.getPassword() == password && user.getName() == userName)
         return true;
      else
         return false;
    };
     std::list<User> r = storage_->queryUser(k);
    if (r.size() != 0) 
        return true;
    else 
       return false;
}

bool AgendaService::userRegister(std::string userName, std::string password,std::string email, std::string phone) {
     function<bool(const User&)> k = [userName, password, email, phone](const User& user) {
      if (user.getName() == userName)
         return false;
      else 
       return true;
    };
     std::list<User> r = storage_->queryUser(k);
   if (r.size() == 0) {
       User a(userName, password, email, phone);
       storage_->createUser(a);
       return true;
   }
     return false;
}

bool AgendaService::deleteUser(std::string userName, std::string password) {
     int r = 0;
     function<bool(const User&)> k = [userName, password](const User& user) {
       if (user.getPassword() == password && user.getName() == userName)
         return true;
      else
         return false;
    };
     r = storage_->deleteUser(k);
    if (r != 0) {
        deleteAllMeetings(userName);
        return true;
    }
       return false;
}

std::list<User> AgendaService::listAllUsers(void) {
       function<bool(const User&)> k = [](const User& a){
            return true;
       };
       std::list<User> r = storage_->queryUser(k);
       return r;
}

bool AgendaService::createMeeting(std::string userName, std::string title,
                     std::string participator,
                     std::string startDate, std::string endDate) {
       Date startdate = Date::stringToDate(startDate);
       Date enddate = Date::stringToDate(endDate);
       Meeting a(userName, participator, startdate, enddate, title);
       if (!Date::isValid(a.getStartDate()))    return false;
       if (!Date::isValid(a.getEndDate()))    return false;
       if (a.getStartDate() >= a.getEndDate())   
        cout << "1" << endl; 
        return false;
       function<bool(const Meeting&)> k = [userName, title, participator, startDate, endDate](const Meeting& b) {
        if(b.getSponsor() == userName)  
          return true;
        else 
          return false;
    };
       std::list<Meeting> r = storage_->queryMeeting(k);
    std::list<Meeting>::iterator it = r.begin();
    for (;it != r.end(); it++) {
       if (a.getStartDate() <= it->getEndDate() && a.getStartDate() >= it->getStartDate() && a.getEndDate() >= it->getEndDate())
         return false;
       if (a.getEndDate() >= it->getStartDate() && a.getEndDate() <= it->getEndDate() && a.getStartDate() <= it->getStartDate())
         return false;
       if (a.getStartDate() >= it->getStartDate() && a.getEndDate() <= it->getEndDate())
         return false;
       if (a.getStartDate() <= it->getStartDate() && a.getEndDate() >= it->getEndDate())
         return false;
    }
    k = [userName, title, participator, startDate, endDate](const Meeting& b) {
        if(b.getSponsor() == participator)  
          return true;
        else 
          return false;
    };
    r = storage_->queryMeeting(k);
    it = r.begin();
    for (;it != r.end(); it++) {
       if (a.getStartDate() <= it->getEndDate() && a.getStartDate() >= it->getStartDate() && a.getEndDate() >= it->getEndDate())
         return false;
       if (a.getEndDate() >= it->getStartDate() && a.getEndDate() <= it->getEndDate() && a.getStartDate() <= it->getStartDate())
         return false;
       if (a.getStartDate() >= it->getStartDate() && a.getEndDate() <= it->getEndDate())
         return false;
       if (a.getStartDate() <= it->getStartDate() && a.getEndDate() >= it->getEndDate())
         return false;
    }
    k = [userName, title, participator, startDate, endDate](const Meeting& b) {
        if(b.getParticipator() == userName)  
          return true;
        else 
          return false;
    };
    r = storage_->queryMeeting(k);
    it = r.begin();
    for (;it != r.end(); it++) {
       if (a.getStartDate() <= it->getEndDate() && a.getStartDate() >= it->getStartDate() && a.getEndDate() >= it->getEndDate())
         return false;
       if (a.getEndDate() >= it->getStartDate() && a.getEndDate() <= it->getEndDate() && a.getStartDate() <= it->getStartDate())
         return false;
       if (a.getStartDate() >= it->getStartDate() && a.getEndDate() <= it->getEndDate())
         return false;
       if (a.getStartDate() <= it->getStartDate() && a.getEndDate() >= it->getEndDate())
         return false;
    }
    k = [userName, title, participator, startDate, endDate](const Meeting& b) {
        if(b.getParticipator() == participator)  
          return true;
        else 
          return false;
    };
    r = storage_->queryMeeting(k);
    it = r.begin();
    for (;it != r.end(); it++) {
       if (a.getStartDate() <= it->getEndDate() && a.getStartDate() >= it->getStartDate() && a.getEndDate() >= it->getEndDate())
         return false;
       if (a.getEndDate() >= it->getStartDate() && a.getEndDate() <= it->getEndDate() && a.getStartDate() <= it->getStartDate())
         return false;
       if (a.getStartDate() >= it->getStartDate() && a.getEndDate() <= it->getEndDate())
         return false;
       if (a.getStartDate() <= it->getStartDate() && a.getEndDate() >= it->getEndDate())
         return false;
    }
    function<bool(const Meeting&)> filter3 = [userName,title](const Meeting &meeting) {
    if ((meeting.getSponsor() == userName) && (meeting.getTitle() == title)) 
           return true;
    else 
           return false;
   };
  if (storage_->queryMeeting(filter3).size() != 0) return false;
    function<bool(const User&)> ans = [userName](const User& b) {
        if(b.getName() == userName)  
          return true;
        else 
          return false;
    };
     if (storage_->queryUser(ans).size() == 0) 
          return false;
       return true;
    ans = [participator](const User& b) {
        if(b.getName() == participator)  
          return true;
        else 
          return false;
    };
     if (storage_->queryUser(ans).size() == 0) 
          return false;
     storage_->createMeeting(a);
     return true;
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string title) {
     function<bool(const Meeting&)> k =[userName, title](const Meeting& b) {
          if (b.getSponsor() == userName && b.getTitle() == title || b.getParticipator() == userName && b.getTitle() == title)
             return true;
          else
             return false;
      };
     std::list<Meeting> r = storage_->queryMeeting(k);
      return r;
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string startDate,
                                  std::string endDate) {
         function<bool(const Meeting&)> k = [userName, startDate, endDate](const Meeting& b) {
            if (b.getSponsor() == userName && b.getStartDate() > Date::stringToDate(startDate) && b.getEndDate() < Date::stringToDate(endDate) || b.getParticipator() == userName && b.getStartDate() > Date::stringToDate(startDate) && b.getEndDate() < Date::stringToDate(endDate))
               return true;
            else 
               return false;
         };
         std::list<Meeting> r = storage_->queryMeeting(k);
            return r;
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
          function<bool(const Meeting&)> k = [userName](const Meeting& b) {
            if (b.getSponsor() == userName || b.getParticipator() == userName)
               return true;
            else
               return false;
          };
          std::list<Meeting> r = storage_->queryMeeting(k);
           return r;
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
           function<bool(const Meeting&)> k = [userName](const Meeting& b) {
            if (b.getSponsor() == userName || b.getParticipator() == userName)
               return true;
            else
               return false;
          };
      std::list<Meeting> r = storage_->queryMeeting(k);
      return r;
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(std::string userName){
       function<bool(const Meeting&)> k = [userName](const Meeting& b) {
          if (b.getParticipator() == userName)
             return true;
          else
           return false;
       };
       std::list<Meeting> r = storage_->queryMeeting(k);
      return r;
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
       function<bool(const Meeting&)>  k = [userName, title](const Meeting& b) {
          if (b.getSponsor() == userName && b.getTitle() == title || b.getParticipator() == userName && b.getTitle() == title)
             return true;
          else
             return false;
      };
      int count = 0;
      count = storage_->deleteMeeting(k);
     if (count == 0) 
      return false;
     else
       return true;
}

bool AgendaService::deleteAllMeetings(std::string userName) {
       int count = 0;
       function<bool(const Meeting&)> k = [userName](const Meeting& b) {
            if (b.getSponsor() == userName || b.getParticipator() == userName)
               return true;
            else
               return false;
          };
       count = storage_->deleteMeeting(k);
     if (count == 0) 
      return false;
     else
       return true;
}

void AgendaService::startAgenda(void) {
  storage_ = Storage::getInstance();
}

void AgendaService::quitAgenda(void) {
  storage_->sync();
}
      
        


     
     
