TEMPLATE = app

unix:!mac{
    LIBS += -lpthread
}


HEADERS += \
    exception/t_exception.h \
    resource/t_thread.h \
    resource/t_resalloc.h

SOURCES += \
    main.cpp \
    resource/t_thread.cpp \
    resource/t_resalloc.cpp \
    exception/t_exception.cpp
