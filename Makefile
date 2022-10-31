.PHONY: all clean fclean re

NAME			= ircserv

SOURCE			= srcs_connect/Connect.cpp \
                  srv_inside/CommandLine.cpp srv_inside/NicknameStorage.cpp srv_inside/Room.cpp srv_inside/RoomStorage.cpp \
                  srv_inside/User.cpp srv_inside/UserStorage.cpp \
                  tools/LogIdentifier.cpp \
                  Commando.cpp MainCircuit.cpp Parser.cpp Serv.cpp
HEADERS			= includes/*.hpp

OBJECTDIR		=	objects/

OBJECT			=	$(addprefix $(OBJECTDIR), $(SOURCE:.cpp=.o))

CXX				= 	c++

CXXFLAGS		= 	-std=c++98
#-Wall -Wextra -Werror

RESET			= 	\033[0m
GREEN 			= 	\033[38;5;46m
WHITE 			= 	\033[38;5;15m
GREY 			= 	\033[38;5;8m
ORANGE 			= 	\033[38;5;202m
RED 			= 	\033[38;5;160m

all: $(NAME)

$(OBJECTDIR):
	mkdir objects
	mkdir objects/srcs_connect
	mkdir objects/srv_inside
	mkdir objects/tools

$(OBJECTDIR)%.o: %.cpp $(HEADERS)
	@echo "$(GREY)Compiling...				$(WHITE)$<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJECTDIR) $(OBJECT)
	@echo "$(GREEN)----------------------------------------------------"
	@$(CXX) $(CXXFLAGS) $(OBJECT) -o $(NAME)
	@echo "Executable				./$(NAME) $(RESET)"

clean:
	@echo "$(RED)----------------------------------------------------"
	@/bin/rm -f $(OBJECT)
	@/bin/rm -rf $(OBJECTDIR)
	@echo "$(WHITE)REMOVED O-FILES $(RESET)"

fclean: clean
	@echo "$(RED)----------------------------------------------------"
	@/bin/rm -f $(NAME)
	@echo "$(WHITE)REMOVED EXECUTABLE FILE $(RESET)"

re: fclean all

