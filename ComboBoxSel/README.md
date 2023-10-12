JUCE version: 

* commit 86d496d424f5587756b856acf17a3d1bb6456ece (HEAD -> develop, origin/develop)
* Author: reuk <reuk@users.noreply.github.com>
* Date:   Tue Oct 10 20:17:35 2023 +0100

Compiler:

 * XCode 15.0

OS:

* Sonoma 14.0

Description:

ComboBox selection does not work if the menu has to scroll all the way to the top. If user goes from last entry to first, it will not work. If they go from last entry to somewhere in the middle, and then from middle to first, it will work.

* Video:

https://www.youtube.com/watch?v=28vx7HxY_oI

* Forum post:

https://forum.juce.com/t/br-combobox-selection-does-not-work-if-the-menu-has-to-scroll/58316