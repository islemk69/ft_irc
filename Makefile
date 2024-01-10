CC = c++
SRCS = src/main.cpp src/Server.cpp src/Client.cpp
OBJS_DIR = .obj
OBJS = $(patsubst src/%.cpp,$(OBJS_DIR)/%.o,$(SRCS))
DEPS = $(patsubst src/%.cpp,$(OBJS_DIR)/%.d,$(SRCS))
FLAGS =  -std=c++98 -MMD -MP
NAME = ircserv
HEAD = includes/Server.hpp includes/Client.hpp
RM = rm -f

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

$(OBJS_DIR)/%.o: src/%.cpp Makefile ${HEAD} | $(OBJS_DIR)
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@${CC} ${FLAGS} -c $< -o $@
	@echo "$(GREEN)Compilation of $< complete.$(RESET)"

all: $(NAME)

$(NAME): $(OBJS) ${HEAD}
	@echo "$(GREEN)Program compiling...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Compilation complete.$(RESET)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	
-include $(DEPS)

clean:
	@$(RM) -r $(OBJS_DIR)
	@echo "$(RED)Cleaned up object files.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Removed executable.$(RESET)"

re: fclean all

.PHONY: all clean fclean re