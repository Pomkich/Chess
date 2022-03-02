// ChessMain.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "MoveCommandTest.h"
#include "CastlingCommandTest.h"
#include "DeskViewerTest.h"
#include "Chess.h"
#include "SfmlControlManager.h"
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

using namespace std;

mutex mut;
condition_variable running_cv;
bool running_bool;

int main()
{
    //MoveCommandTest test1;
    //CastlingCommandTest test2;
    //DeskViewerTest test3;
    running_bool = false;
    shared_ptr<SfmlControlManager> manager = make_shared<SfmlControlManager>();
    manager->InitPointers();
    manager->InitResources();
    thread run(&SfmlControlManager::Run, manager);
    run.detach();

    running_bool = true;
    
    unique_lock<mutex> lock(mut);
    running_cv.wait(lock, [] {return !running_bool; });

    return 0;
}