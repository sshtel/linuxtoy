if [ $# -eq 0 ] ; then
    echo "You need parameters"
	exit 1
elif [ $# -eq 4 ] ; then
echo "#" > ssmtp.conf
echo "# Config file for sSMTP sendmail" >> ssmtp.conf
echo "#" >> ssmtp.conf
echo "# The person who gets all mail for userids < 1000" >> ssmtp.conf
echo "# Make this empty to disable rewriting." >> ssmtp.conf
echo "root=" >> ssmtp.conf
echo "" >> ssmtp.conf
echo "# The place where the mail goes. The actual machine name is required no" >> ssmtp.conf
echo "# MX records are consulted. Commonly mailhosts are named mail.domain.com  " >> ssmtp.conf
echo "mailhub=$1:$2" >> ssmtp.conf
echo "" >> ssmtp.conf
echo "" >> ssmtp.conf
echo "AuthUser=$3" >> ssmtp.conf
echo "AuthPass=$4" >> ssmtp.conf
echo "AuthMethod=LOGIN" >> ssmtp.conf
echo "UseTLS=YES" >> ssmtp.conf
echo "UseSTARTTLS=YES" >> ssmtp.conf
echo "" >> ssmtp.conf
echo "# Where will the mail seem to come from?" >> ssmtp.conf
#echo "rewriteDomain=gmail.com" >> ssmtp.conf
echo "" >> ssmtp.conf
echo "# The full hostname" >> ssmtp.conf
echo "#hostname=" >> ssmtp.conf
echo "" >> ssmtp.conf
echo "# Are users allowed to set their own From: address?" >> ssmtp.conf
echo "# YES - Allow the user to specify their own From: address" >> ssmtp.conf
echo "# NO - Use the system generated From: address" >> ssmtp.conf
echo "FromLineOverride=YES" >> ssmtp.conf


sudo mv -f ./ssmtp.conf /etc/ssmtp/ssmtp.conf

else
    echo "Usage: {SMTP_URL} {SMTP_PORT} {EMAIL} {PASSWD}"

	echo "Ex)"
	echo ">gmail"
	echo "SMTP_URL : smtp.gmail.com"
	echo "SMTP_PORT : 587"
	exit 1
fi

echo setting for email...
