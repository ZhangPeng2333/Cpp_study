# C++ 封装版服务器

TARGET   = bin/app
CXX      = g++
CXXFLAGS = -g -Wall -O0 -pthread -I$(INCDIR) -I../common/inc
LDFLAGS  = -pthread -lsqlite3 -lcrypto

# spdlog 日志库
# 说明: Ubuntu jammy 的 libspdlog-dev(1.9.2) 不提供 spdlog.pc,
# 故优先探测头文件, 链接按 header-only 处理(无 .pc 也能正常编译)。
SPD_CFLAGS :=
SPD_LIBS   :=
ifeq ($(wildcard /usr/include/spdlog/spdlog.h /usr/local/include/spdlog/spdlog.h),)
# 头文件不在常规路径, 退路尝试 pkg-config
ifeq ($(shell pkg-config --exists spdlog 2>/dev/null && echo yes),yes)
SPD_CFLAGS := $(shell pkg-config --cflags spdlog)
SPD_LIBS   := $(shell pkg-config --libs spdlog)
else
$(error spdlog 未找到: 请先执行 `sudo apt install libspdlog-dev`)
endif
else
# 头文件存在: Ubuntu 的 libspdlog-dev(1.9.x) 以共享库形式提供,
# 且 fmt 也是独立系统库, 故需同时链接 -lspdlog 与 -lfmt。
SPD_LIBS := $(shell ld -lspdlog >/dev/null 2>&1 && echo -lspdlog || true)
SPD_LIBS += $(shell ld -lfmt >/dev/null 2>&1 && echo -lfmt || true)
endif
CXXFLAGS += $(SPD_CFLAGS)
LDFLAGS  += $(SPD_LIBS)

SRCDIR   = src
OBJDIR   = obj
INCDIR   = inc
BINDIR   = bin
RESDIR   = resourse

LOCAL_SRC  = $(wildcard $(SRCDIR)/*.cpp)
LOCAL_OBJ  = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(LOCAL_SRC))
COMMON_SRC = $(wildcard ../common/src/*.cpp)
COMMON_OBJ = $(patsubst ../common/src/%.cpp, $(OBJDIR)/%.o, $(COMMON_SRC))
OBJECTS    = $(LOCAL_OBJ) $(COMMON_OBJ)
DEPENDS    = $(OBJECTS:.o=.d)

RES_FILES  = $(RESDIR)/hello1.txt $(RESDIR)/hello2.txt $(RESDIR)/hello3.txt $(RESDIR)/welcome.txt

# 无源文件立即报错, 避免 gcc 链接空对象导致 undefined main
ifeq ($(OBJECTS),)
$(error 未找到 .cpp 源文件: 请确认 src/main.cpp、src/server.cpp 及 ../common/src/*.cpp 存在)
endif

.PHONY: all clean distclean resources
all: $(TARGET) resources

$(BINDIR) $(OBJDIR):
	mkdir -p $@

$(RESDIR):
	mkdir -p $(RESDIR)

$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR)/%.o: ../common/src/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(DEPENDS)

# 生成资源文件(每次make重新生成)
resources: | $(RESDIR)
	yes "Hello World" | head -c 500M > $(RESDIR)/hello1.txt
	yes "Hello C" | head -c 200M > $(RESDIR)/hello2.txt
	yes "Hello CPP" | head -c 300M > $(RESDIR)/hello3.txt
	yes "Welcome to China!" | head -c 5G > $(RESDIR)/welcome.txt

clean:
	rm -f $(OBJECTS) $(DEPENDS) $(TARGET) $(RES_FILES)

distclean: clean
	rm -rf $(OBJDIR) $(BINDIR) $(RESDIR)
