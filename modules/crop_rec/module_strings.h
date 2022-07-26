static char __module_string_a_name [] MODULE_STRINGS_SECTION = "Name";
static char __module_string_a_value[] MODULE_STRINGS_SECTION = "Crop mode recording";
static char __module_string_b_name [] MODULE_STRINGS_SECTION = "Author";
static char __module_string_b_value[] MODULE_STRINGS_SECTION = "a1ex";
static char __module_string_c_name [] MODULE_STRINGS_SECTION = "License";
static char __module_string_c_value[] MODULE_STRINGS_SECTION = "GPL";
static char __module_string_d_name [] MODULE_STRINGS_SECTION = "Summary";
static char __module_string_d_value[] MODULE_STRINGS_SECTION = "Turn the 1080p and 720p video modes into 1:1 sensor crop modes";
static char __module_string_e_name [] MODULE_STRINGS_SECTION = "Description";
static char __module_string_e_value[] MODULE_STRINGS_SECTION = 
    "This alters the 1080p and 720p video modes, transforming them\n"
    "into 3x (1:1) crop modes, by tweaking the sensor registers.\n"
    "\n"
    "All other behaviors are the same as with Canon's 1080p/720p\n"
    "implementation: resolution, H.264, RAW, audio, HDMI, preview,\n"
    "overlays and so on.\n"
    "\n"
;
static char __module_string_f_name [] MODULE_STRINGS_SECTION = "Last update";
static char __module_string_f_value[] MODULE_STRINGS_SECTION = 
    "e7f0ef4 on 2022-04-25 09:16:54 UTC by danne:\n"
    "crop_rec.c:(EOSM SET button added to customize buttons)\n"
;
static char __module_string_g_name [] MODULE_STRINGS_SECTION = "Build date";
static char __module_string_g_value[] MODULE_STRINGS_SECTION = "2022-04-25 09:22:24 UTC";
static char __module_string_h_name [] MODULE_STRINGS_SECTION = "Build user";
static char __module_string_h_value[] MODULE_STRINGS_SECTION = 
    "daniel@Daniels-MacBook-Pro.local\n"
    "\n"
;

#define MODULE_STRINGS() \
  MODULE_STRINGS_START() \
    MODULE_STRING(__module_string_a_name, __module_string_a_value) \
    MODULE_STRING(__module_string_b_name, __module_string_b_value) \
    MODULE_STRING(__module_string_c_name, __module_string_c_value) \
    MODULE_STRING(__module_string_d_name, __module_string_d_value) \
    MODULE_STRING(__module_string_e_name, __module_string_e_value) \
    MODULE_STRING(__module_string_f_name, __module_string_f_value) \
    MODULE_STRING(__module_string_g_name, __module_string_g_value) \
    MODULE_STRING(__module_string_h_name, __module_string_h_value) \
  MODULE_STRINGS_END()
