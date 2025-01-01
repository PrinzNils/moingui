cmake_minimum_required(VERSION 3.10)
project(moingui)

# Ignoriere nicht benötigte Catkin-Variablen
set(CATKIN_INSTALL_INTO_PREFIX_ROOT OFF CACHE BOOL "" FORCE)
set(CATKIN_SYMLINK_INSTALL OFF CACHE BOOL "" FORCE)


# Automatisches Ausführen von MOC für Header mit Q_OBJECT
set(CMAKE_AUTOMOC ON)

# Hinzufügen von Headern und Quellen
set(SRC_FILES
    src/main.cpp
    src/VideoStreamNode.cpp
    src/ROSImageProvider.cpp
    main.qml
)

set(HDR_FILES
    include/VideoStreamNode.hpp
    include/ROSImageProvider.hpp
)

set(QT_RESOURCES qml.qrc)



# Finde benötigte Pakete
find_package(ament_cmake REQUIRED)
find_package(ament_index_cpp REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Quick Gui QuickControls2)
find_package(cv_bridge REQUIRED)

# Füge das Include-Verzeichnis hinzu
include_directories(include
    ${cv_bridge_INCLUDE_DIRS}
)




# ROS 2 und Qt-Bibliotheken einbinden
add_executable(moingui ${SRC_FILES} ${HDR_FILES} )

# Verknüpfe die benötigten Bibliotheken
ament_target_dependencies(${PROJECT_NAME}
    rclcpp
    sensor_msgs
    OpenCV
    cv_bridge
)

target_link_libraries(${PROJECT_NAME} 
    Qt5::Core 
    Qt5::Quick 
    Qt5::Gui 
    Qt5::QuickControls2
    rclcpp::rclcpp 
    ${OpenCV_LIBS}
    ${cv_bridge_LIBRARIES})

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)


# Installationsschritte
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(FILES package.xml
    DESTINATION share/${PROJECT_NAME}
)


install(DIRECTORY include
    DESTINATION include/${PROJECT_NAME}
)


# Ament-Paket exportieren
ament_package()

