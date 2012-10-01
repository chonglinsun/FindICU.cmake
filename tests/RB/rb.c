#include <stdlib.h>

#include <unicode/putil.h>
#include <unicode/ures.h>
#include <unicode/ustdio.h>
#include <unicode/uclean.h>
#ifndef URES_COMMON
# include <unicode/udata.h>
#endif /* !URES_COMMON */

#ifndef URES_COMMON
const void U_IMPORT *rb_dat;
#endif /* !URES_COMMON */

int main(int argc, char **argv)
{
    int ret;
    int32_t msg_len;
    const UChar *msg;
    UErrorCode status;
    UResourceBundle *ures;
    UFILE *ustdout, *ustderr;
    const char *locale = "fr_FR";

    ures = NULL;
    ret = EXIT_FAILURE;
    status = U_ZERO_ERROR;
    ustdout = u_finit(stdout, NULL, NULL);
    ustderr = u_finit(stderr, NULL, NULL);

    if (2 == argc) {
        locale = argv[1];
    }

#ifdef URES_COMMON
    u_setDataDirectory(".");
#else
    udata_setAppData(URESNAME, &rb_dat, &status);
    if (U_FAILURE(status)) {
        u_fprintf(ustderr, "udata_setAppData failed: %s\n", u_errorName(status));
        goto end;
    }
#endif /* !URES_COMMON */

    ures = ures_open(URESNAME, locale, &status);
    if (U_FAILURE(status)) {
        u_fprintf(ustderr, "translation disabled: %s\n", u_errorName(status));
        goto end;
    } else {
        if (U_USING_DEFAULT_WARNING == status) {
            u_fprintf(ustderr, "default translation enabled\n");
        } else {
            u_fprintf(ustderr, "translation enabled: %s\n", ures_getLocaleByType(ures, ULOC_ACTUAL_LOCALE, &status));
        }
    }
    /* */
    msg = ures_getStringByKey(ures, "whoami", &msg_len, &status);
    if (U_FAILURE(status)) { /* U_MISSING_RESOURCE_ERROR */
        // TODO: "better"
        goto end;
    } else if (U_USING_DEFAULT_WARNING == status) {
        u_fprintf(ustderr, "[M] default translation used\n");
    } else if (U_USING_FALLBACK_WARNING == status) {
        /* on working tests you see that because resource bundle source has 'fr' as locale not 'fr_FR' */
        u_fprintf(ustderr, "[M] translation fallback\n");
    }
    u_fprintf(ustdout, "%S\n", msg);
    /* */
    ret = EXIT_SUCCESS;

end:
    if (NULL != ures) {
        ures_close(ures);
    }
    u_fclose(ustdout);
    u_fclose(ustderr);
    u_cleanup();

    return ret;
}
