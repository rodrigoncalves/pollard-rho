# -*- coding: UTF-8 -*-
#!/usr/bin/python

import smtplib

def send_email(msg):
    rodrigo = 'rodrigosg2000@gmail.com'
    carlos = 'carlostjunior517@gmail.com'

    sender = rodrigo
    receivers = [rodrigo, carlos]

    msg['From'] = 'Rodrigo Gonçalves ' + sender
    msg['To'] = ', '.join(receivers)

    try:
        s = smtplib.SMTP('smtp.gmail.com', 587)
        # s.set_debuglevel(1)
        s.ehlo()
        s.starttls()
        s.login(sender, '')
        s.sendmail(sender, receivers, msg.as_string())
        s.quit()
        print 'Successfully sent email'
    except smtplib.SMTPException:
        print 'Error: Unable to send email'

def format_time(time):
    minute = 60
    hour = 60*minute
    day = 24*hour
    month = 30*day
    year = 12*month
    y = int(time//year)
    mo = int(time - y*year) // month
    d = int(time - y*year - mo*month) // day
    h = int(time - y*year - mo*month - d*day) // hour
    mi = int(time - y*year - mo*month - d*day - h*hour) // minute
    s = int(time - y*year - mo*month - d*day - h*hour - mi*minute)
    return '%dy %dm %dd %dh %dm %ds' % (y, mo, d, h, mi, s)
