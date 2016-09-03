#include "AgendaUI.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

    AgendaUI::AgendaUI() {
    	startAgenda();
    }

    void AgendaUI::OperationLoop(void) {
    	bool flag = 1;
    	while (flag) {
    		string ope = getOperation();
    		flag = executeOperation(ope);
    	}
    }

    /**
     * constructor
     */
    void AgendaUI::startAgenda(void) {
    	cout << "--------------------------------Agenda----------------------------------" << endl;
    	cout << "Action :" << endl;
    	cout << "l    - log in agenda by user name and password" << endl;
    	cout << "r    - register an angenda account" << endl;
    	cout << "q    - quit agenda" << endl;
    	cout << "------------------------------------------------------------------------" << endl;
    	cout << endl;
    	cout << "Agenda : ~$";
    }

    /**
     * catch user's operation
     * @return the operation
     */
    std::string AgendaUI::getOperation() {
    	string oper;
    	cin >> oper;
    	return oper;
    }

    /**
     * execute the operation
     * @return if the operationloop continue
     */
    bool AgendaUI::executeOperation(std::string t_operation) {
    	if (t_operation == "l") {
    		userLogIn();
    		return 1;
    	}
    	if (t_operation == "r") {
    		userRegister();
    		return 1;
    	}
    	if (t_operation == "q") {
            quitAgenda();
       		return 0;
    	}
    	if (t_operation == "dc") {
            deleteUser();
            return 1;
    	}
        if (t_operation == "lu") {
            listAllUsers();
            return 1;
        }
        if (t_operation == "cm") {
            createMeeting();
            return 1;
        }
        if (t_operation == "la") {
            listAllMeetings();
            return 1;
        }
        if (t_operation == "las") {
            listAllSponsorMeetings();
            return 1;
        }
        if (t_operation == "lap") {
            listAllParticipateMeetings();
            return 1;
        }
        if (t_operation == "qm") {
            queryMeetingByTitle();
            return 1;
        }
        if (t_operation == "qt") {
            queryMeetingByTimeInterval();
            return 1;
        }
        if (t_operation == "dm") {
            deleteMeetingByTitle();
            return 1;
        }
        if (t_operation == "da") {
            deleteAllMeetings();
            return 1;
        }
        if (t_operation == "o") {
            userLogOut();
            return 1;
        }
    }

    /**
     * user Login
     */
    void AgendaUI::userLogIn(void) {
    	cout << "[log in] [user name] [password]" << endl;
    	cout << "[log in] ";
    	string nam, pas;
    	cin >> nam >> pas;
    	bool flag = m_agendaService.userLogIn(nam, pas);
    	if (flag) {
    		m_userName = nam;
    		m_userPassword = pas;
            cout << endl;
    		cout << "[log in] succeed!" << endl;
    		cout << endl;
    		cout << "--------------------------------Agenda----------------------------------" << endl;
    		cout << "Action :" << endl;
    		cout << "o    - log out agenda" << endl;
    		cout << "dc   - delete agenda account" << endl;
    		cout << "lu   - list all agenda user" << endl;
    		cout << "cm   - create a meeting" << endl;
    		cout << "la   - list all meetings" << endl;
    		cout << "las  - list all sponsor meetings" << endl;
    		cout << "lap  - list all participate meetings" << endl;
    		cout << "qm   - query meeting by title" << endl;
    		cout << "qt   - query meeting by time interval" << endl;
    		cout << "dm   - delete meeting by title" << endl;
    		cout << "da   - delete all meetings" << endl;
    		cout << "------------------------------------------------------------------------" << endl;
            cout << endl;
    		cout << "Agenda@" << m_userName << " : #";
    	} else {
            cout << endl;
    		cout << "[error] log in fail!" << endl;
    		cout << endl;
            cout << "--------------------------------Agenda----------------------------------" << endl;
            cout << "Action :" << endl;
            cout << "l    - log in agenda by user name and password" << endl;
            cout << "r    - register an angenda account" << endl;
            cout << "q    - quit agenda" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            cout << endl;
            cout << "Agenda : ~$";
    	}
    	
    }

    /*=*
     * user regist
     */
    void AgendaUI::userRegister(void) {
        cout << endl;
    	cout << "[register] [user name] [password] [email] [phone]" << endl;
    	cout << "[register] ";
    	string nam, pas, ema, pho;
    	cin >> nam >> pas >> ema >> pho;
    	bool flag = m_agendaService.userRegister(nam, pas, ema, pho);
    	if (flag) {
    		m_userName = nam;
    		m_userPassword = pas;
            cout << endl;
    		cout << "[register] succeed!" << endl;
    	} else {
            cout << endl;
    		cout << "[error] register fail!" << endl;
    	}
        cout << endl;
        cout << "--------------------------------Agenda----------------------------------" << endl;
        cout << "Action :" << endl;
        cout << "l    - log in agenda by user name and password" << endl;
        cout << "r    - register an angenda account" << endl;
        cout << "q    - quit agenda" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << endl;
        cout << "Agenda : ~$";
    }

    /**
     * quit the Agenda
     */
    void AgendaUI::quitAgenda(void) {
        cout << endl;
        cout << "see you :)" << endl;
        cout << endl;
    }

    /**
     * user logout
     */
    void AgendaUI::userLogOut(void) {
        m_userName = "";
        m_userPassword = "";
        cout << endl;
        cout << "--------------------------------Agenda----------------------------------" << endl;
        cout << "Action :" << endl;
        cout << "l    - log in agenda by user name and password" << endl;
        cout << "r    - register an angenda account" << endl;
        cout << "q    - quit agenda" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << endl;
        cout << "Agenda : ~$";
    }

    /**
     * delete a user from storage
     */
    void AgendaUI::deleteUser(void) {
        m_agendaService.deleteUser(m_userName, m_userPassword);
        cout << endl;
        cout << "[delete agenda account] succeed!" << endl;
        cout << endl;
        cout << "--------------------------------Agenda----------------------------------" << endl;
        cout << "Action :" << endl;
        cout << "l    - log in agenda by user name and password" << endl;
        cout << "r    - register an angenda account" << endl;
        cout << "q    - quit agenda" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << endl;
        cout << "Agenda : ~$";
    }

    /**
     * list all users from storage
     */
    void AgendaUI::listAllUsers(void) {
        cout << endl;
        cout << "[list all users]" << endl;
        cout << endl;
        cout << "[name]              [email]             [phone]" << endl;
        list<User> u = m_agendaService.listAllUsers();
        for (auto it = u.begin(); it != u.end(); it++) {
            cout << setw(20);
            cout << setiosflags(ios::left);
            cout << (*it).getName() ;
            cout << setw(20);
            cout << setiosflags(ios::left);
            cout << (*it).getEmail() ;
            cout << setw(20);
            cout << setiosflags(ios::left);
            cout << (*it).getPhone() << endl;
        }
        cout << endl;
        cout << "--------------------------------Agenda----------------------------------" << endl;
        cout << "Action :" << endl;
        cout << "o    - log out agenda" << endl;
        cout << "dc   - delete agenda account" << endl;
        cout << "lu   - list all agenda user" << endl;
        cout << "cm   - create a meeting" << endl;
        cout << "la   - list all meetings" << endl;
        cout << "las  - list all sponsor meetings" << endl;
        cout << "lap  - list all participate meetings" << endl;
        cout << "qm   - query meeting by title" << endl;
        cout << "qt   - query meeting by time interval" << endl;
        cout << "dm   - delete meeting by title" << endl;
        cout << "da   - delete all meetings" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << endl;
        cout << "Agenda@" << m_userName << " : #";
    }

    /**
     * user create a meeting with someone else
     */
    void AgendaUI::createMeeting(void) {
        cout << endl;
        cout << "[create meeting] [the number of participators]" << endl;
        cout << "[create meeting] ";
        int num;
        cin >> num;
        string p;
        vector<string> parti;
        for (int i = 1; i <= num; i++) {
            cout << "[create meeting] [please enter the participator " << i << " ]" << endl;
            cout << "[create meeting] ";
            cin >> p;
            parti.push_back(p);
        }
        cout << "[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
        cout << "[create meeting] ";
        string tit, sta, end;
        cin >> tit >> sta >> end;
        bool flag = m_agendaService.createMeeting(m_userName, tit, sta, end, parti);
        if (flag) {
            cout << "[create meeting] succeed!" << endl;
        } else {
            cout << "[create meeting] error!" << endl;
        }
        cout << endl;
        cout << "--------------------------------Agenda----------------------------------" << endl;
        cout << "Action :" << endl;
        cout << "o    - log out agenda" << endl;
        cout << "dc   - delete agenda account" << endl;
        cout << "lu   - list all agenda user" << endl;
        cout << "cm   - create a meeting" << endl;
        cout << "la   - list all meetings" << endl;
        cout << "las  - list all sponsor meetings" << endl;
        cout << "lap  - list all participate meetings" << endl;
        cout << "qm   - query meeting by title" << endl;
        cout << "qt   - query meeting by time interval" << endl;
        cout << "dm   - delete meeting by title" << endl;
        cout << "da   - delete all meetings" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << endl;
        cout << "Agenda@" << m_userName << " : #";
    }

    /**
     * list all meetings from storage
     */
    void AgendaUI::listAllMeetings(void) {
        cout << endl;
        cout << "[list all meetings]" << endl;
        cout << endl;
        cout << "[title]" << "                  " << "[sponsor]" << "                " << "[start time]" << "             " << "[end time]" << "               " << "[participators]" << endl;
        list<Meeting> match = m_agendaService.listAllMeetings(m_userName);
        for (auto it = match.begin(); it != match.end(); ++it) {
            string sta = Date::dateToString((*it).getStartDate());
            string end = Date::dateToString((*it).getEndDate());
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << (*it).getTitle();
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << (*it).getSponsor();
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << sta;
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << end;
            for (int i = 0; i < (*it).getParticipator().size(); i++) {
                cout << (*it).getParticipator()[i] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "--------------------------------Agenda----------------------------------" << endl;
        cout << "Action :" << endl;
        cout << "o    - log out agenda" << endl;
        cout << "dc   - delete agenda account" << endl;
        cout << "lu   - list all agenda user" << endl;
        cout << "cm   - create a meeting" << endl;
        cout << "la   - list all meetings" << endl;
        cout << "las  - list all sponsor meetings" << endl;
        cout << "lap  - list all participate meetings" << endl;
        cout << "qm   - query meeting by title" << endl;
        cout << "qt   - query meeting by time interval" << endl;
        cout << "dm   - delete meeting by title" << endl;
        cout << "da   - delete all meetings" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << endl;
        cout << "Agenda@" << m_userName << " : #";
    }

    /**
     * list all meetings that this user sponsored
     */
    void AgendaUI::listAllSponsorMeetings(void) {
        cout << endl;
        cout << "[list all sponsor meetings]" << endl;
        cout << endl;
        cout << "[title]" << "                  " << "[sponsor]" << "                " << "[start time]" << "             " << "[end time]" << "               " << "[participators]" << endl;
        list<Meeting> match = m_agendaService.listAllSponsorMeetings(m_userName);
        for (auto it = match.begin(); it != match.end(); ++it) {
            string sta = Date::dateToString((*it).getStartDate());
            string end = Date::dateToString((*it).getEndDate());
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << (*it).getTitle();
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << (*it).getSponsor();
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << sta;
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << end;
            for (int i = 0; i < (*it).getParticipator().size(); i++) {
                cout << (*it).getParticipator()[i] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "--------------------------------Agenda----------------------------------" << endl;
        cout << "Action :" << endl;
        cout << "o    - log out agenda" << endl;
        cout << "dc   - delete agenda account" << endl;
        cout << "lu   - list all agenda user" << endl;
        cout << "cm   - create a meeting" << endl;
        cout << "la   - list all meetings" << endl;
        cout << "las  - list all sponsor meetings" << endl;
        cout << "lap  - list all participate meetings" << endl;
        cout << "qm   - query meeting by title" << endl;
        cout << "qt   - query meeting by time interval" << endl;
        cout << "dm   - delete meeting by title" << endl;
        cout << "da   - delete all meetings" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << endl;
        cout << "Agenda@" << m_userName << " : #";
    }

    /**
     * list all meetings that this user take part in
     */
    void AgendaUI::listAllParticipateMeetings(void) {
        cout << endl;
        cout << "[list all participate meetings]" << endl;
        cout << endl;
        cout << "[title]" << "                  " << "[sponsor]" << "                " << "[start time]" << "             " << "[end time]" << "               " << "[participators]" << endl;
        list<Meeting> match = m_agendaService.listAllParticipateMeetings(m_userName);
        for (auto it = match.begin(); it != match.end(); ++it) {
            string sta = Date::dateToString((*it).getStartDate());
            string end = Date::dateToString((*it).getEndDate());
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << (*it).getTitle();
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << (*it).getSponsor();
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << sta;
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << end;
            for (int i = 0; i < (*it).getParticipator().size(); i++) {
                cout << (*it).getParticipator()[i] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "--------------------------------Agenda----------------------------------" << endl;
        cout << "Action :" << endl;
        cout << "o    - log out agenda" << endl;
        cout << "dc   - delete agenda account" << endl;
        cout << "lu   - list all agenda user" << endl;
        cout << "cm   - create a meeting" << endl;
        cout << "la   - list all meetings" << endl;
        cout << "las  - list all sponsor meetings" << endl;
        cout << "lap  - list all participate meetings" << endl;
        cout << "qm   - query meeting by title" << endl;
        cout << "qt   - query meeting by time interval" << endl;
        cout << "dm   - delete meeting by title" << endl;
        cout << "da   - delete all meetings" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << endl;
        cout << "Agenda@" << m_userName << " : #";
    }

    /**
     * search meetings by title from storage
     */
    void AgendaUI::queryMeetingByTitle(void) {
        cout << endl;
        cout << "[query meeting] [title]" << endl;
        cout << "[query meeting] ";
        string tit;
        cin >> tit;
        cout << "[title]" << "                  " << "[sponsor]" << "                " << "[start time]" << "             " << "[end time]" << "               " << "[participators]" << endl;
        list<Meeting> match = m_agendaService.meetingQuery(m_userName, tit);
        for (auto it = match.begin(); it != match.end(); ++it) {
            string sta = Date::dateToString((*it).getStartDate());
            string end = Date::dateToString((*it).getEndDate());
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << (*it).getTitle();
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << (*it).getSponsor();
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << sta;
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << end;
            for (int i = 0; i < (*it).getParticipator().size(); i++) {
                cout << (*it).getParticipator()[i] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "--------------------------------Agenda----------------------------------" << endl;
        cout << "Action :" << endl;
        cout << "o    - log out agenda" << endl;
        cout << "dc   - delete agenda account" << endl;
        cout << "lu   - list all agenda user" << endl;
        cout << "cm   - create a meeting" << endl;
        cout << "la   - list all meetings" << endl;
        cout << "las  - list all sponsor meetings" << endl;
        cout << "lap  - list all participate meetings" << endl;
        cout << "qm   - query meeting by title" << endl;
        cout << "qt   - query meeting by time interval" << endl;
        cout << "dm   - delete meeting by title" << endl;
        cout << "da   - delete all meetings" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << endl;
        cout << "Agenda@" << m_userName << " : #";
    }

    /**
     * search meetings by timeinterval from storage
     */
    void AgendaUI::queryMeetingByTimeInterval(void) {
        cout << endl;
        cout << "[query meeting] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
        cout << "[query meeting] ";
        string sta, end;
        cin >> sta >> end;
        cout << "[title]" << "                  " << "[sponsor]" << "                " << "[start time]" << "             " << "[end time]" << "               " << "[participators]" << endl;
        list<Meeting> match = m_agendaService.meetingQuery(m_userName, sta, end);
        for (auto it = match.begin(); it != match.end(); ++it) {
            string sta = Date::dateToString((*it).getStartDate());
            string end = Date::dateToString((*it).getEndDate());
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << (*it).getTitle();
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << (*it).getSponsor();
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << sta;
            cout << setw(25);
            cout << setiosflags(ios::left);
            cout << end;
            for (int i = 0; i < (*it).getParticipator().size(); i++) {
                cout << (*it).getParticipator()[i] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "--------------------------------Agenda----------------------------------" << endl;
        cout << "Action :" << endl;
        cout << "o    - log out agenda" << endl;
        cout << "dc   - delete agenda account" << endl;
        cout << "lu   - list all agenda user" << endl;
        cout << "cm   - create a meeting" << endl;
        cout << "la   - list all meetings" << endl;
        cout << "las  - list all sponsor meetings" << endl;
        cout << "lap  - list all participate meetings" << endl;
        cout << "qm   - query meeting by title" << endl;
        cout << "qt   - query meeting by time interval" << endl;
        cout << "dm   - delete meeting by title" << endl;
        cout << "da   - delete all meetings" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << endl;
        cout << "Agenda@" << m_userName << " : #";
    }

    /**
     * delete meetings by title from storage
     */
    void AgendaUI::deleteMeetingByTitle(void) {
        cout << endl;
        cout << "[delete meeting] [title]" << endl;
        cout << "[delete meeting] ";
        string tit;
        cin >> tit;
        bool flag = m_agendaService.deleteMeeting(m_userName, tit);
        if (flag) {
            cout << "[delete meeting by title] succeed!" << endl;
        } else {
            cout << "[error] delete meeting fail!" << endl;
        }
        cout << endl;
        cout << "--------------------------------Agenda----------------------------------" << endl;
        cout << "Action :" << endl;
        cout << "o    - log out agenda" << endl;
        cout << "dc   - delete agenda account" << endl;
        cout << "lu   - list all agenda user" << endl;
        cout << "cm   - create a meeting" << endl;
        cout << "la   - list all meetings" << endl;
        cout << "las  - list all sponsor meetings" << endl;
        cout << "lap  - list all participate meetings" << endl;
        cout << "qm   - query meeting by title" << endl;
        cout << "qt   - query meeting by time interval" << endl;
        cout << "dm   - delete meeting by title" << endl;
        cout << "da   - delete all meetings" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << endl;
        cout << "Agenda@" << m_userName << " : #";
    }

    /**
     * delete all meetings that this user sponsored
     */
    void AgendaUI::deleteAllMeetings(void) {
        cout << endl;
        bool flag = m_agendaService.deleteAllMeetings(m_userName);
        if (flag) {
            cout << "[delete all meetings] succeed!" <<endl;
        } else {
            cout << "[error] fail!" << endl;
        }
        cout << endl;
        cout << "--------------------------------Agenda----------------------------------" << endl;
        cout << "Action :" << endl;
        cout << "o    - log out agenda" << endl;
        cout << "dc   - delete agenda account" << endl;
        cout << "lu   - list all agenda user" << endl;
        cout << "cm   - create a meeting" << endl;
        cout << "la   - list all meetings" << endl;
        cout << "las  - list all sponsor meetings" << endl;
        cout << "lap  - list all participate meetings" << endl;
        cout << "qm   - query meeting by title" << endl;
        cout << "qt   - query meeting by time interval" << endl;
        cout << "dm   - delete meeting by title" << endl;
        cout << "da   - delete all meetings" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << endl;
        cout << "Agenda@" << m_userName << " : #";
    }

    /**
     * show the meetings in the screen
     */
    void AgendaUI::printMeetings(std::list<Meeting> t_meetings) {
    }