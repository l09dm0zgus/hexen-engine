//
// Created by cx9ps3 on 14.07.2023.
//

#include "Task.h"

void core::threading::TaskInfo::execute()
{
    if (!isNull())
    {
        getDelegate()->call();
    }

    if (counter)
    {
        counter->decrement();
    }
}
