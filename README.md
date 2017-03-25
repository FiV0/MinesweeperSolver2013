## MINESWEEPER-SOLVER ##
	This progarm is used to solve the original Microsoft minesweeper
	game on linux machines. For more infos please refer to
	<http://www.minesweeper.info/wiki/Windows_Minesweeper> .

# LICENCE: #
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


# INSTALLATION: #
	For this program to compile correctly you need to have the
	following libraries installed:

	xdotool: <http://semicomplete.com/files/xdotool/>
	gtk2: <https://developer.gnome.org/gtk2/>
	openCV: <http://opencv.org/downloads.html>

	Please follow the instructions in the respective README's for
	installation of these libraries. Make sure to install the latest
	version of xdotool (2.20101014.3063 as of 26.5.2013), otherwise
	there might be errors while compiling.

# VERSIONS: #

	The makefile lets you choose between 4 versions:

	debug: Takes as input the path to a minesweeper configuration
		file, which can be found in the 'test' directory and tries
		to solve the configuration as far as possible with the
		specified functions. Please look at the 'test.c' sourcefile
		for more information.

	testing: Lets you play minesweeper at the comment line with help of
		logical solver. Takes as input the x and y dimensions of the
		minefield and the number of mines.

	version2: Helps you to solve the original Microsoft minesweeper
		from the commend line. Takes as input the x and y dimensions
		and the number of mines. The fourth input is the time in
		seconds between consecutive clicks generated by the program.
		We recommend to choose anything higher than 0.001 seconds,
		because otherwise the program receiving the clicks might
		crash. The final input is a charactar. Specify 'p' if you want
		the program to continue solving even if it is not sure
		about a mine location. Specify any other letter and the
		program only solves logically.

	finalversion: Essentially does the same thing as version2, but is
		easier to use because of a little graphical interface. Nothing
		has to be specified at the comment line.

	Important: So that the last 2 versions work correctly you need to make
		sure that the minefield is never concealed by any other window.

# AUTHORS: #
	Völkel,Finn