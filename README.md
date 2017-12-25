mamboMarket
===========


Prerequisites
=============

### BOOST
	UBUNTU 16.04 libboost-all-dev

### gcc  ≥5 
requires C++11 support 4.8 may or may not work.

### autoconf-archive
	UBUNTU 16.04 autoconf-archive



Installation instructions
========================

	git clone https://scrappy73@bitbucket. iorg/scrappy73/mamboMarket.git
	cd mamboMarket
	autoreconf --install -force 
	./configure
	make
	

Usage
=====
Currently the program is run as follows
	
	./mambo aapl

aapl is a stock symbol

Attribution
===========
Portions of this program were derived from sec-xbrl == a python programo designed to connect to sec.gov and download zip archives and access ratios from 10-Q reports.

