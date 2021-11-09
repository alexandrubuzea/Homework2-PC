build:
	gcc *.c *.h -o star_dust -Wall -Wextra
clean:
	rm star_dust
.PHONY: clean