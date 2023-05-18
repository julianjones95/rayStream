
# Runs the compiled output
run: clean compile 
	output/out

# Compiles
compile: src/Client/*.cpp
	clang++ src/Client/*.cpp -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -g -o output/out

# Removes compiled code inside output
clean:
	rm output/out



#Code to compile the server

runS: cleanS compileS
	lsof -ti:8080 | xargs kill -9
	output/server

compileS:
	g++ src/Server/*.cpp -w -g -o output/server

cleanS:
	rm output/server
