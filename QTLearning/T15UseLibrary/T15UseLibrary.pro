SOURCES += \
    main.cpp

# 如果QT mingw版本，使用动态库方式和linux没区别（-L, -l)
# 如果QT VS版本。。。使用动态库方式和windows没区别
# 如果QT mingw版本，要调用VS写的动态库，使用一个工具，生成libXXXXX.a文件
LIBS += -LC:\StudyNote\QTLearning\build-T14Library-Desktop_Qt_5_9_0_MinGW_32bit-Debug\debug -lT14Library
