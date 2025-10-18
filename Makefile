# My first Makefile
# Version 0.1

CC=g++

# Explanation:
# -Wall    significant set of warning msgs (unused/uninit vars, deprecated funcs)
# -Wextra  
# fuck it, im bored

CPPFLAGS += -std=c++17 -Wall -Wextra -Werror -Wno-missing-fielsd -Werror=vla -pthread

OUTDIR=out
TASKS := $(filter-out $(OUTDIR) Makefile,$(wildcard *))

$(OUTDIR):
	mkdir -p $(OUTDIR)

define find_task
$(firstword $(filter $(1)% %$(1) %$(1)%,$(TASKS)))
endef

build-%: $(OUTDIR)
	$(eval DIR=$(call find_task,$*))
	$(eval TARGET=$(OUTDIR)/$(DIR))
	$(eval SRC=$(wildcard $(DIR)/*.cpp))
	mkdir -p $(TARGET)
	$(CC) $(CPPFLAGS) -o $(TARGET)/prog $(SRC)

run-%: build-%
	$(eval DIR=$(call find_task,$*))
	./$(OUTDIR)/$(DIR)/prog

clean:
	rm -rf $(OUTDIR)
