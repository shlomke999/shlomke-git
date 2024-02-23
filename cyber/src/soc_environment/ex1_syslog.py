# ex1 - program that writes to syslog, forward all logs with severity higher than warning to a remote server
# first we configure syslog config file for the client and the server (look at this guide: https://linuxhint.com/syslog-tutorial/)
# then run this script on the client to send logs to the server.

from logging import getLogger, Formatter
import logging.handlers

def define_logging(server_ip):
    # Make the desired format string for Syslog
    LOG_FORMAT = f"%(levelname)s:%(filename)s:%(lineno)d - %(process)d - %(asctime)s - %(message)s"


    # Get the root logger
    logger = getLogger()

    syslogHandler = logging.handlers.SysLogHandler(address=(server_ip,514))

    # only send logs for warning and above:
    logger.setLevel(logging.WARNING)

    # Set the format string for the handler
    syslogHandler.setFormatter(Formatter(LOG_FORMAT))

    logger.addHandler(syslogHandler)
    logger.info("Configuring logger")
    logger.info("Logging configured!")



define_logging("10.1.0.116")
logging.warning('oy tate1')
logging.warning('oy tate2')
logging.warning('oy tate3')
logging.info('oy vey')
