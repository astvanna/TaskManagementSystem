#include "../include/Task.hpp"
#include <iostream>

Task::Task()
	: m_title(""), m_description(""), m_deadline(""), m_category(""), m_priority(Priority::LOW), m_completed(false) {}

Task::Task(const std::string& title, const std::string& description, const std::string& deadline, const std::string& category, int priority, bool completed)
	: m_title(title), m_description(description), m_deadline(deadline), m_category(category), m_completed(completed)
{
	switch(priority) {
	case 1:
		m_priority = Priority::LOW;
		break;
	case 2:
		m_priority = Priority::MEDIUM;
		break;
	case 3:
		m_priority = Priority::HIGH;
		break;
	default:
		m_priority = Priority::LOW;
	}
}

Task::Task(const Task& other)
	: m_title(other.m_title), m_description(other.m_description), m_deadline(other.m_deadline), m_category(other.m_category), m_priority(other.m_priority), m_completed(other.m_completed) {}

Task::Task(Task&& other) noexcept
	: m_title(std::move(other.m_title)), m_description(std::move(other.m_description)), m_deadline(std::move(other.m_deadline)), m_category(std::move(other.m_category)), m_priority(other.m_priority), m_completed(other.m_completed) {
	std::cout << "Transferred task ownership" << std::endl;
	other = Task();
}

Task::~Task() {}

std::string Task::getTitle() const {
	return m_title;
}

std::string Task::getDescription() const {
	return m_description;
}

std::string Task::getDeadline() const {
	return m_deadline;
}

std::string Task::getCategory() const {
	return m_category;
}

int Task::getPriority() const {
	return static_cast<int>(m_priority);
}

bool Task::getCompleted() const {
	return m_completed;
}

void Task::setTitle(const std::string& title) {
	m_title = title;
}

void Task::setDescription(const std::string& description) {
	m_description = description;
}

void Task::setDeadline(const std::string& deadline) {
	m_deadline = deadline;
}

void Task::setCategory(const std::string& category) {
	m_category = category;
}

void Task::setPriority(int priority) {
	switch(priority) {
	case 1:
		m_priority = Priority::LOW;
		break;
	case 2:
		m_priority = Priority::MEDIUM;
		break;
	case 3:
		m_priority = Priority::HIGH;
		break;
	default:
		m_priority = Priority::LOW;
	}
}

void Task::setCompleted(bool completed) {
	m_completed = completed;
}

void Task::markCompleted() {
	m_completed = true;
}

void Task::editTask(const std::string& newTitle, const std::string& newDescription, const std::string& newDeadline, const std::string& newCategory, int newPriority)
{
	m_title = newTitle;
	m_description = newDescription;
	m_deadline = newDeadline;
	m_category = newCategory;
	setPriority(newPriority);
}

void Task::displayTask() const {
	std::cout << "Title: " << m_title << std::endl;
	std::cout << "Description: " << m_description << std::endl;
	std::cout << "Deadline: " << m_deadline << std::endl;
	std::cout << "Category: " << m_category << std::endl;
	std::cout << "Priority: ";
	switch (m_priority)
	{
	case Priority::LOW:
		std::cout << "Low";
		break;
	case Priority::MEDIUM:
		std::cout << "Medium";
		break;
	case Priority::HIGH:
		std::cout << "High";
		break;
	default:
		std::cout << "Unknown";
	}
	std::cout << std::endl << "Status:\t";
	if(m_completed) {
		std::cout << "Completed\n" << std::endl;
	} else {
		std::cout << "Pending\n" << std::endl;
	}
}

Task& Task::operator=(const Task& other) {
	if (this != &other) {
		m_title = other.m_title;
		m_description = other.m_description;
		m_deadline = other.m_deadline;
		m_category = other.m_category;
		m_priority = other.m_priority;
		m_completed = other.m_completed;
	}
	return *this;
}

Task& Task::operator=(Task&& other) noexcept {
	if (this != &other) {
		m_title = std::move(other.m_title);
		m_description = std::move(other.m_description);
		m_deadline = std::move(other.m_deadline);
		m_category = std::move(other.m_category);
		m_priority = other.m_priority;
		m_completed = other.m_completed;

		other.m_priority = Priority::LOW;
		other.m_completed = false;
	}
	return *this;
}
