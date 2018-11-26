import poplib
import email
import getpass

pop_conn = poplib.POP3_SSL('pop.gmail.com', 995)
#pop_conn.user(input("insert Email : "))
#pop_conn.pass_(getpass.getpass("password : "))
pop_conn.user('tst9928@gmail.com')
pop_conn.pass_('testing1;')

print(pop_conn.stat())
print(pop_conn.list())
print ("")

if pop_conn.stat()[1] > 0:
    print ("You have new mail.")
else:
    print ("No new mail.")
print ("")

numMessages = len(pop_conn.list()[1])
for i in range(numMessages):
    for j in pop_conn.retr(i+1)[1]:
        #print (j)
        if j.startswith(b'Subject'):
            print(j)
        msg = email.message_from_string(j.decode("utf-8"))
        strtext=msg.get_payload()
        print (strtext)
        

pop_conn.quit()
input("Press any key to continue.")
