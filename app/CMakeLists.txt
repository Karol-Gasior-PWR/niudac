qt_add_resources(RESOURCES_RCC ${RESOURCES})

qt_add_executable(${PROJECT_NAME}
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    addsimulationdialog.h addsimulationdialog.cpp addsimulationdialog.ui
    chartwindow.h chartwindow.cpp chartwindow.ui
    dialogsimulationinfo.h dialogsimulationinfo.cpp dialogsimulationinfo.ui
    calculationthread.h calculationthread.cpp
    csvexporter.h csvexporter.cpp


)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Charts
        MyLib
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#---------------------------------------------------------

#------------------------------------------------------------------------------

