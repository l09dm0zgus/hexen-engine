//
// Created by cx9ps3 on 24.05.2023.
//
#include "application/Application.h"

#include <core/threading/TaskManager.h>

void testTask1(int* x)
{
   std::cout << "Task 1 with " << *x << std::endl;
    (*x)++;
}

struct TestTask2
{
    void execute(int* x)
    {
        std::cout << "TestTask2::execute with " << *x << std::endl;
        (*x)++;
    }

    void operator()(int* x)
    {
        std::cout << "TestTask2::operator() with " << *x << std::endl;
        (*x)++;
    }
};

static core::i32 i{0};

int main()
{
    //edit::Application app;
    //app.run();

    core::threading::TaskManager taskManager;

    if(taskManager.initialize() != core::threading::TaskManager::ReturnCode::Succes)
    {
        return -1;
    }


    std::shared_ptr<core::threading::TaskCounter> counter = std::make_shared<core::threading::TaskCounter>(&taskManager);

    taskManager.scheduleTask(core::threading::TaskPriority::Normal,counter,testTask1,&i);
    taskManager.scheduleTask(core::threading::TaskPriority::Normal,counter,testTask1,&i);
    taskManager.scheduleTask(core::threading::TaskPriority::Normal,counter,testTask1,&i);
    taskManager.scheduleTask(core::threading::TaskPriority::Normal,counter,testTask1,&i);
    taskManager.scheduleTask(core::threading::TaskPriority::Normal,counter,testTask1,&i);

    taskManager.waitForCounter(counter);

    return 0;
}