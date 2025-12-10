/*
# After make urjtag successfuly
# dynamic:
# (Windows needs other dlls: libftdi1.dll libreadline8.dll libtermcap-0.dll libusb-1.0.dll libwinpthread-1.dll
# and liburjtag-0.dll)
libtool --mode=link gcc -o example example.c -I"../include" -L"../src/.libs" -lurjtag -lftdi1 -lusb-1.0 -lintl
# or
gcc -o example example.c -I"../include" -L"../src/.libs" -lurjtag -lftdi1 -lusb-1.0 -lintl

# static:
# (Windows needs other dlls: libftdi1.dll libreadline8.dll libtermcap-0.dll libusb-1.0.dll libwinpthread-1.dll
# But do not need liburjtag-0.dll)
libtool --mode=link gcc -static -o example example.c -I"../include" -L"../src/.libs" -lurjtag -lftdi1 -lusb-1.0 -lintl
# or (Windows do not needs other dll)
gcc -static -o example example.c -I"../include" -L"../src/.libs" -lurjtag -lftdi1 -lusb-1.0 -lintl -lreadline -lncurses
*/

#include <stdio.h>
#include <stdarg.h>
#include <urjtag/urjtag.h>
#include <urjtag/parse.h>


static int stderr_vprintf (const char *fmt, va_list ap);
static int stdout_vprintf (const char *fmt, va_list ap);

static int
stderr_vprintf(const char *fmt, va_list ap)
{
    printf("### HELLO URJTAG ###\r\n");
    return vfprintf (stderr, fmt, ap);
}

static int
stdout_vprintf(const char *fmt, va_list ap)
{
    printf("### HELLO URJTAG ###\r\n");
    int r = vfprintf (stdout, fmt, ap);

    fflush (stdout);

    return r;
}

int main()
{
    int r = 0;
    urj_chain_t *chain = NULL;
    chain = urj_tap_chain_alloc ();
    if (!chain)
    {
        printf ("Out of memory\r\n");
        return -1;
    }

    printf ("urj_tap_chain_alloc r = %d\r\n", r);
    
    urj_log_state.level = URJ_LOG_LEVEL_DETAIL;
    urj_log_state.err_vprintf = stderr_vprintf; // redirect to your function
    urj_log_state.out_vprintf = stdout_vprintf; // redirect to your function
    
   
    char *params[5];
    params[0] = "pid=0x6010";
    params[1] = "vid=0x403";
    params[2] = "interface=1";
    params[3] = "driver=ftdi-mpsse";
    params[4] = NULL;

    r = urj_tap_chain_connect(chain, "ft2232", params);
    printf ("urj_tap_chain_connect r = %d\r\n", r);

     // use cmd: detect
    
    // 1st method
    
    r = urj_parse_line(chain, "detect");
    printf ("urj_parse_line r = %d\r\n", r);
    if (r == URJ_STATUS_FAIL)
            urj_log_error_describe (URJ_LOG_LEVEL_ERROR);

    // 2nd method
   
    //params[0] = "detect";
    //params[1] = NULL;
    //r = urj_cmd_run(chain, params);
    //printf ("urj_cmd_run r = %d\r\n", r);

    // 3rd method
    
    //r = urj_tap_detect(chain, 0);
    //printf ("urj_tap_detect r = %d\r\n", r);
    
    urj_tap_chain_free (chain);
    return 0;
}