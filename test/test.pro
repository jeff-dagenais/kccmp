TARGET  = test
SOURCES = test.cpp ../config_value.cpp
CONFIG += warn_on debug
OBJECTS_DIR = obj

LIBS += -lboost_unit_test_framework
#MOC_DIR =
