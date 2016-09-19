
# These are the source files
options_c = data.c memory.c main.c project_1.c

#These are the header files
options_h = data.h memory.h project_1.h

# These are the object files
options_o = data.o memory.o project_1.o main.o


object_directory = Project1/object

output_directory = Project1/output

VPATH = Project1:../object


HEADER_PATH = $(pathsubst %, $(object_directory)/%, $(options_h))

OBJECT_PATH = $(pathsubst %, $(output_directory)/%, $(options_o))


