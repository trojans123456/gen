TEMPLATE = app

unix:!mac{
    LIBS += -lpthread
}


HEADERS += \
    exception/t_exception.h \
    resource/t_thread.h \
    resource/t_resalloc.h \
    event/t_event.h \
    #socket/t_socket.h

SOURCES += \
    main.cpp \
    resource/t_thread.cpp \
    resource/t_resalloc.cpp \
    exception/t_exception.cpp \
    event/t_event.cpp \
   # socket/t_socket.cpp
