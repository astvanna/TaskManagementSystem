#ifndef TASK_HPP
#define TASK_HPP

#include <string>

enum Priority {LOW = 1, MEDIUM= 2, HIGH = 3};

class Task {
private:
	std::string m_title;
	std::string m_description;
	std::string m_deadline;
	std::string m_category;
	Priority m_priority;
	bool m_completed;

public:
	Task();
	Task(const std::string& title, const std::string& description, const std::string& deadline, const std::string& category, int priority, bool completed = false);
	Task(const Task& other);
	Task(Task&& other) noexcept;
	~Task();
	std::string getTitle() const;
	std::string getDescription() const;
	std::string getDeadline() const;
	std::string getCategory() const;
	int getPriority() const;
	bool getCompleted() const;
	void setTitle(const std::string& title);
	void setDescription(const std::string& description);
	void setDeadline(const std::string& deadline);
	void setCategory(const std::string& category);
	void setPriority(int priority);
	void setCompleted(bool completed);
	void markCompleted();
	void editTask(const std::string& newTitle, const std::string& newDescription, const std::string& newDeadline, const std::string& newCategory, int newPriority);
	void displayTask() const;

	Task& operator=(const Task& other);
	Task& operator=(Task&& other) noexcept;

};

#endif /* TASK_HPP */
