qt_add_library(MyLib STATIC

    transmission.h transmission.cpp
    channelcoder.h channelcoder.cpp
    channel.h channel.cpp
    codeword.h codeword.cpp

    #swarqtransmission.h swarqtransmission.cpp
    bscchannel.h bscchannel.cpp

    coder.h coder.cpp
    paritycoder.h paritycoder.cpp
    filehandler.h filehandler.cpp
    threadmanager.h threadmanager.cpp
    transmissionstruct.h transmissionstruct.cpp
    simulation.h simulation.cpp
    simulationdata.h simulationdata.cpp
    bacchannel.h bacchannel.cpp

)
target_link_libraries(MyLib PRIVATE Qt6::Core)

target_include_directories(MyLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
