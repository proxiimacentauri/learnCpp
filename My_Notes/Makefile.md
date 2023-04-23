# MakeFile Structure
<p>

- #### Target
	- Its a user-specified name to refer to a group of commands. Similar to a function in a programming language.
	- A target is aligned on the left-hand column continous word ends with `(:)`
	- When we call `make` we can specify a `target_name`
		```
		make target_name
		```
	- `make` will check the `MakeFile` and execute the commands associated with that target.
</br>
</br>

- #### Source
	- They are references to files or other targets.
	- They represent pre-reqs / dependencies for the target they are associated with.
	  ```
	  target1: target2
		target1_command
      target2:
		target2_command
	  ```
	- If you call `make target1` it would check for `target1` in the `MakeFile` and would find `target2` as the source/dependency for `target1`. Now it would temporarily jump to `target2` check for its dependancies and if not run the commands for it and then pass the control back to `target1`.
</br>
</br>

- ## Execution of Makefile

	- Typing `make` will invoke the **first target** entry in the file.

		- It will hit `default` which has a dependency on `count`.
		- Control will pass to `count` which has dependency on `countwords.o counter.o scanner.o`
		- It will go on to `countwords.o` execute the cmd.
		- Then go to `counter.o` execute the cmd.
		- Then to `scanner.o` execute the cmd.
		- Back to `count`  execute the cmd.
		- Back to `default`.
		</br>
		</br>
			```
				CC = gcc
				CFLAGS  = -g -Wall

				default: count
				count:  countwords.o counter.o scanner.o
					$(CC) $(CFLAGS) -o count countwords.o counter.o scanner.o

				countwords.o:  countwords.c scanner.h counter.h
					$(CC) $(CFLAGS) -c countwords.c

				counter.o:  counter.c counter.h
					$(CC) $(CFLAGS) -c counter.c

				scanner.o:  scanner.c scanner.h
					$(CC) $(CFLAGS) -c scanner.c

				clean:
					$(RM) count *.o *~
			```
		</br>
		</br>


	- Simple example to build an executable named myprog from myprog.c
		```
			all: myprog.c
				gcc -g -Wall -o myprog myprog.c

			clean:
				$(RM) myprog
		```
	</br>
	</br>

	- More generic form of the above example:
		```
			CC = gcc
			CFLAGS = -g -Wall
			TARGET = mprog

			all: $(TARGET)

			$(TARGET): $(TARGET).c
				$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

			clean:
				$(RM) $(TARGET)
		```

</br>
</br>

## Operators in Makefiles

- #### Dash Before a Cmd (`-`)
	- A `(-)` before a command tells `make` to ignore errors that may occur during the execution of the command.
		```
		clean:
			-rm *.o
		```

- #### At Before a Cmd (`@`)
	- A `(@)` before a command tells `make` to NOT print output to `stdout`.
		```
		CC = gcc

		all: program

		program: main.o foo.o bar.o
			@$(CC) $^ -o $@

		main.o: main.c
			@$(CC) -c $< -o $@

		foo.o: foo.c
			@$(CC) -c $< -o $@

		bar.o: bar.c
			@$(CC) -c $< -o $@

		clean:
			@rm *.o program

		----------------------------

		build:
			@echo "Compiling source files..."
			gcc main.c -o program


		```


- #### Simple Assignment (`=`)
	- Assigns the value of a variable on RHS side to the var on LHS
		```
			CXX=g++
		```

- #### Immediate Assignment (`:=`)
	- Evaluates the RHS side immediately and assigns it to the var on LHS.
		```
			SOURCES := $(wildcard *.cpp)
		```

	- Assign the result of `wildcard` function (which expands to a list of all `.cpp` files in the current dir.) and assigns it to the variable `SOURCES`.


