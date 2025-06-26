#include "../include/TaskManager.hpp"
#include <iostream>

TaskManager::TaskManager() : loggedInUser(nullptr) {}

TaskManager::TaskManager(const TaskManager& other) : loggedInUser(nullptr) {
	for (size_t i = 0; i < other.users.size(); ++i) {
		users.push_back(new User(*other.users[i]));
	}
}

TaskManager::TaskManager(TaskManager&& other) noexcept {
	users = std::move(other.users);
	loggedInUser = other.loggedInUser;
	other.users.clear();
	other.loggedInUser = nullptr;
}

TaskManager::~TaskManager() {
	for (size_t i = 0; i < users.size(); ++i) {
		delete users[i];
	}
	users.clear();
}

void TaskManager::registerUser(const std::string& username, const std::string& password) {
	for (size_t i = 0; i < users.size(); ++i) {
		if (users[i]->getName() == username) {
			std::cout << "Username already exists!\n";
			return;
		}
	}
	users.push_back(new User(username, password));
	std::cout << "User registered successfully!\n";
}

bool TaskManager::login(const std::string& username, const std::string& password) {
	for (size_t i = 0; i < users.size(); ++i) {
		if (users[i]->getName() == username) {
			if (users[i]->login(password)) {
				loggedInUser = users[i];
				return true;
			}
			break;
		}
	}
	return false;
}

void TaskManager::logout() {
	if (loggedInUser) {
		loggedInUser->logout();
		loggedInUser = nullptr;
	}
}

void TaskManager::addTask(const Task& task) {
	if (loggedInUser) {
		loggedInUser->addTask(new Task(task));
	} else {
		std::cout << "No user logged in!\n";
	}
}

void TaskManager::deleteTask(const std::string& title) {
	if (loggedInUser) {
		if (!loggedInUser->deleteTask(title)) {
			std::cout << "Task not found!\n";
		}
	} else {
		std::cout << "No user logged in!\n";
	}
}

void TaskManager::editTask(const std::string& title, const Task& updatedTask) {
	if (loggedInUser) {
		if (!loggedInUser->editTask(title, updatedTask)) {
			std::cout << "Task not found!\n";
		}
	} else {
		std::cout << "No user logged in!\n";
	}
}

void TaskManager::displayTasks() const {
	if (loggedInUser) {
		loggedInUser->listTasks();
	} else {
		std::cout << "No user logged in!\n";
	}
}
