#!/bin/bash

# Import terminal colors
RED="\e[31m"
GREEN="\e[32m"
LIGHT_GRAY="\e[37m"
PURPLE="\e[35m"
BOLD="\033[1m"
DEFAULT="\e[0m"

# Create variables to keep track of all the different test statistics
test_cnt=0
tests_passed=0

# Test the output code
test_script_output(){
    test_description=$1 # The test description
    test_cnt=$2         # Test count
    test_file=$(pwd)/io_tests2024/$3.input  # Program input file
    test_output=$(pwd)/io_tests2024/$3.output  # Program output file

    printf "${LIGHT_GRAY}[Test $test_cnt] – $test_description\n" # Print information about the current test

    # Run the script
    ./io-test <"$test_file" > "tmp_file.out"

    # Check the output
    output=$(cat ./tmp_file.out)
    ref_ouput=$(cat "$test_output")
    
    # Check if the return code and output is matching
    if [ "$output" == "$ref_ouput" ]; then
        echo -e "${GREEN}Test passed ✓ ${DEFAULT}\n"
        # Increase the passed tests count
        tests_passed=$(($tests_passed + 1))
    else
        echo -e "${RED}Test failed ⨯ ${DEFAULT}\n"
    fi

    # Increase the test count
    test_cnt=$(($test_cnt + 1))
}

printf "${LIGHT_GRAY}Running io tests...\n\n" # Print information about the current test

# Run the output tests
for file in "./io_tests2024"/*.input; do
    test_name=$(echo "$file" | rev | cut -d '.' -f2 | cut -d '/' -f1 | rev)
    test_script_output "Testing basic and advanced functionality - $test_name test" $test_cnt "$test_name"
done

printf "${BOLD}${PURPLE}Total:\n\tTESTS PASSED = $tests_passed/$test_cnt\n\tTESTS FAILED = $(($test_cnt - $tests_passed))/$test_cnt\n\n"

rm tmp_file.out

#if [ $tests_passed -eq $test_cnt ]
#then
#    xdg-open --version > /dev/null 2>&1
#    if [ $? -eq 0 ]
#    then
#        xdg-open ./tail_tests2024/__/klidecek.jpg > /dev/null 2>&1
#    fi
#fi

# Author ~ Marek Čupr (xcuprm01)
