#include "gtest/gtest.h"
#include "../include/TaskManager.hpp"

class TaskManagerTest : public ::testing::Test {
protected:
	TaskManager tm;
	Task task{"Task1", "Desc", "2023-12-31", "Work", 2};
	
	void SetUp() override {
		tm.registerUser("admin", "admin123");
		tm.login("admin", "admin123");
	}
};

TEST_F(TaskManagerTest, UserRegistration) {
	EXPECT_TRUE(tm.login("admin", "admin123"));
	testing::internal::CaptureStdout();
	tm.registerUser("admin", "newpass");
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("already exists"), std::string::npos);
}

TEST_F(TaskManagerTest, AuthenticationFunctions) {
	EXPECT_TRUE(tm.login("admin", "admin123"));
	tm.logout();
	EXPECT_FALSE(tm.login("admin", "wrongpass"));
}

TEST_F(TaskManagerTest, TaskOperations) {
	tm.addTask(task);
	testing::internal::CaptureStdout();
	tm.displayTasks();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("Task1"), std::string::npos);
	Task updated{"Task1", "New Desc", "2024-01-01", "Home", 3};
	tm.editTask("Task1", updated);
	testing::internal::CaptureStdout();
	tm.displayTasks();
	output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("New Desc"), std::string::npos);
	tm.deleteTask("Task1");
	testing::internal::CaptureStdout();
	tm.displayTasks();
	output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output.find("Task1"), std::string::npos);
}

TEST_F(TaskManagerTest, UnauthorizedOperations) {
	tm.logout();
	
	testing::internal::CaptureStdout();
	tm.addTask(task);
	tm.deleteTask("Task1");
	tm.editTask("Task1", task);
	tm.displayTasks();
	std::string output = testing::internal::GetCapturedStdout();
	size_t pos = output.find("No user logged in");
	EXPECT_NE(pos, std::string::npos);
	pos = output.find("No user logged in", pos + 1);
	EXPECT_NE(pos, std::string::npos);
}
