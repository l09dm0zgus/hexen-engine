//
// Created by cx9ps3 on 29.07.2023.
//

#pragma once
#include <memory>
#include "../core/threading/Threading.h"

namespace sys
{
    class TaskSystem
    {
    private:
        static core::threading::TaskScheduler scheduler;
        static core::threading::TaskCounter counter;
    public:
        static void initialize();
        template<class T,typename Ret ,typename ...Args> static void addTask(core::threading::TaskPriority priority,T* object,Ret (T::*method)(Args...) , Args... args);
        template<typename Ret ,typename ...Args> static void addTask(core::threading::TaskPriority priority , Ret (*function)(Args...) , Args... args);
        template<class T ,typename ...Args> static void addTask(core::threading::TaskPriority priority ,T* newFunctor, Args... args);
        static void addTasks(core::threading::TaskPriority priority,const std::array<core::threading::Task,400> &tasks);
        static void waitForCounter(core::i32 value = 0);
    };

    template<class T, typename... Args>
    void TaskSystem::addTask(core::threading::TaskPriority priority, T *newFunctor, Args... args)
    {
        core::threading::Task task;
        task.bind(newFunctor,args...);
        scheduler.addTask(task,priority,&counter);
    }

    template<typename Ret, typename... Args>
    void TaskSystem::addTask(core::threading::TaskPriority priority,Ret (*function)(Args...), Args... args)
    {
        core::threading::Task task;
        task.bind(function,args...);
        scheduler.addTask(task,priority,&counter);
    }

    template<class T, typename Ret, typename... Args>
    void TaskSystem::addTask(core::threading::TaskPriority priority,T *object, Ret (T::*method)(Args...), Args... args)
    {
        core::threading::Task task;
        task.bind(object,method,args...);
        scheduler.addTask(task,priority,&counter);
    }
}


