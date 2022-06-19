**Autoři:** Ivan Sedakov, Tikhon Zaikin  
**Projekt:** Popular Simple Game - Snake  
**Předmět:** A0B36APO - Architektura počítačů  
**Semestr:** letní 2020/2021  
           

Úvod
====

Semestrální práce z předmětu APO. Jednoduchá a popularní hra Had.
Had se neustále pochybuje po ploše a sbírá jablka, a tím roste.
Had nesmí narazit do zdi a taky sám do sebe. 

Instalace
=========

1.  Naklonovat projekt: 
	```git clone git@gitlab.fel.cvut.cz:sedakiva/apo-sem-work.git```

2.  Ve složce ./Snake zkompilovat projekt příkazem make: 
        ```cd apo-sem-work/Snake && make```

3.  Soubor snake_main v složce Snake nahrát do QtMips.

Tlačitka
========

**První - červené, tlačítko** ovladá hada (checkbox + jedna z odpovidajících poloh: up, right, left, down)  
**Druhé - zelené, tlačítko** restartuje hru (checkbox + poloha 128-255)  
**Třetí - modré, tlačítko** ukončí hru (checkbox + poloha 128-255)  

Moduly
======

### snake_main.c ###
	contains a main function
	
### point.c ###
	is used to represents 2D coordinates
	
### snake.c ###
	represents a snake part
	
### apple.c ###
	represents a apple part
	
### move_utils.c ###
	contains utils for objects moving
	
### terminal.c ###
	is used to write info to the console
	
### game_manager.c ###
	is used for combination all other objects
	
### controller.c ###
	checks buttons events
	
### frontend.c ###
	is used to draw pixels on the display