- #### Conditional Assignment (`?=`)
	- Assigns value of RHS to var on LHS only if LHS is not previously defined.
		```
			CXX ?= g++
		```
	- If `CXX` is already previous set to empty or to some other value the above code will not be run.
		```
			CXX = clang++ 		// CXX holds value clang++
			..
			..
			..
			CXX ?= g++			// since CXX is already set it will not run
		```

- #### Appending (`+=`)
	- Appends the value on the RHS to the current value of LHS.
		```
			CXXFLAGS = -O2
			CXXFLAGS += -Wall -Wextra   	// CXXFLAGS = -O2 -Wall -Wextra
		```

- #### Run Shell (`!=`)
	- Run the RHS as a shell command in a sub-shell and assigns the result to LHS.
		```
			SOURCES != find src/ -name '*.cpp'
		```

- #### (`$^`)
	- It expands to the list of dependancies of target.
	- `$^ --> foo.o bar.o baz.o`
		```
		myprog: foo.o bar.o baz.o
	    gcc $^ -o $@
		```

- #### (`$<`)
	- It expands to the 1st dependancy of target.
	- `$< --> foo.o`
		```
		myprog: foo.o bar.o baz.o
	    gcc $< -o $@
		```

- #### (`$@`)
	- It expands to the name of the target file.
	- `$@ --> myprog`
		```
		myprog: foo.o bar.o baz.o
	    gcc $< -o $@
		```


- #### (`$?`) and (`$*`)
	- Find good examples

- #### Wildcard (`% * wildcard`)
	- It expands to the name of the target file.
		```
		%.o: %.c
			gcc -c $< -o $@

		all: $(wildcard *.c)
			gcc $^ -o myprog
		```
	- `*` wildcard in the target matches any characters before the txt extension, so the target newdir/*txt will match `newdir/file1.txt` and `newdir/file2.txt`
		```
		newdir/*txt: *.txt
			cp $< $@
		```
	- `%` wildcard in the target matches any string of characters before the .doc extension, so the target %.exe will match file1.exe and file2.exe.
		```
		%.exe: %.doc
	    	gcc $< -o $@
		```

</br>
</br>

## Guidelines for a better MakeFile

- #### Tabs
	- Don't use tabs use `>` as a block char
		```
		ifeq ($(origin .RECIPEPREFIX), undefined)
	    	$(error This Make does not support .RECIPEPREFIX. Please use GNU Make 4.0 or later)
		endif
		.RECIPEPREFIX = >
		```
	- The version check is NOT neccessary but is good to have. With the above change:
		```
		hello:
			echo "Hello"
			echo "world"
		.PHONY: hello
		```
		Would look like:
		```
		hello:
		> echo "Hello"
		> echo "world"
		.PHONY: hello
		```

- #### Specify Shell
	- Use recent `bash`, make by default uses `/bin/sh`. Point is to specify a specific shell.
		```
		SHELL := bash
		```

- #### Use Shell flags
	- Use the following flags to perform error check that the shell gives you.
		```
		.SHELLFLAGS := -eu -o pipefail -c
		```

- #### Change some Make Defaults
	- Use `.ONESHELL` it ensures that the make recipie is ran as single shell session, rather than 1 new shell per line.
		```
		.ONESHELL
		```
	- Use `.DELETE_ON_ERROR` if a make rule fails, its target file is deleted.
		```
		.DELETE_ON_ERROR
		```
	- Get a warning if we are refering to make variables that dont exsists.
		```
		MAKEFLAGS += --warn-undefined-variables
		```
	- [OPTIONAL] Removes built in rules, which means we need to specify everything.
		```
		MAKEFLAGS += --no-builtin-rules
		```

- #### TL;DR
	```
	SHELL := bash
	.ONESHELL:
	.DELETE_ON_ERROR:
	.SHELLFLAGS := -eu -o pipefail -c
	MAKEFLAGS += --warn-undefined-variables

	ifeq ($(origin .RECIPEPREFIX), undefined)
	$(error This Make does not support .RECIPEPREFIX. Please use GNU Make 4.0 or later)
	endif
	.RECIPEPREFIX = >
	```
