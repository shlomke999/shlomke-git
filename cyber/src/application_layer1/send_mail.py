import smtplib, ssl, email
from email import encoders
from email.mime.base import MIMEBase
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

#approved by afonin.
port = 465
context = ssl.create_default_context()
my_mail = "shpr251@gmail.com"
password = "agflgpmwqxztxrif"
to_mail = "israelliraz95@gmail.com"
subject = "ma kore mami?"
body = "i love you!."
message = MIMEMultipart()
message["From"] = my_mail
message["To"] = to_mail
message["Subject"] = subject
message["Bcc"] = "aaa798136@gmail.com"
message.attach(MIMEText(body, "plain"))
filename = "/home/shlomi/ll"
with open(filename, "rb") as file:
    part = MIMEBase("application", "octet-stream")
    part.set_payload(file.read())
encoders.encode_base64(part)
part.add_header("Content-Disposition", f"attachment; filename= {filename}")
message.attach(part)
text = message.as_string()
with smtplib.SMTP_SSL("smtp.gmail.com", port, context=context) as server:
    server.login(my_mail, password)
    server.sendmail(my_mail, to_mail, text)
