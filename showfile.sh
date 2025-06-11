#!/bin/sh

# Check if a file was provided
if [ -z "$1" ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

# Check if the file exists
if [ ! -f "$1" ]; then
    echo "Error: File '$1' does not exist."
    exit 1
fi

# Display the file content
cat "$1"

