
# Runs the compiled output
run: clean compile 
	output/out

# Compiles
compile: src/*.cpp
	clang++ src/*.cpp -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -o output/out

# Removes compiled code inside output
clean:
	rm output/out
