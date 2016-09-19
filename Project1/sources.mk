
# These are the source files
options_c = data.c memory.c main.c project_1.c

#These are the header files
options_h = data.h memory.h project_1.h

# These are the object files
options_o = data.o memory.o project_1.o main.o



# Setting the directories
object_directory = Project1/object

output_directory = Project1/output


# Setting the path
VPATH = Project1:../object


OBJECT_PATH = $(pathsubst %, $(output_directory)/%, $(options_o))

HEADER_PATH = $(pathsubst %, $(object_directory)/%, $(options_h))

