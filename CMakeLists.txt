# Project name
set(PROJECT_NAME PolarisationSimulator)
project( ${PROJECT_NAME} )


cmake_minimum_required(VERSION 3.1)

# Build type
set(CMAKE_BUILD_TYPE Debug CACHE TYPE STRING FORCE )


#QT
find_package(Qt5 COMPONENTS  Core Network Widgets Gui Charts REQUIRED)



# Include paths
include_directories (
        ${QT_INCLUDES}

)

# Use all .cpp and .h files
FILE ( GLOB SRC_FILES "*.cpp")
FILE ( GLOB HEADER_FILES "*.h")

#Add all .ui files
FILE ( GLOB UI_FILES "*.ui")




ADD_DEFINITIONS (
                ${QT_DEFINITIONS}
                )


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


#Create the executable
ADD_EXECUTABLE ( ${PROJECT_NAME}
        ${SRC_FILES}
        ${HEADER_FILES}
        ${UI_FILES}
)

#Linker settings
TARGET_LINK_LIBRARIES ( ${PROJECT_NAME}
     
        ${QT_LIBRARIES}                
                ${Qt5Widgets_LIBRARIES}
                ${Qt5Network_LIBRARIES}
                ${Qt5Core_LIBRARIES}
                ${Qt5Gui_LIBRARIES}
                ${Qt5Charts_LIBRARIES}
                
)




