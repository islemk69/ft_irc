# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/29 13:28:53 by ccrottie          #+#    #+#              #
#    Updated: 2024/01/29 13:28:54 by ccrottie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++
SRCS =	src/main.cpp \
		src/Server.cpp \
		src/Client.cpp \
		src/Channel.cpp \
		src/Command.cpp \
		src/utils.cpp \
		src/commands/invite.cpp \
		src/commands/join.cpp \
		src/commands/kick.cpp \
		src/commands/mode.cpp \
		src/commands/nick.cpp \
		src/commands/pass.cpp \
		src/commands/privmsg.cpp \
		src/commands/topic.cpp \
		src/commands/user.cpp \
		src/commands/part.cpp \
		src/commands/who.cpp \
		src/signal.cpp \
		src/commands/quit.cpp
OBJS_DIR = .obj
BOT_NAME = bot
OBJS = $(patsubst src/%.cpp,$(OBJS_DIR)/%.o,$(SRCS))
DEPS = $(patsubst src/%.cpp,$(OBJS_DIR)/%.d,$(SRCS))
FLAGS =  -std=c++98 -MMD -MP -g3
NAME = ircserv
HEAD = 	includes/Server.hpp \
		includes/Client.hpp \
		includes/Channel.hpp \
		includes/utils.hpp \
		includes/numericReplies.hpp	\
		includes/commands.hpp \
		includes/Command.hpp \
		includes/signal.hpp
RM = rm -f

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

$(OBJS_DIR)/%.o: src/%.cpp Makefile ${HEAD} | $(OBJS_DIR)
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@${CC} ${FLAGS} -c $< -o $@
	@echo "$(GREEN)Compilation of $< complete.$(RESET)"

all: $(NAME) $(BOT_NAME)

$(NAME): $(OBJS) ${HEAD}
	@echo "$(GREEN)Program compiling...$(RESET)"
	@$(CC) ${FLAGS} $(OBJS) -o $(NAME)
	@echo "$(GREEN)Compilation complete.$(RESET)"

$(BOT_NAME): src/Bot.cpp
	@echo "$(GREEN)Compiling bot.cpp...$(RESET)"
	@$(CC) ${FLAGS} src/Bot.cpp -o $(BOT_NAME)
	@echo "$(GREEN)Compilation of bot complete.$(RESET)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/commands
	
-include $(DEPS)

clean:
	@$(RM) -r $(OBJS_DIR)
	@echo "$(RED)Cleaned up object files.$(RESET)"

fclean: clean
	@$(RM) $(NAME) $(BOT_NAME)
	@echo "$(RED)Removed executable.$(RESET)"

re: fclean all

run:	$(NAME) 
		./ircserv 6667 pass

.PHONY: all clean fclean re
