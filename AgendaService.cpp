#include"AgendaService.h"
#include<functional>
using std::function;

AgendaService::AgendaService() {
    storage_ = Storage::getInstance();
}
AgendaService::~AgendaService() {
     delete storage_;
}
bool AgendaService::userLogIn(std::string userName, std::string password) {
     function<bool(const User&)> k = [userName, password](const User& user) {
       if (user.getpassword() == password && user.getName() == userName)
         return true;
      else
         return false;
    };
     std::list<User> r = storage_->queryUser(k);
    if (r.size() == 0) 
        return true;
    else 
       return false;
}

bool AgendaService::userRegister(std::string userName, std::string password,std:string email, std::string phone) {
     function<bool(const User&)> k = [userName, password, email, phone](const User& user) {
      if (user.getName() == userName)
         return false;
      else 
       return true;
    };
     std::list<User> r = storage_->queryUser(k);
   if (r.size() != 0)
       return true;
   else 
     return false;
}

bool AgendaService::deleteUser(std::string userName, std::string password) {
     int r = 0;
     function<bool(const Use&)> k = [userName, password](const User& user) {
       if (user.getpassword() == password && user.getName() == userName)
         return true;
      else
         return false;
    };
     r = storage_->deleteUser(k);
    if (r == 0)
        return true;
    else 
       return false;
}

std::list<User> AgendaService::listAllUsers(void) {
       function<bool(const Use&)> k = true;
       std::list<User> r = storage_->queryUser(k);
       return r;
}

bool AgendaService::createMeeting(std::string userName, std::string title,
                     std::string participator,
                     std::string startDate, std::string endDate) {
       Meeting a(useName, title, participator, startDate, endDate);
       if (!a.getStartDate().isvalid())    return false;
       if (!a.getEndDate().isvalid())    return false;
       if (!(a.getStartDate() <= a.getEndDate()))    return false;
       function<bool(const Meeting&)> k = [userName, title, participator, startDate, endDate](const Meeting& b) {
        if(b.getSponsor() == userName)  
          return true;
        else 
          return false;
    };
       std::list<Meeting> r = storage_->queryMeeting(k);
    std::list<Meeting>::iterator it = r.begin();
    for (;it != r.end(); it++) {
       if (a.getStartDate() < it->getEndDate() && a.getStartDate() > it->getStartDate())
         return false;
       if (a.getEndDate() > it->getStartDate() && a.getEndDate() < it->getEndDate())
         return false;
    }
    k = [userName, title, participator, startDate, endDate](const Meeting& b) {
        if(b.getSponsor() == participator)  
          return true;
        else 
          return false;
    };
    r = storage_->queryMeeting(k);
    std::list<Meeting>::iterator it = r.begin();
    for (;it != r.end(); it++) {
       if (a.getStartDate() < it->getEndDate() && a.getStartDate() > it->getStartDate())
         return false;
       if (a.getEndDate() > it->getStartDate() && a.getEndDate() < it->getEndDate())
         return false;
    }
    k = [userName, title, participator, startDate, endDate](const Meeting& b) {
        if(b.getParticipator() == userName)  
          return true;
        else 
          return false;
    };
    r = storage_->queryMeeting(k);
    std::list<Meeting>::iterator it = r.begin();
    for (;it != r.end(); it++) {
       if (a.getStartDate() < it->getEndDate() && a.getStartDate() > it->getStartDate())
         return false;
       if (a.getEndDate() > it->getStartDate() && a.getEndDate() < it->getEndDate())
         return false;
    }
    k = [useName, title, participator, startDate, endDate](const Meeting& b) {
        if(b.getParticipator() == participator)  
          return true;
        else 
          return false;
    };
    r = storage_->queryMeeting(k);
    std::list<Meeting>::iterator it = r.begin();
    for (;it != r.end(); it++) {
       if (a.getStartDate() < it->getEndDate() && a.getStartDate() > it->getStartDate())
         return false;
       if (a.getEndDate() > it->getStartDate() && a.getEndDate() < it->getEndDate())
         return false;
    }
    k = [useName](const User& b) {
        if(b.getName() == userName)  
          return true;
        else 
          return false;
    };
    r = storage_->queryMeeting(k);
     if (r.size() == 0) 
          return false;
   k = [title, participator, startDate, endDate](const Meeting& b) {
        if(b.getName() == participator)  
          return true;
        else 
          return false;
    };
   r = storage_->queryMeeting(k);
     if (r.size() == 0) 
          return false;
     return true;
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string title) {
     function<bool(const Meeting&)> k =[userName, title](const Meeting& b) {
          if (b.getSponsor() == userName && b.getTile() == title || b.getParticipator() == userName && b.getTile() == title)
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
               return true
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
       count = storage_->queryMeeting(k);
     if (count == 0) 
      return false;
     else
       return true;
}
 
      
        


     
     
