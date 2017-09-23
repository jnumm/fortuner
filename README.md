ABOUT
------
Fortuner shows a fortune as a notification. Requires the fortune
program, CMake, and Qt5.

INSTALLATION
-------------
1. Install the requirements
   An example for Debian GNU/Linux:

        # apt-get install fortune-mod cmake qtbase5-dev

2. Clone the repository (get sources) if you haven’t already

        $ git clone https://github.com/jnumm/fortuner.git

3. Build the program

        $ cd fortuner
        $ mkdir build && cd build
        $ cmake ..
        $ make

3. Now you can run Fortuner:

        $ ./fortuner

4. To install the package into /usr/local:

        # make install

BUGS
-----
Please report bugs to https://github.com/jnumm/fortuner/issues.

LICENSE
--------
Fortuner source code is licensed under GNU GPL v3+ (see COPYING).

Fortuner icons are licensed under CC BY 3.0.
