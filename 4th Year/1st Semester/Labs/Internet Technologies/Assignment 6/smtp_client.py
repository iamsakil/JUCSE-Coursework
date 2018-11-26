import smtplib
import email.utils
from email.mime.text import MIMEText
import getpass

username = 'tst9928@gmail.com'
password = 'testing1;'
server = smtplib.SMTP('smtp.gmail.com:587')
server.ehlo()
server.starttls()
server.login(username,password)

# Create the message
msg = MIMEText(input("Body : "))
msg['To'] = email.utils.formataddr(('Recipient', input("To : ")))
msg['From'] = email.utils.formataddr(('Author', username))
msg['Subject'] = input("Subject : ")


try:
    server.sendmail(username, [msg['To']], msg.as_string())
finally:
    server.quit()
