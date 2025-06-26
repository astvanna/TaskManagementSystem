#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP

#include "User.hpp"
#include "Task.hpp"
#include <vector>
#include <string>

class TaskManager {
	private:
		std::vector<User*> users; //List of all users
		User* loggedInUser; //The currently logged-in user
	public:
		TaskManager(); //Initializes the system
		TaskManager(const TaskManager& other); //Copy Constructor (deep copy of user list)
		TaskManager(TaskManager&& other) noexcept; //Move Constructor (transfer ownership)
		~TaskManager(); //Destructor (deallocate users)

		void registerUser(const std::string& username, const std::string& password); //Registers a new user
		bool login(const std::string& username, const std::string& password); //Logs in a user
		void logout(); //Logs out the current user
		
		void addTask(const Task& task); //Adds a task for the logged-in user.
		void deleteTask(const std::string& title); //Deletes a task for the logged-in user.
		void editTask(const std::string& title, const Task& updatedTask); //Modifies a task for the logged-in user.
		void displayTasks() const; //Displays all tasks for the logged-in user
};

#endif /*TASKMANAGER_HPP*/
