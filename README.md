mamboMarket
===========


Prerequisites
=============

### BOOST
	UBUNTU libboost-all-dev

### GIT
	UBUNTU git

### pkg-config
	sudo apt-get install pkg-config
	
### autoconf-archive
	sudo apt-get install autoconf-archive

### STL-TA
install stlta

Installation instructions
========================

	git clone https://scrappy73@bitbucket.org/scrappy73/mamboMarket.git
	cd mamboMarket
	autoreconf --install -force 
	./configure
	make
	

Usage
=====
Currently the program is run as follows
	
	./mambo aapl

aapl is a stock symbol