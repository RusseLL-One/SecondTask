comp		=gcc
compflags	=-std=c99 -Wall
libs		=-lpthread
path		=bin
obj			=	\
			$(path)/main.o	\
			$(path)/MessageAddDashes.o	\
			$(path)/MessageAddSpaces.o	\
			$(path)/MessageReverse.o	\
			$(path)/MessageUpper.o	\
			$(path)/queue.o	\
			$(path)/ReceiveMessage.o	\
			$(path)/SendMessage.o	\

default : check_bin $(path)/secondTask

check_bin :
	@ if [ ! -d $(path) ]; then mkdir $(path); fi

$(path)/secondTask : $(obj)
	$(comp) $(compflags) -o $(path)/secondTask $(obj) $(libs)

$(path)/%.o : %.c
	$(comp) $(compflags) -c $< -o $@

clean :
	rm -rf $(path)
