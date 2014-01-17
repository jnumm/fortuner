ABOUT
------
Fortuner shows a fortune as a notification. Requires the fortune
program, libnotify and gtkmm 3.

INSTALLATION
-------------
1) Install the requirements
   An example for Debian GNU/Linux:
   # apt-get install libgtkmm-3.0-dev fortune-mod libnotify-dev

2) Clone the repository (get sources) if you haven’t already
   $ git clone https://github.com/jnumm/fortuner.git

3) Build the program
   $ cd fortuner
   $ ./autogen.sh
   $ ./configure
   $ make

3) Now you can run Fortuner:
   $ src/fortuner

4) To install the package:
   # make install

BUGS
-----
Please report bugs to https://github.com/jnumm/fortuner/issues.

LICENSE
--------
Fortuner source code is licensed under GNU GPL v3+ (see COPYING).

Fortuner icons are licensed under CC BY 3.0.
