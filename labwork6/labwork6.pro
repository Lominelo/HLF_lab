QT += core gui widgets printsupport
CONFIG += c++17
TARGET = labwork6
TEMPLATE = app
SOURCES += main.cpp spectrum_window.cpp fft_processor.cpp \
           ../labwork5/fourier_params.cpp ../labwork4/complex_array.cpp \
           qcustomplot.cpp
HEADERS += spectrum_window.h fft_processor.h \
           ../labwork5/fourier_params.h ../labwork4/array2d.h \
           ../labwork4/complex_array.h qcustomplot.h
FORMS += spectrum_window.ui
INCLUDEPATH += ..

INCLUDEPATH += $$PWD
LIBS += -L$$PWD -llibfftw3-3