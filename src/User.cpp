#include "../include/User.hpp"
#include <iostream>

User::User(const std::string& username, const std::string& password)
	: m_username(username), m_password(password), m_is_logged(false) {}

User::User(const User& other)
	: m_username(other.m_username), m_password(other.m_password), m_is_logged(false) {
	for (size_t i = 0; i < other.m_tasks.size(); ++i) {
		m_tasks.push_back(new Task(*other.m_tasks[i]));
	}
}

User::User(User&& other) noexcept
	: m_username(std::move(other.m_username)), m_password(std::move(other.m_password)), m_tasks(std::move(other.m_tasks)), m_is_logged(other.m_is_logged) {
	other.m_tasks.clear();
	other.m_is_logged = false;
}

User::~User() {
	for (size_t i = 0; i < m_tasks.size(); ++i) {
		delete m_tasks[i];
	}
	m_tasks.clear();
}

User& User::operator=(const User& other) {
	if (this != &other) {
		m_username = other.m_username;
		m_password = other.m_password;
		m_is_logged = false;

		for (size_t i = 0; i < m_tasks.size(); ++i) {
			delete m_tasks[i];
		}
		m_tasks.clear();

	}
	return *this;
}

User& User::operator=(User&& other) noexcept {
	if (this != &other) {
		for (size_t i = 0; i < m_tasks.size(); ++i) {
			delete m_tasks[i];
		}

		m_username = std::move(other.m_username);
		m_password = std::move(other.m_password);
		m_tasks = std::move(other.m_tasks);
		m_is_logged = other.m_is_logged;

		other.m_tasks.clear();
		other.m_is_logged = false;
	}
	return *this;
}

User::operator bool() const {
	return !m_username.empty() && !m_password.empty();
}

void User::addTask(Task* task) {
	m_tasks.push_back(task);
}

bool User::deleteTask(const std::string& taskId) {
	for (size_t i = 0; i < m_tasks.size(); ++i) {
		if (m_tasks[i]->getTitle() == taskId) {
			delete m_tasks[i];
			m_tasks.erase(m_tasks.begin() + i);
			return true;
		}
	}
	return false;
}

bool User::editTask(const std::string& taskId, const Task& updatedTask) {
	for (size_t i = 0; i < m_tasks.size(); ++i) {
		if (m_tasks[i]->getTitle() == taskId) {
			*m_tasks[i] = updatedTask;
			return true;
		}
	}
	return false;
}

void User::listTasks() const {
	for (size_t i = 0; i < m_tasks.size(); ++i) {
		m_tasks[i]->displayTask();
	}
}

Task* User::searchTask(const std::string& titleOrId) const {
	for (size_t i = 0; i < m_tasks.size(); ++i) {
		if (m_tasks[i]->getTitle() == titleOrId) {
			return m_tasks[i];
		}
	}
	return nullptr;
}

bool User::login(const std::string& password) {
	m_is_logged = (m_password == password);
	return m_is_logged;
}

void User::logout() {
	m_is_logged = false;
}

const std::string& User::getName() const {
	return m_username;
}

const std::vector<Task*>& User::getTasks() const {
	return m_tasks;
}

bool User::isLoggedIn() const {
	return m_is_logged;
}

std::ostream& operator<<(std::ostream& os, const User& user) {
	os << "Username: " << user.m_username << "\n" << "Task Count: " << user.m_tasks.size() << "\n" << "Logged In: " << (user.m_is_logged ? "Yes" : "No");
	return os;
}

std::istream& operator>>(std::istream& is, User& user) {
	is >> user.m_username >> user.m_password;
	return is;
}
