
#!/bin/bash

# Calling make for server and client programs
make all

# Clearing the terminal
clear

# Check if there are exactly 2 arguments
if [[ $# -eq 2 ]]; then
	arg="$1"
	numberOfClient="$2"

	# If Argument is "run" then run the server and "$2" number of client applications
	if [[ "$arg" = "run" ]]; then
		gnome-terminal -- ./server
		for ((i = 0; i < numberOfClient; i++)); do
			# For the last iteration, run the client and exit
			if [[ "$i" -eq "$((numberOfClient - 1))" ]]; then
				gnome-terminal -- ./client && exit
			else
				gnome-terminal -- ./client
			fi
		done
	fi
fi
