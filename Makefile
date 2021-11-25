# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gricquie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/21 20:51:53 by gricquie          #+#    #+#              #
#    Updated: 2021/11/19 16:54:23 by gricquie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = abstract-vm

HDIR = header
SDIR = src
ODIR = obj

CC=g++
FLAGS=-Wall -Wextra -Werror

SRCS_RAW =		main.cpp \
				Operand.cpp \
				OperandFactory.cpp \
				FloatingPointException.cpp \
				getStream.cpp \
				LexerToken.cpp \
				Lexer.cpp \
				Stack.cpp \
				Instr.cpp \
				Parser.cpp \

OBJS_RAW = $(SRCS_RAW:.cpp=.o)
HEADERS_RAW =	abstract-vm.hpp \
				eOperandType.hpp \
				IOperand.hpp \
				Operand.hpp \
				OperandFactory.hpp \
				FloatingPointException.hpp \
				getStream.hpp \
				eLexerTokenType.hpp \
				LexerToken.hpp \
				Lexer.hpp \
				Stack.hpp \
				Instr.hpp \
				Parser.hpp \

SRCS = $(addprefix $(SDIR)/, $(SRCS_RAW))
OBJS = $(addprefix $(ODIR)/, $(OBJS_RAW))
HEADERS = $(addprefix $(HDIR)/, $(HEADERS_RAW))

all : $(NAME)

$(NAME) : $(OBJS) $(HEADERS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) -I$(HDIR)

$(ODIR)/%.o : $(SDIR)/%.cpp $(HEADERS)
	@mkdir -p $(ODIR)
	$(CC) $(FLAGS) -c $< -o $@ -I$(HDIR)

run : $(NAME)
	./$(NAME)

clean : 
	rm -f $(OBJS)
	rmdir $(ODIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all run clean fclean re
