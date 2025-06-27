#include "../include/TaskManager.hpp"
#include "gtest/gtest.h"

class TaskManagerTest : public ::testing::Test {
protected:
	TaskManager tm;
	Task testTask;
	const std::string username1 = "user1";
	const std::string username2 = "user2";
	const std::string password = "pass123";

	void SetUp() override {
		testTask = Task{"Main Task", "Task description", "15.07.2025", "Office", 2};
		tm.registerUser(username1, password);
		tm.registerUser(username2, password);
	}
};

TEST_F(TaskManagerTest, ConstructorDestructor) {
	TaskManager localTM;
	TaskManager copiedTM(tm);
	TaskManager movedTM(std::move(copiedTM));
}

TEST_F(TaskManagerTest, RegisterUser) {
	EXPECT_TRUE(tm.login(username1, password));
	tm.logout();
	testing::internal::CaptureStdout();
	tm.registerUser(username1, "newpass");
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("already exists"), std::string::npos);
}

TEST_F(TaskManagerTest, LoginLogout) {
	EXPECT_TRUE(tm.login(username1, password));
	EXPECT_FALSE(tm.login("nonexistent", password));
	EXPECT_FALSE(tm.login(username1, "wrongpass"));
	tm.logout();
	EXPECT_TRUE(tm.login(username1, password));
}

TEST_F(TaskManagerTest, AddTask) {
	tm.login(username1, password);
	tm.addTask(testTask);
	testing::internal::CaptureStdout();
	tm.displayTasks();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("Main Task"), std::string::npos);
}

TEST_F(TaskManagerTest, EditTask) {
	tm.login(username1, password);
	tm.addTask(testTask);
	Task updated{"Main Task", "Updated desc", "20.07.2025", "Home", 1};
	tm.editTask("Main Task", updated);
	testing::internal::CaptureStdout();
	tm.displayTasks();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("Updated desc"), std::string::npos);
}

TEST_F(TaskManagerTest, DeleteTask) {
	tm.login(username1, password);
	tm.addTask(testTask);
	tm.deleteTask("Main Task");
	testing::internal::CaptureStdout();
	tm.displayTasks();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output.find("Main Task"), std::string::npos);
}

TEST_F(TaskManagerTest, DisplayTasks) {
	tm.login(username1, password);
	tm.addTask(testTask);
	testing::internal::CaptureStdout();
	tm.displayTasks();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("Main Task"), std::string::npos);
	EXPECT_NE(output.find("15.07.2025"), std::string::npos);
}

TEST_F(TaskManagerTest, UserIsolation) {
	tm.login(username1, password);
	tm.addTask(testTask);
	tm.logout();
	
	tm.login(username2, password);
	testing::internal::CaptureStdout();
	tm.displayTasks();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output.find("Main Task"), std::string::npos);
}

TEST_F(TaskManagerTest, InvalidOperations) {
	testing::internal::CaptureStdout();
	tm.addTask(testTask);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("No user logged in"), std::string::npos);

	tm.login(username1, password);
	testing::internal::CaptureStdout();
	tm.editTask("Non-existent", testTask);
	output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("not found"), std::string::npos);

	testing::internal::CaptureStdout();
	tm.deleteTask("Non-existent");
	output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("not found"), std::string::npos);
}
