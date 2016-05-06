# -*- coding: UTF-8 -*-
#!/usr/bin/python

import smtplib
from email.mime.text import MIMEText

def send_email(*args):
    E = args[0]
    P = args[1]
    Q = args[2]
    x = args[3]
    nbits = args[4]
    time = args[5]
    algorithm = args[6]
    nthreads = args[7]

    rodrigo = 'rodrigosg2000@gmail.com'
    carlos = 'carlostjunior517@gmail.com'

    sender = rodrigo
    receivers = [rodrigo, carlos]

    msg = MIMEText(
        "Algoritmo: " + algorithm + "\n"
        "Threads = " + str(nthreads) + "\n"
        "Bits = " + str(nbits) + " bits\n"
        "E = "+ str(E) + "\n"
        "P: " + str(P) + "\n"
        "Q: " + str(Q) + "\n"
        "x = " + str(x) + "\n"
        "Tempo de execução: " + format_time(time))
    msg['Subject'] = "Quebra da curva de " + str(nbits) + " bits"
    msg['From'] = "Rodrigo Gonçalves " + sender
    msg['To'] = ", ".join(receivers)

    ### "Safety" lock ###
    return

    try:
        s = smtplib.SMTP('smtp.gmail.com', 587)
        # s.set_debuglevel(1)
        s.ehlo()
        s.starttls()
        s.login(sender, "Irodrigo10.")
        s.sendmail(sender, receivers, msg.as_string())
        s.quit()
        print "Successfully sent email"
    except smtplib.SMTPException:
        print "Error: unable to send email"

def format_time(time):
    minute = 60
    hour = 60*minute
    day = 24*hour

    d = int(time//day)
    h = int(time - d*day)//hour
    m = int(time - d*day - h*hour)//minute
    s = int(time - d*day - h*hour - m*minute)
    return str(d) + "d " + str(h) + "h " + str(m) + "m " + str(s) + "s"
