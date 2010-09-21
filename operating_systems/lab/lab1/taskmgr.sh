#!/bin/bash

#1.6. [2] Напишите скрипт, управляющий списком текущих дел. Скрипт должен хранить
#     список дел в файле .todo в текущем каталоге и предоставлять возможность
#     добавления задачи, удаления задачи, отметки задачи как выполненной и
#     просмотра всех задач. Режим работы задается параметром командной строки.
#     Предусмотрите также параметр, при использовании которого скрипт будет
#     работать с файлом .todo в домашнем каталоге пользователя независимо от
#     наличия файла .todo в текущем каталоге.
#     Все скрипты должны выдавать справку о своем назначении и поддерживаемых параметрах
#     командной строки. Справка печатается на экран, если среди параметров есть ключ
#     «--help» или «-h», никаких других действий в этом случае выполнять не нужно.


# Global help message variable
HELP_MSG="Usage: ./taskmgr.sh [-g] [-a|-r|-d|-l]\nOptions: \n
	-g, --global \t Work with ~/.todo file, otherwise .todo file in current directory will be used \n\n
	-a, --add \t Add new task \n
	-r, --remove \t Remove task from the list \n
	-d, --done \t Mark certain task as 'done' \n
	-l, --list \t List present tasks \n
	-h, --help \t Display this message \n
  "

# Store script arguments in variable
args=("$@")

declare file_name

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
}

function addTask()
{
	echo "fuck"
}

function deleteTask()
{
	echo "ss"
}

function markTaskDone()
{
	echo "yy"
}

function listTasks()
{
	echo "aa"
}

function processArguments()
{
   determineFile
}

# Entry point for the script
function work()
{
   # If help argument provided, nothing more is required
   findParameter -h --help
   return_val=$?

   if [ $return_val -ne 0 ]; then
      echo -e $HELP_MSG
   else
      # If not, going to process another arguments
      processArguments
   fi
}

# Begin to work
work
