-- cinema 2.39:1  

-- Sets all parameters for anamorphic 2.39:1

lv.start()
lv.zoom = 1
console.hide()
menu.close()

-- end this script if not eosm/700d/100D/650D
if camera.model_short ~= "EOSM" and camera.model_short ~= "700D" and camera.model_short ~= "100D" and camera.model_short ~= "650D" and camera.model_short ~= "5D3" then
 display.notify_box("Script not working on this cam")
 menu.set("cinema 2:39.1", "Autorun", "OFF")
 msleep(2000)
 return
end

-- this script should never run on Autorun, menu.set not working so running menu.select instead
if menu.get("cinema 2.39:1", "Autorun", "") == "ON" then
 menu.select("Scripts", "cinema 2.39:1")
 menu.open()     -- open ML menu
 key.press(KEY.SET)
 key.press(KEY.WHEEL_DOWN)
 key.press(KEY.WHEEL_DOWN)
 key.press(KEY.SET)
 menu.close()
 display.notify_box("cinema Autorun is now disabled!")
 msleep(3000)
 return
end

-- warnings 
while camera.mode ~= MODE.MOVIE do
display.notify_box("enable MOVIE mode")
msleep(1000)
end

-- enable sound
menu.set("sound recording", "Enable sound", "ON")
if menu.get("sound recording", "Enable sound", "") ~= "ON" then
display.notify_box("enable mlv_snd.mo and mlv_lite.mo")
msleep(2000)
display.notify_box("enable mlv_snd.mo and mlv_lite.mo")
msleep(2000)
return
end

-- crop mode
if camera.model_short == "EOSM" then
  menu.set("Movie", "presets", "5K anamorphic")
end
if camera.model_short == "100D" then
  menu.set("Movie", "presets", "anamorphic rewired")
end
if camera.model_short == "5D3" then
  menu.set("Movie", "presets", "anamorphic")
end
  menu.set("Movie", "bitdepth", "10 bit")
  menu.set("Movie", "ratio", "2.39:1")
msleep(300)

-- enable crop_rec.mo. Checking first after trying to enable 5k preset
if menu.get("Movie", "presets", "") ~= "anamorphic" and menu.get("Movie", "presets", "") ~= "anamorphic rewired" and menu.get("Movie", "presets", "") ~= "5K anamorphic" then
display.notify_box("enable crop_rec.mo")
msleep(1000)
display.notify_box("enable crop_rec.mo")
msleep(1000)
return
end

-- movie
menu.set("Movie", "fps override", "OFF")
menu.set("raw video", "Crop rec preview", "auto mode")
menu.set("raw video", "Preview", "Framing")
menu.set("raw video", "Resolution Index", 11)
menu.set("Movie", "raw video", "ON")
menu.set("raw video", "Aspect ratio", "1:2")

-- Overlay
menu.set("Overlay", "Focus Peak", "OFF")
menu.set("Overlay", "Zebras", "OFF")
menu.set("Overlay", "Magic Zoom", "OFF")
menu.set("Overlay", "Cropmarks", "OFF")
menu.set("Overlay", "Spotmeter", "OFF")
menu.set("Overlay", "False color", "OFF")
menu.set("Overlay", "Histogram", "OFF")
menu.set("Overlay", "Waveform", "OFF")
menu.set("Overlay", "Vectorscope", "OFF")
menu.set("Display", "Clear overlays", "OFF")

-- done, turn on global draw
menu.set("Overlay", "Global Draw", "LiveView")

lv.pause()
lv.resume()

-- success!
if camera.model_short == "100D" then
 display.notify_box("anamorphic rewired is all set")
elseif camera.model_short == "5D3" then
 display.notify_box("5.5K anamorphic is all set")
else
 display.notify_box("5K anamorphic is all set")
end

