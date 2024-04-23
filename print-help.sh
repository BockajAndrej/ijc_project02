#!/bin/bash

# Import terminal colors
RED="\e[31m"
GREEN="\e[32m"
LIGHT_GRAY="\e[37m"
PURPLE="\e[35m"
BOLD="\033[1m"
DEFAULT="\e[0m"

clear

printf "${LIGHT_GRAY} Usage: make [target]\n${DEFAULT}"
printf "${GREEN}\t ◦ all = run all tests\n${DEFAULT}"
printf "${GREEN}\t ◦ tail = run tail tests\n${DEFAULT}"
printf "${GREEN}\t ◦ io = run io tests\n${DEFAULT}"
printf "${GREEN}\t ◦ wordcount = run wordcount tests\n${DEFAULT}"
printf "${RED}\t ◦ help = print usage to the user\n${DEFAULT}"
printf "${RED}\t ◦ clean = delete extra files created in the process\n${DEFAULT}"
printf "\n"
printf "${RED}Warning: \n${DEFAULT}"
printf "${RED}\t ◦ tail      ... needs to be compiled manually by the user\n${DEFAULT}"
printf "${RED}\t ◦ io        ... is compiled automatically by the script\n${DEFAULT}"
printf "${RED}\t ◦ wordcount ... needs to be compiled manually by the user\n${DEFAULT}"
