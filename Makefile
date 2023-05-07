
# Runs the compiled output
run: clean compile 
	output/out

# Compiles
compile: src/Client/*.cpp
	clang++ src/Client/*.cpp -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -o output/out

# Removes compiled code inside output
clean:
	rm output/out



# Code to compile old Client

runC: cleanC compileC
	output/client

compileC:
	g++ src/Client/old/client.cpp -w -o output/client

cleanC:
	rm output/client



#Code to compile the server

runS: cleanS compileS
	lsof -ti:8080 | xargs kill -9
	output/server

compileS:
	g++ src/Server/server.cpp -w -o output/server

cleanS:
	rm output/server
