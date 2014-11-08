/*
---------------------------------------------------------------------------------------------------------------------------------------
(C)2013 Thomas AUGUEY <contact@aceteam.org>
---------------------------------------------------------------------------------------------------------------------------------------
This file is part of Arduino Project (AceTeaM).

This code is free: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with WebFrameWork.  If not, see <http://www.gnu.org/licenses/>.
---------------------------------------------------------------------------------------------------------------------------------------
*/

// Librairie 'Serveur'
#include "Serveur.h"
#include "SwitchObjet.h"
// Librairie Additionnelles
#include "LedStripEquipement.h"

LedStripEquipement equip;

void setup() {
     equip.Initialise();
}

void loop() {
    equip.Periode();
    delay(100);
}

