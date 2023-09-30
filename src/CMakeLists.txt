add_executable(main 
    ./logic/chess/cpp/ChessMain.cpp 
    ./logic/chess/cpp/Chess.cpp 
    ./logic/chess/cpp/CommandHolder.cpp
    ./logic/chess/cpp/ConsolePresenter.cpp
    ./logic/chess/cpp/Desk.cpp
    ./logic/chess/cpp/DeskViewer.cpp
    ./logic/chess/cpp/SfmlControlManager.cpp

    ./logic/commands/cpp/CastlingCommand.cpp
    ./logic/commands/cpp/MoveCommand.cpp

    ./tests/cpp/CastlingCommandTest.cpp
    ./tests/cpp/DeskViewerTest.cpp
    ./tests/cpp/MoveCommandTest.cpp
)

target_include_directories(main PRIVATE ./logic/chess/hdr)
target_include_directories(main PRIVATE ./logic/commands/hdr)
target_include_directories(main PRIVATE ./logic/figures)
target_include_directories(main PRIVATE ./tests/hdr)

set(MY_SFML_PATH D:\\Development\\Libs\\SFML-2.6.0\\lib\\cmake\\SFML)
set(SFML_DIR ${MY_SFML_PATH})
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)
target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics)