# My first Makefile
# Version 0.2

CC=g++

# Explanation:
# -Wall    significant set of warning msgs (unused/uninit vars, deprecated funcs)
# -Wextra  
# fuck it, im bored

CPPFLAGS += -std=c++17 -Wall -Wextra -Werror -Wno-missing-fielsd -Werror=vla -pthread

OUTDIR=out
TASKS := $(filter-out $(OUTDIR) Makefile,$(wildcard *))

define find_task
$(firstword $(filter $(1)% %$(1) %$(1)%,$(TASKS)))
endef

build-%:
	@$(eval DIR=$(call find_task,$*))
	@$(eval TARGET=$(OUTDIR)/$(DIR)/prog)
	@$(eval SRC=$(wildcard $(DIR)/*.cpp))
	@if [ -z "$(SRC)" ]; then \
		exit 1; \
	fi; \
	NEEDS_REBUILD=0; \
	if [ ! -f "$(TARGET)" ]; then \
		NEEDS_REBUILD=1; \
	else \
		for f in $(SRC); do \
			if [ "$$f" -nt "$(TARGET)" ]; then \
				NEEDS_REBUILD=1; \
				break; \
			fi; \
		done; \
	fi; \
	if [ $$NEEDS_REBUILD -eq 1 ]; then \
		mkdir -p "$(dir $(TARGET))"; \
		if ! $(CC) $(CPPFLAGS) -o "$(TARGET)" $(SRC); then \
			rm -rf "$(dir $(TARGET))"; \
			exit 1; \
		fi; \
	fi

run-%:
	@$(eval DIR=$(call find_task,$*))
	@$(eval TARGET=$(OUTDIR)/$(DIR)/prog)
	@$(MAKE) --no-print-directory build-$*
	@$(TARGET) $(ARGS)

clean:
	@rm -rf $(OUTDIR)
