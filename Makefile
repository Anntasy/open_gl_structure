CC			:=	g++
FLAG		:=	#-Wall -Wextra -Werror
LIBS		:=	-lglfw -lGLEW -lGL -lSOIL -lGLU

CNAMES	:=	main.cpp Shader.cpp VertexData.cpp Texture.cpp utilities.cpp

ONAMES		:=	$(CNAMES:.cpp=.o)

HNAMES	:=	h.hpp Shader.hpp VertexData.hpp Texture.hpp

NAME		:=	project
RM			:=	rm -f

test: all
	@./$(NAME)

all: $(NAME)

$(NAME): $(ONAMES) $(HNAMES) Makefile
	@$(CC) $(ONAMES) -o $(NAME) $(LIBS)
	@printf "Makefile: $(NAME) successfuly built\n"

%.o: %.cpp $(HNAMES) Makefile
	@$(CC) $(FLAG) -c $< -o $@

clean:
	@$(RM) $(ONAMES)
	@printf "Makefile: all non-source files deleted\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "Even the $(NAME)\n"

re: fclean all

.PHONY: all clean fclean re