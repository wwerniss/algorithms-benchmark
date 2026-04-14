# Find Qt5 or Qt6
find_package(Qt5 COMPONENTS Core Gui Widgets Multimedia REQUIRED)

# Need AUTOMOC, AUTOUIC, AUTORCC for Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(AlgorithmsApp
    src/main.cpp
    include/MainWindow.h
    src/MainWindow.cpp
    include/VisualizationWidget.h
    src/VisualizationWidget.cpp
    include/SortingWindow.h
    src/SortingWindow.cpp
    include/AudioSynthesizer.h
    src/AudioSynthesizer.cpp
    include/GraphVisualizationWidget.h
    src/GraphVisualizationWidget.cpp
    include/GraphWindow.h
    src/GraphWindow.cpp
    include/TreeVisualizationWidget.h
    src/TreeVisualizationWidget.cpp
    include/TreeWindow.h
    src/TreeWindow.cpp
    include/HistoryWindow.h
    src/HistoryWindow.cpp
)

target_link_libraries(AlgorithmsApp PRIVATE
    AlgorithmsCore
    Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia
)

target_include_directories(AlgorithmsApp PRIVATE include)
