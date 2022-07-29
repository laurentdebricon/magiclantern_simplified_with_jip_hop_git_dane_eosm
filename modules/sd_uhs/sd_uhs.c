/**
 * Experimental SD UHS overclocking.
 */

#include <module.h>
#include <dryos.h>
#include <patch.h>
#include <console.h>
#include <config.h>
#include <lens.h>

/* camera-specific parameters */
static uint32_t sd_setup_mode = 0;
static uint32_t sd_setup_mode_in = 0;
static uint32_t sd_setup_mode_reg = 0xFFFFFFFF;
static uint32_t sd_set_function = 0;

static uint32_t uhs_regs[]     = { 0xC0400600, 0xC0400604,/*C0400608, C040060C*/0xC0400610, 0xC0400614, 0xC0400618, 0xC0400624, 0xC0400628, 0xC040061C, 0xC0400620 };   /* register addresses */
static uint32_t sdr_160MHz[]   = {        0x2,        0x2,                             0x1, 0x1D000001,        0x0,      0x100,      0x100,      0x100,        0x1 };   /* overclocked values: 160MHz = 96*(4+1)/(2?+1) (found by brute-forcing) */
static uint32_t sdr_192MHz[]   = {        0x8,        0x3,                             0x4, 0x1D000301,        0x0,      0x201,      0x201,      0x100,        0x4 };
static uint32_t sdr_240MHz[]   = {        0x8,        0x3,                             0x3, 0x1D000301,        0x0,      0x201,      0x201,      0x100,        0x3 };

static uint32_t uhs_vals[COUNT(uhs_regs)];  /* current values */
static int sd_setup_mode_enable = 0;
static CONFIG_INT("sd.sd_overclock", sd_overclock, 2);

/* start of the function */
static void sd_setup_mode_log(uint32_t* regs, uint32_t* stack, uint32_t pc)
{
    qprintf("sd_setup_mode(dev=%x)\n", regs[0]);
    
    /* this function is also used for other interfaces, such as serial flash */
    /* only enable overriding when called with dev=1 */
    sd_setup_mode_enable = (regs[0] == 1);
}

/* called right before the case switch in sd_setup_mode (not at the start of the function!) */
static void sd_setup_mode_in_log(uint32_t* regs, uint32_t* stack, uint32_t pc)
{
    qprintf("sd_setup_mode switch(mode=%x) en=%d\n", regs[sd_setup_mode_reg], sd_setup_mode_enable);
    
    if (sd_setup_mode_enable && regs[sd_setup_mode_reg] == 4)   /* SDR50? */
    {
        /* set our register overrides */
        for (int i = 0; i < COUNT(uhs_regs); i++)
        {
            MEM(uhs_regs[i]) = uhs_vals[i];
        }
        
        /* set some invalid mode to bypass the case switch
         * and keep our register values only */
        regs[sd_setup_mode_reg] = 0x13;
    }
}

static void sd_overclock_task()
{
    
    /* install the hack */
    if (sd_overclock == 1) memcpy(uhs_vals, sdr_160MHz, sizeof(uhs_vals));
    if (sd_overclock == 2) memcpy(uhs_vals, sdr_192MHz, sizeof(uhs_vals));
    if (sd_overclock == 3) memcpy(uhs_vals, sdr_240MHz, sizeof(uhs_vals));
    patch_hook_function(sd_setup_mode, MEM(sd_setup_mode), sd_setup_mode_log, "SD UHS");
    patch_hook_function(sd_setup_mode_in, MEM(sd_setup_mode_in), sd_setup_mode_in_log, "SD UHS");

}

static struct menu_entry sd_uhs_menu[] =
{
    {
        .name   = "sd overclock",
        .priv   = &sd_overclock,
        .max    = 3,
        .choices = CHOICES("OFF", "160MHz", "192MHz", "240MHz(feeling lucky)"),
        .help   = "Select a patch and restart camera. Disable with OFF and restart",
        .help2  = "Proven working with 95Mb/s and 170Mb/s cards",
    }
};

static struct menu_entry sd_uhs_menu1[] =
{
    {
        .name   = "sd overclock",
        .priv   = &sd_overclock,
        .max    = 3,
        .choices = CHOICES("OFF", "160MHz", "192MHz", "240MHz (feeling lucky)"),
        .help   = "Select a patch and restart camera. Disable with OFF and restart",
        .help2  = "Proven working with 95Mb/s and 170Mb/s cards",
    }
};

static unsigned int sd_uhs_init()
{
    
    //needed with manual lenses cause it stalls liveview. Maybe helps for cams like 6D. To be tested.
    while (is_movie_mode() && !lv)
    {
        msleep(100);
    }
    
    if (is_camera("EOSM", "2.0.2"))
    {
        sd_setup_mode       = 0xFF338D40;
        sd_setup_mode_in    = 0xFF338DC8;
        sd_setup_mode_reg   = 1;
        sd_set_function     = 0xFF63EF60;
        if (sd_overclock)
        {
            sd_overclock_task();
        }
    }
    
    menu_add("Movie", sd_uhs_menu, COUNT(sd_uhs_menu));
    menu_add("Debug", sd_uhs_menu1, COUNT(sd_uhs_menu1));
    
    return 0;
}

static unsigned int sd_uhs_deinit()
{
    return 0;
}

MODULE_INFO_START()
MODULE_INIT(sd_uhs_init)
MODULE_DEINIT(sd_uhs_deinit)
MODULE_INFO_END()

MODULE_CONFIGS_START()
MODULE_CONFIG(sd_overclock)
MODULE_CONFIGS_END()


