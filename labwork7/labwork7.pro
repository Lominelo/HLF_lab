QT += core gui widgets printsupport
CONFIG += c++17
TARGET = labwork7
TEMPLATE = app
SOURCES += main.cpp viewer_window.cpp optimized_fft.cpp qcustomplot.cpp \
           ../labwork5/fourier_params.cpp ../labwork4/complex_array.cpp
HEADERS += viewer_window.h optimized_fft.h \
           ../labwork5/fourier_params.h \
           ../labwork4/array2d.h ../labwork4/complex_array.h qcustomplot.h
FORMS += viewer_window.ui
INCLUDEPATH += ..

INCLUDEPATH += $$PWD
LIBS += -L$$PWD -llibfftw3-3
