# Date:

Oct 17th, 2019

# Description:

If the message queue on windows is full, then ActionBroadcaster::sendActionMessage silently fails, and then message is lost. Could we at minimum get an assert, and a return value from ActionBroadcaster::sendActionMessage or best case somehow delay and retry later.

# Forum

https://forum.juce.com/t/actionbroadcaster-sendactionmessage-silently-fails/35748

# Status

Fixed in https://github.com/juce-framework/JUCE/commit/ce9bb8b60549b42756580094253aa4c770624800