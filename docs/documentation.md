# Project 3 Keypad / LED Patterns / RGB LED

The purpose of the project was to use a locking keypad to change patterns on an LED bar and make an RGB LED change hues. 


The main C file consists of initializations of ports that we use and the unlock function calls. Below is the flowchart of the main.c file: 

![Picture](Proj3-Main.svg)




The Keypad utilized a header file with functions that read the columns and rows of the keypad and which key was being pressed to compare against the correct passcode in order to decide whether or not to open. 




The LED bar's design consists of functions in a header file that can be included in the main C file so each of the patterns can be called in the Interrupt Service Routine dependant on which button is pressed. 

Below is each of the high-level flow charts for each of the functions in the led-bar.h header file: 

![Picture](Proj3-Patterns-Combined.svg)
