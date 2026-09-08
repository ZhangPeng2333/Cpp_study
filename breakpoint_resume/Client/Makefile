# C++ 封装版客户端

TARGET   = bin/app
CXX      = g++
CXXFLAGS = -g -Wall -O0 -pthread -I$(INCDIR) -I../common/inc
LDFLAGS  = -pthread -lcrypto

SRCDIR   = src
OBJDIR   = obj
INCDIR   = inc
BINDIR   = bin

LOCAL_SRC  = $(wildcard $(SRCDIR)/*.cpp)
LOCAL_OBJ  = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(LOCAL_SRC))
COMMON_SRC = $(wildcard ../common/src/*.cpp)
COMMON_OBJ = $(patsubst ../common/src/%.cpp, $(OBJDIR)/%.o, $(COMMON_SRC))
OBJECTS    = $(LOCAL_OBJ) $(COMMON_OBJ)
DEPENDS    = $(OBJECTS:.o=.d)

# 无源文件立即报错, 避免 gcc 链接空对象导致 undefined main
ifeq ($(OBJECTS),)
$(error 未找到 .cpp 源文件: 请确认 src/client.cpp、src/main.cpp 及 ../common/src/*.cpp 存在)
endif

.PHONY: all clean distclean
all: $(TARGET)

$(BINDIR) $(OBJDIR):
	mkdir -p $@

$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR)/%.o: ../common/src/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(DEPENDS)

clean:
	rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

distclean: clean
	rm -rf $(OBJDIR) $(BINDIR)
