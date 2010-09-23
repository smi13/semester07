#!/bin/bash

# 1.6 [2] Напишите скрипт, управляющий списком текущих дел. Скрипт должен хранить
#     список дел в файле .todo в текущем каталоге и предоставлять возможность
#     добавления задачи, удаления задачи, отметки задачи как выполненной и
#     просмотра всех задач. Режим работы задается параметром командной строки.
#     Предусмотрите также параметр, при использовании которого скрипт будет
#     работать с файлом .todo в домашнем каталоге пользователя независимо от
#     наличия файла .todo в текущем каталоге.
#     Все скрипты должны выдавать справку о своем назначении и поддерживаемых параметрах
#     командной строки. Справка печатается на экран, если среди параметров есть ключ
#     «--help» или «-h», никаких других действий в этом случае выполнять не нужно.

# TODO: Comment the code

# Global help message variable
HELP_MSG="Usage: ./taskmgr.sh [-h] [-g] [-a|-r|-d|-l]\nOptions: \n
	-g, --global \t Work with ~/.todo file, otherwise .todo file in current directory will be used \n\n
	-a, --add \t Add new task \n
	-r, --remove \t Remove task from the list \n
	-d, --done \t Mark certain task as 'done' \n
	-l, --list \t Display present tasks \n
	-h, --help \t Display this message \n"

args=("$@")

declare file_name
declare line_count
declare -a file_array

function readFile()
{
   let count=0
   
   while read LINE; do

      file_array[$count]=$LINE
      ((count++))
   done <$file_name

   line_count=${#file_array[@]} 
}

# Find argument in array function
function _findArg()
{
   if [ -z "$1" ]; then	
      return
   fi

   for i in ${args[@]} 
   do
      if [ $i == $1 ]; then
         return 1
      fi
   done

   return 0
}

function findParameter()
{
   _findArg $1
   local ret_1=$?

   _findArg $2
   local ret_2=$?

   if [ $ret_1 -ne 0 ] || [ $ret_2 -ne 0 ]; then
      return 1  
   else
      return 0
   fi
}

# Check which file should be modified
function determineFile()
{
   findParameter -g --global
   local ret_value=$?

   if [ $ret_value -ne 0 ]; then
      file_name=$HOME"/.todo"
   else
      file_name=".todo"
   fi  

   if [ ! -e $file_name ]; then
      touch $file_name
   fi

   readFile
}

function addTask()
{
   local task_message
   echo -e "Write task message:"
   read task_message

   file_array[$line_count]=$task_message
   ((line_count++))
}

# Tests whether *entire string* is numerical.
# In other words, tests for integer variable.
function isDigit()    
{               
  [ $# -eq 1 ] || return 0

  case $1 in
    *[!0-9]*|"") return 0;;
              *) return 1;;
  esac
}

function deleteTask()
{
   listTasks
   echo -e "What task will be removed? (number)"
   read number

   isDigit $number

   if [ $? -eq 0 ]; then
      echo "Invalid number"
      return
   else
     if [ $number -gt $line_count ] || [ $number -eq 0 ]; then
        echo "Invalid number"    
        return	
     fi

     ((number--))
     unset file_array[$number]
   fi
}

function markTaskDone()
{
   listTasks
   echo -e "What task is done? (number)"
   read number

   isDigit $number
   
   if [ $? -eq 0 ]; then
      echo "Invalid number"
      return
   else
     if [ $number -gt $line_count ] || [ $number -eq 0 ]; then
        echo "Invalid number"    
        return	
     fi

     ((number--))

     if [[ ${file_array[$number]} =~ done ]]; then
        echo "Task #$((number+1)) has been already marked as done"
	return
     fi
   fi

   file_array[$number]+=" (done)"
}

function listTasks()
{
   for ((i=0; i<$line_count; i++)); do
      if [ $# -eq 0 ]; then
        echo $((i+1))")" ${file_array[$i]}	   
      else
        if [ -z "${file_array[$i]}" ]; then      
           continue
        else
           echo ${file_array[$i]}	   
        fi
      fi
   done
}

function processArguments()
{
   determineFile

   local command

   #TODO: check -g order
   if [ -z ${args[1]} ]; then
      command=${args[0]}
   else
      command=${args[1]}
   fi

   case "$command" in
      -a|--add)
         addTask
         ;;
      -l|--list)
         listTasks
	 ;;
      -r|--remove)
      	 deleteTask
	 ;;
      -d|--done)
         markTaskDone
	 ;;
       *)
         echo -e "Invalid arguments\n"$HELP_MSG
	 ;;       
   esac      
}

# Entry point for the script
function work()
{
   if [ ${#args[@]} -eq 0 ]; then
      echo -e "No argument provided\n"$HELP_MSG
      return
   fi

   if [ ${#args[@]} -eq 1 ]; then
      if [ ${args[0]} == "-g" ] || [ ${args[0]} == "--global" ]; then
         echo -e "No command provided\n"$HELP_MSG
	 return
      fi
   fi
  
   # If help argument provided, nothing more is required
   findParameter -h --help
   return_val=$?

   if [ $return_val -ne 0 ]; then
      echo -e $HELP_MSG
   else
      # If not, going to process another arguments
      processArguments
   fi

   if [ -z "$file_name" ]; then
      return
   else
      listTasks "fake_param" > $file_name
   fi
}

# Begin to work
work
