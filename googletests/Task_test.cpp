#include "gtest/gtest.h"
#include "../include/Task.hpp"

class TaskTest : public ::testing::Test {
protected:
	Task task;
	Task fullTask{"Birth", "Being born", "04.12.2006", "Life", 3, true};
};

TEST_F(TaskTest, DefaultConstructor) {
	EXPECT_EQ(task.getTitle(), "");
	EXPECT_EQ(task.getDescription(), "");
	EXPECT_EQ(task.getDeadline(), "");
	EXPECT_EQ(task.getCategory(), "");
	EXPECT_EQ(task.getPriority(), 1);
	EXPECT_FALSE(task.getCompleted());
}

TEST_F(TaskTest, ParameterizedConstructor) {
	EXPECT_EQ(fullTask.getTitle(), "Birth");
	EXPECT_EQ(fullTask.getDescription(), "Being born");
	EXPECT_EQ(fullTask.getDeadline(), "04.12.2006");
	EXPECT_EQ(fullTask.getCategory(), "Life");
	EXPECT_EQ(fullTask.getPriority(), 3);
	EXPECT_TRUE(fullTask.getCompleted());
}

TEST_F(TaskTest, SettersAndGetters) {
	task.setTitle("New Title");
	task.setDescription("BLablaBlA");
	task.setDeadline("01.01.2025");
	task.setCategory("Secret");
	task.setPriority(3);
	task.setCompleted(true);

	EXPECT_EQ(task.getTitle(), "New Title");
	EXPECT_EQ(task.getDescription(), "BLablaBlA");
	EXPECT_EQ(task.getDeadline(), "01.01.2025");
	EXPECT_EQ(task.getCategory(), "Secret");
	EXPECT_EQ(task.getPriority(), 3);
	EXPECT_TRUE(task.getCompleted());
}

TEST_F(TaskTest, MarkCompletedFunction) {
	task.markCompleted();
	EXPECT_TRUE(task.getCompleted());
}

TEST_F(TaskTest, PriorityValidation) {
	task.setPriority(0);
	EXPECT_EQ(task.getPriority(), 1);

	task.setPriority(22);
	EXPECT_EQ(task.getPriority(), 3);
}

TEST_F(TaskTest, EditTaskFunction) {
	fullTask.editTask("Edited", "New Description", "26.06.2025", "Test", 1);
	EXPECT_EQ(fullTask.getTitle(), "Edited");
	EXPECT_EQ(fullTask.getDescription(), "New Description");
	EXPECT_EQ(fullTask.getDeadline(), "26.06.2025");
	EXPECT_EQ(fullTask.getCategory(), "Test");
	EXPECT_EQ(fullTask.getPriority(), 1);
}

TEST_F(TaskTest, DisplayTaskOutput) {
	testing::internal::CaptureStdout();
	fullTask.displayTask();
	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_NE(output.find("Birth"), std::string::npos);
	EXPECT_NE(output.find("Life"), std::string::npos);
	EXPECT_NE(output.find("High"), std::string::npos);
	EXPECT_NE(output.find("Completed"), std::string::npos);
}
