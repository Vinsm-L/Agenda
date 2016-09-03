#include "AgendaService.hpp"
using namespace std;

    AgendaService::AgendaService() {
    	startAgenda();
    }

    /**
     * destructor
     */
    AgendaService::~AgendaService() {
    	quitAgenda();
    }

    /**
     * check if the username match password
     * @param userName the username want to login
     * @param password the password user enter
     * @return if success, true will be returned
     */
     //[](xx xxx) -> xxx {}
    bool AgendaService::userLogIn(const std::string userName, const std::string password) {
    	list<User> match = m_storage->queryUser([userName](const User &u) -> bool {
    		if (u.getName() == userName) {
    			return 1;
    		}
    		return 0;
    	});
    	bool flag = 0;
    	if (match.size() == 0) {
    		return 0;
    	} else {
    		for (auto it = match.begin(); it != match.end(); ++it) {
    			if ((*it).getPassword() == password) {
    				flag = 1;
    				break;
    			}
    		}
    	}
    	return flag;
    }

    /**
     * regist a user
     * @param userName new user's username
     * @param password new user's password
     * @param email new user's email
     * @param phone new user's phone
     * @return if success, true will be returned
     */
    bool AgendaService::userRegister(const std::string userName, const std::string password,
                      const std::string email, const std::string phone) {
    	list<User> match = m_storage->queryUser([userName](const User &u) -> bool {
    		if (u.getName() == userName) {
    			return 1;
    		}
    		return 0;
    	});
    	if (match.size() == 0) {
    		User temp(userName, password, email, phone);
    		m_storage->createUser(temp);
    		return 1;
    	}
    	return 0;
    }

    /**
     * delete a user
     * @param userName user's username
     * @param password user's password
     * @return if success, true will be returned
     */
    bool AgendaService::deleteUser(const std::string userName, const std::string password) {
    	list<User> match = m_storage->queryUser([userName, password](const User &u) -> bool {
    		if (u.getName() == userName&&u.getPassword() == password) {
    			return 1;
    		}
    		return 0;
    	});
    	if (match.size() == 0) {
    		return 0;
    	}
    	m_storage->deleteMeeting([userName](const Meeting &m) -> bool {
    			if (m.getSponsor() == userName) {
    				return 1;
    			}
    			for (int i = 0; i < m.getParticipator().size(); i++) {
    				if (m.getParticipator()[i] == userName)
    					return 1;
    			}
    			return 0;
    	});
    	for (auto it = match.begin(); it != match.end(); ++it) {
    		m_storage->deleteUser([&](const User &u) -> bool {
    			if (u.getName() == (*it).getName()) {
    				return 1;
    			}
    			return 0;
    		});
    	}
    	return 1;
    }

    /**
     * list all users from storage
     * @return a user list result
     */
    std::list<User> AgendaService::listAllUsers(void) const {
    	list<User> match = m_storage->queryUser([](const User &u) -> bool {
    		return 1;
    	});
    	return match;
    }

    /**
     * create a meeting
     * @param userName the sponsor's userName
     * @param title the meeting's title
     * @param participator the meeting's participator
     * @param startData the meeting's start date
     * @param endData the meeting's end date
     * @return if success, true will be returned
     */
    bool AgendaService::createMeeting(const std::string userName, const std::string title,
                       const std::string startDate, const std::string endDate,
                       const std::vector<std::string> participator) {
        Date startD = Date::stringToDate(startDate);
        Date endD = Date::stringToDate(endDate);
    	if (startD >= endD) {
    		return 0;
    	}
        for (int i = 0; i < participator.size(); i++) {
            if (userName == participator[i])
                return 0;
        }
    	list<Meeting> match = m_storage->queryMeeting([=](const Meeting & m) -> bool {
    		if (title == m.getTitle()) {
    			return 1;
    		}
    		if (m.getSponsor() == userName) {
    			if (m.getEndDate() <= startD) {
    			} else if (m.getStartDate() >= endD) {
    			} else {
    				return 1;
    			}
    		}
    		for (int i = 0; i < m.getParticipator().size(); i++) {
    			for (int j = 0; j < participator.size(); j++) {
    				if (m.getParticipator()[i] == participator[j]) {
    					if (m.getEndDate() <= startD) {
    			} else if (m.getStartDate() >= endD) {
    			} else {
    				return 1;
    			}
    				}
    			}
    		}
    		for (int i = 0; i < m.getParticipator().size(); i++) {
    			if (m.getParticipator()[i] == userName) {
    				if (m.getEndDate() <= startD) {
    			} else if (m.getStartDate() >= endD) {
    			} else {
    				return 1;
    			}
    			}
    		}
    		for (int j = 0; j < participator.size(); j++) {
    			if (m.getSponsor() == participator[j]) {
    				if (m.getEndDate() <= startD) {
    			} else if (m.getStartDate() >= endD) {
    			} else {
    				return 1;
    			}
    			}
    		}
    		return 0;
    	});
        if (match.size() > 0) {
        	return 0;
        }
        list<User> u1 = m_storage->queryUser([userName](const User &u) -> bool {
    		if (u.getName() == userName) {
    			return 1;
    		}
    		return 0;
    	});
    	if (u1.size() != 1)
    		return 0;
    	list<User> u2 = m_storage->queryUser([participator](const User &u) -> bool {
    		for (int i = 0; i < participator.size(); i++) {
    			if (participator[i] == u.getName())
    				return 1;
    		}
    		return 0;
    	});
    	if (u2.size() != participator.size())
    		return 0;
        Meeting me(userName, participator, startD, endD, title);
        m_storage->createMeeting(me);
    	return 1;
    }

    /**
     * search meetings by username and title (user as sponsor or participator)
     * @param uesrName the user's userName
     * @param title the meeting's title
     * @return a meeting list result
     */
    std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string title) const {
    	list<Meeting> match = m_storage->queryMeeting([title, userName](const Meeting & m) -> bool {
    		if (m.getTitle() == title) {
    			if (m.getSponsor() == userName) {
    				return 1;
    			} else {
    				for (int i = 0; i < m.getParticipator().size(); i++) {
    					if (m.getParticipator()[i] == userName) {
    						return 1;
    					}
    				}
    			}
    		}
            return 0;
    	});
    	return match;
    }
    /**
     * search a meeting by username, time interval (user as sponsor or participator)
     * @param uesrName the user's userName
     * @param startDate time interval's start date
     * @param endDate time interval's end date
     * @return a meeting list result
     */
    std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string startDate,
                                    const std::string endDate) const {
    	list<Meeting> temp;
        Date startD = Date::stringToDate(startDate);
        Date endD = Date::stringToDate(endDate);
    	if (startD > endD)
    		return temp;
    	if (!Date::isValid(startD) || !Date::isValid(endD))
    		return temp;
    	list<Meeting> match = m_storage->queryMeeting([=](const Meeting & m) -> bool {
    		int flag = 0;
    		if (m.getSponsor() == userName) {
    			flag++;
    		}
    			for (int i = 0; i < m.getParticipator().size(); i++) {
    				if (m.getParticipator()[i] == userName) {
    					flag++;
    				}
    			}
    		if (flag == 0)
    			return 0;
    		if ((m.getStartDate() >= startD&&m.getStartDate() <= endD) || (m.getEndDate() >= startD&&m.getEndDate() <= endD) || (m.getStartDate() <= startD&&m.getEndDate() >= endD)) {
    			return 1;
    		} else {
    			return 0;
    		}
    	});
    	return match;
    }

    /**
     * list all meetings the user take part in
     * @param userName user's username
     * @return a meeting list result
     */
    std::list<Meeting> AgendaService::listAllMeetings(const std::string userName) const {
    	list<Meeting> match = m_storage->queryMeeting([userName](const Meeting & m) -> bool {
    		if (m.getSponsor() == userName) {
    				return 1;
    		}
    		for (int i = 0; i < m.getParticipator().size(); i++) {
    				if (m.getParticipator()[i] == userName) {
    					return 1;
    				}
    		}
    		return 0;
    	});
    	return match;
    }

    /**
     * list all meetings the user sponsor
     * @param userName user's username
     * @return a meeting list result
     */
    std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string userName) const {
    	list<Meeting> match = m_storage->queryMeeting([userName](const Meeting & m) -> bool {
    		if (m.getSponsor() == userName) {
    				return 1;
    		}
    		return 0;
    	});
    	return match;
    }

    /**
     * list all meetings the user take part in and sponsor by other
     * @param userName user's username
     * @return a meeting list result
     */
    std::list<Meeting> AgendaService::listAllParticipateMeetings(
        const std::string userName) const {
    	list<Meeting> match = m_storage->queryMeeting([userName](const Meeting & m) -> bool {
    		for (int i = 0; i < m.getParticipator().size(); i++) {
    				if (m.getParticipator()[i] == userName) {
    					return 1;
    				}
    		}
    		return 0;
    	});
    	return match;
    }

    /**
     * delete a meeting by title and its sponsor
     * @param userName sponsor's username
     * @param title meeting's title
     * @return if success, true will be returned
     */
    bool AgendaService::deleteMeeting(const std::string userName, const std::string title) {
    	int num = m_storage->deleteMeeting([userName, title](const Meeting & m) -> bool {
    		if (m.getSponsor() == userName&&m.getTitle() == title) {
    				return 1;
    		}
    		return 0;
    	});
    	return (num > 0);
    }

    /**
     * delete all meetings by sponsor
     * @param userName sponsor's username
     * @return if success, true will be returned
     */
    bool AgendaService::deleteAllMeetings(const std::string userName) {
    	int num = m_storage->deleteMeeting([userName](const Meeting & m) -> bool {
    		if (m.getSponsor() == userName) {
    				return 1;
    		}
    		return 0;
    	});
    	return (num > 0);
    }

    /**
     * start Agenda service and connect to storage
     */
    void AgendaService::startAgenda(void) {
    	m_storage = Storage::getInstance();
    }

    /**
     * quit Agenda service
     */
    void AgendaService::quitAgenda(void) {
    	m_storage->sync();
        m_storage = NULL;
    }
