#include "gtest/gtest.h"
#include "../include/User.hpp"
#include "../include/Task.hpp"

class UserTest : public ::testing::Test {
protected:
	User user{"testuser", "notapassword"};
	Task* task = new Task{"Task1", "Description", "01.01.2001", "Work", 2};
};

TEST_F(UserTest, ConstructorAndGetters) {
	EXPECT_EQ(user.getName(), "testuser");
	EXPECT_FALSE(user.isLoggedIn());
	EXPECT_TRUE(user.getTasks().empty());
}

TEST_F(UserTest, LoginLogoutFunctions) {
	EXPECT_TRUE(user.login("notapassword"));
	EXPECT_TRUE(user.isLoggedIn());
	
	user.logout();
	EXPECT_FALSE(user.isLoggedIn());
	
	EXPECT_FALSE(user.login("wrongpass"));
}

TEST_F(UserTest, TaskManagementFunctions) {
	user.addTask(task);
	ASSERT_EQ(user.getTasks().size(), 1);
	EXPECT_EQ(user.getTasks()[0]->getTitle(), "Task1");
	user.addTask(task);
	Task updated{"Task1", "New Desc", "01.01.2025", "Picsart", 3};
	EXPECT_TRUE(user.editTask("Task1", updated));
	EXPECT_EQ(user.getTasks()[0]->getDescription(), "New Desc");
	Task* found = user.searchTask("Task1");
	ASSERT_NE(found, nullptr);
	EXPECT_EQ(found->getCategory(), "Picsart");
}

TEST_F(UserTest, ListTasksOutput) {
	user.addTask(task);
	testing::internal::CaptureStdout();
	user.listTasks();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("Task1"), std::string::npos);
}

TEST_F(UserTest, InvalidTaskOperations) {
	EXPECT_FALSE(user.editTask("Nonexistent", *task));
	EXPECT_EQ(user.searchTask("Nonexistent"), nullptr);
}
