#include "stdafx.h"

int main()
{
    FRAMEWORK.Init(1366, 768, "Angry Bird Demo");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}