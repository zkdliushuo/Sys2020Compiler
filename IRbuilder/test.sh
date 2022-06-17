#!/bin/bash
flag="1"
for file in ../../functional_test/*
do
    if [ "${file##*.}"x = "sy"x ]; then
	    echo ${file:0:((${#varname}-3))}
        ./c1i $file;
        if [ "${?}" -ne "0" ]; then
            echo "WRONG program ${file}"
            ${flag} = "0"
            continue
        fi 
        llvm-link ${file:0:((${#varname}-3))}.ll ../src/io.ll -o ${file:0:((${#varname}-3))}.bc;
        if [ "${?}" -ne "0" ]; then
            echo "WRONG llvm linker ${file}"
            ${flag} = "0"
            continue
        fi 
        llc ${file:0:((${#varname}-3))}.bc -filetype=obj;
        if [ "${?}" -ne "0" ]; then
            echo "WRONG llvm codegen ${file}"
            ${flag} = "0"
            continue
        fi 
        clang ${file:0:((${#varname}-3))}.o -o ${file:0:((${#varname}-3))};
        if [ "${?}" -ne "0" ]; then
            echo "WRONG generate excutable ${file}"
            ${flag} = "0"
            continue
        fi 
        if [ ! -f ${file:0:((${#varname}-3))}.in ]; then
            ./${file:0:((${#varname}-3))} > ${file:0:((${#varname}-3))}.result
        else
            cat ${file:0:((${#varname}-3))}.in | ./${file:0:((${#varname}-3))} > ${file:0:((${#varname}-3))}.result
        fi
	    echo -e -n "\n${?}" >> ${file:0:((${#varname}-3))}.result
        diff -B -b ${file:0:((${#varname}-3))}.result ${file:0:((${#varname}-3))}.out > /dev/null
        if [ "${?}"x = "0"x ]; then
            echo "Success"
        else
            echo "Wrong"
            ${flag} = "0"
        fi
        rm ${file:0:((${#varname}-3))}.result
    fi
done

if [ "${flag}"x = "1"x ]; then
    echo -e "\nPass Functional Test"
else
    echo -e "\nFail Functional Test"
    exit 1
fi

flag="1"
for file in ../../performance_test/*
do
    if [ "${file##*.}"x = "sy"x ]; then
	    echo ${file:0:((${#varname}-3))}
        ./c1i $file;
        if [ "${?}" -ne "0" ]; then
            echo "WRONG program ${file}"
            continue
        fi 
        llvm-link ${file:0:((${#varname}-3))}.ll ../src/io.ll -o ${file:0:((${#varname}-3))}.bc;
        if [ "${?}" -ne "0" ]; then
            echo "WRONG llvm linker ${file}"
            continue
        fi 
        llc ${file:0:((${#varname}-3))}.bc -filetype=obj;
        if [ "${?}" -ne "0" ]; then
            echo "WRONG llvm codegen ${file}"
            continue
        fi 
        clang ${file:0:((${#varname}-3))}.o -o ${file:0:((${#varname}-3))};
        if [ "${?}" -ne "0" ]; then
            echo "WRONG generate excutable ${file}"
            continue
        fi 
        if [ ! -f ${file:0:((${#varname}-3))}.in ]; then
            ./${file:0:((${#varname}-3))} > ${file:0:((${#varname}-3))}.result
        else
            cat ${file:0:((${#varname}-3))}.in | ./${file:0:((${#varname}-3))} > ${file:0:((${#varname}-3))}.result
        fi
	    echo -e -n "\n${?}" >> ${file:0:((${#varname}-3))}.result
        diff -B -b ${file:0:((${#varname}-3))}.result ${file:0:((${#varname}-3))}.out > /dev/null
        if [ "${?}"x = "0"x ]; then
            echo "Success"
        else
            echo "Wrong"
        fi
        rm ${file:0:((${#varname}-3))}.result
    fi
done

if [ "${flag}"x = "1"x ]; then
    echo -e "\nPass Performance Test"
else
    echo -e "\nFail Performance Test"
    exit 1
fi