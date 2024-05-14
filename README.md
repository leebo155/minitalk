# minitalk
 A small data exchange program using UNIX signals.

## Introduction
* This project consists of two programs: `server` and `client`.
* The two programs exchange data with each other using `SIGUSR1` and `SIGUSR2`.
* The server must be started first. After its launch, it has to print its PID.
* The client takes two parameters:   
  ◦ The server PID.   
  ◦ The string to send
* Below is the process of transmitting and receiving the character `'a'`.   
  <img alt="image" src="https://github.com/leebo155/minitalk/blob/main/img/minitalk_main.jpg">

## Process
* Basic
  <img alt="image" src="https://github.com/leebo155/minitalk/blob/main/img/minitalk1.jpg">
  <img alt="image" src="https://github.com/leebo155/minitalk/blob/main/img/minitalk2.jpg">
  
* Bonus
  <img alt="image" src="https://github.com/leebo155/minitalk/blob/main/img/minitalk_bonus1.jpg">
  <img alt="image" src="https://github.com/leebo155/minitalk/blob/main/img/minitalk_bonus2.jpg">

## Makefile
| Rules | Description |
| ----- | ----------- |
| all | Compile basic programs that server and client. |
| bonus | Compile bonus programs that server and client. |
| clean | Remove all the temporary generated files. |
| fclean | Remove all the generated files. |
| re | Remove all the generated files and compile basic server and client. |

## Usage
* Run the server first.
  ```shall
  ./server
  PID : 13661
  ```

* Run the client with the server PID.   
  ◦ client
  ```shall
  ./client 13661 hello
  ```
  
  ◦ server
  ```shall
  ./server
  PID : 13661
  hello
  ```
