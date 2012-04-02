/*
 * fortuner
 * Copyright (C) 2012 Juhani Numminen <juhaninumminen0@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Settings
{
    int timeout;
};

void load_settings (Settings& settings, string filename)
{
    ifstream fin (filename.c_str ());
    if (fin.is_open ())
    {
        string line;
        while (getline (fin, line))
        {
            istringstream sin (line.substr (line.find("=") + 1));
            if (line.find ("timeout") != -1)
            {
                sin >> settings.timeout;
            }
        }
    }
    else
    {
        cout<<"Not able to open configuration file."<<endl;
        
        settings.timeout = 10;
    }
}
