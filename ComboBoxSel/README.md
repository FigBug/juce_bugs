# Date:

Oct 11, 2023

# JUCE version: 

* commit 86d496d424f5587756b856acf17a3d1bb6456ece (HEAD -> develop, origin/develop)
* Author: reuk <reuk@users.noreply.github.com>
* Date:   Tue Oct 10 20:17:35 2023 +0100

# Compiler:

 * XCode 15.0

# OS:

* Sonoma 14.0

# Description:

ComboBox selection does not work if the menu is over the macOS menu bar. `mainMenuTrackingBegan` is called which calls `PopupMenu::dismissAllActiveMenus();` before the `PopupMenu` has time to handle the mouse click.

# Code to reproduce:

https://github.com/FigBug/juce_bugs/tree/master/ComboBoxSel

# Video:

https://www.youtube.com/watch?v=28vx7HxY_oI

# Forum post:

https://forum.juce.com/t/br-combobox-selection-does-not-work-if-the-menu-has-to-scroll/58316