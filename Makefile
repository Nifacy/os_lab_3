compiled/app: compiled/ofiles/main.o compiled/libs/manager.a compiled/libs/io_matrix.a
	gcc compiled/ofiles/main.o compiled/libs/manager.a compiled/libs/io_matrix.a -lpthread -o compiled/app

# Object files

compiled/ofiles/main.o: src/main.c src/task/task.h
	gcc -c src/main.c -o compiled/ofiles/main.o

compiled/ofiles/manager.o: src/manager/manager.c
	gcc -c src/manager/manager.c -o compiled/ofiles/manager.o

compiled/ofiles/observer.o : src/manager/observer/observer.c
	gcc -c src/manager/observer/observer.c -o compiled/ofiles/observer.o

compiled/ofiles/task_buffer.o: src/manager/task_buffer/task_buffer.c
	gcc -c src/manager/task_buffer/task_buffer.c -o compiled/ofiles/task_buffer.o

compiled/ofiles/io_matrix.o: src/io_matrix/io_matrix.c
	gcc -c src/io_matrix/io_matrix.c -o compiled/ofiles/io_matrix.o

compiled/ofiles/matrix.o: src/matrix/matrix.c
	gcc -c src/matrix/matrix.c -o compiled/ofiles/matrix.o

compiled/ofiles/worker.o: src/worker/worker.c
	gcc -c src/worker/worker.c -o compiled/ofiles/worker.o

# Libraries

compiled/libs/manager.a: compiled/ofiles/manager.o compiled/ofiles/observer.o compiled/ofiles/task_buffer.o compiled/ofiles/worker.o
	ar -crs compiled/libs/manager.a compiled/ofiles/manager.o compiled/ofiles/observer.o compiled/ofiles/task_buffer.o compiled/ofiles/worker.o

compiled/libs/io_matrix.a: compiled/ofiles/io_matrix.o compiled/ofiles/matrix.o
	ar -crs compiled/libs/io_matrix.a compiled/ofiles/io_matrix.o compiled/ofiles/matrix.o

# utils

compile_dir:
	mkdir -p compiled
	mkdir -p compiled/ofiles
	mkdir -p compiled/libs

all: compile_dir compiled/app
