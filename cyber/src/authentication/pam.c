#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <stdio.h>

static struct pam_conv conv = 
{
    misc_conv,
    NULL
};

int main(int argc, char *argv[])
{
    pam_handle_t *pamh = NULL;
    int retval;
    const char *user="shlomi";

   

    retval = pam_start("shlomi_auth", user, &conv, &pamh);

    if (retval == PAM_SUCCESS)
        retval = pam_authenticate(pamh, 0);    


    /* This is where we have been authorized or not. */

    if (retval == PAM_SUCCESS)
     {
        fprintf(stdout, "Authenticated\n");
     }
     else 
     {
        fprintf(stdout, "Not Authenticated\n");
     }

     if (pam_end(pamh, retval) != PAM_SUCCESS) 
     {    
         /* close Linux-PAM */
         pamh = NULL;
         fprintf(stderr, "shlomi_auth: failed to release authenticator\n");
         exit(1);
     }

    return 0;       
}


/*
auth required pam_listfile.so onerr=fail item=group sense=allow file=/etc/group.cyber
#
# /etc/pam.d/common-auth - authentication settings common to all services
#
# This file is included from other service-specific PAM config files,
# and should contain a list of the authentication modules that define
# the central authentication scheme for use on the system
# (e.g., /etc/shadow, LDAP, Kerberos, etc.).  The default is to use the
# traditional Unix authentication mechanisms.
#
# As of pam 1.0.1-6, this file is managed by pam-auth-update by default.
# To take advantage of this, it is recommended that you configure any
# local modules either before or after the default block, and use
# pam-auth-update to manage selection of other modules.  See
# pam-auth-update(8) for details.

# here are the per-package modules (the "Primary" block)
auth    [success=2 default=ignore]      pam_unix.so nullok
auth    [success=1 default=ignore]      pam_sss.so use_first_pass
# here's the fallback if no module succeeds
auth    requisite                       pam_deny.so
# prime the stack with a positive return value if there isn't one already;
# this avoids us returning an error just because nothing sets a success code
# since the modules above will each just jump around
auth    required                        pam_permit.so
# and here are more per-package modules (the "Additional" block)
auth    optional                        pam_cap.so
# end of pam-auth-update config
  auth       required     pam_unix.so
*/




















