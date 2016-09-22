comp		=gcc
compflags	=-std=c99 -Wall
libs		=-lpthread -lprotobuf-c
path		=bin
obj			=	\
			$(path)/message.pb-c.o	\
			$(path)/main.o	\
			$(path)/ReceiveMessage.o	\

default : check_bin $(path)/secondTask

check_bin :
	@ if [ ! -d $(path) ]; then mkdir $(path); fi

$(path)/secondTask : $(obj)
	$(comp) $(compflags) -o $(path)/secondTask $(obj) $(libs)

$(path)/%.o : %.c
	$(comp) $(compflags) -c $< -o $@

clean :
	rm -f $(path)/*
