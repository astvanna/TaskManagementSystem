#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
#include "Task.hpp"

class User {
private:
	std::string m_username; // Username
	std::string m_password;
	std::vector<Task*> m_tasks; // List of owned tasks
	bool m_is_logged; // Tracks login status

public:
	// Constructors and  Destructor
	User(const std::string& username, const std::string& password); //Constructor (new user initialization)
	User(const User& other); // Copy constructor (deep copy of task list)
	User(User&& other) noexcept; // Move constructor (transfer ownership of tasks)
	~User(); // Destructor

	// Assignment operators
	User& operator=(const User& other);
	User& operator=(User&& other) noexcept;

	// Boolean conversion operator
	explicit operator bool() const;

	// Task management functions
	void addTask(Task* task);
	bool deleteTask(const std::string& taskId);
	bool editTask(const std::string& taskId, const Task& updatedTask);
	void listTasks() const;
	Task* searchTask(const std::string& titleOrId) const;

	// Login and Logout
	bool login(const std::string& password);
	void logout();

	// Getters
	unsigned int getId() const;
	const std::string& getName() const;
	const std::vector<Task*>& getTasks() const;
	bool isLoggedIn() const;

	// Stream operator overloading
	friend std::ostream& operator<<(std::ostream& os, const User& user);
	friend std::istream& operator>>(std::istream& is, User& user);
};

#endif /* USER_HPP */
