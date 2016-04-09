

if [ $# -eq 0 ] ; then
	echo "You need parameters"
	exit 1
elif [ $# -eq 4 ] ; then

OUTPUT=.muttrc
echo "###" > $OUTPUT
echo "# User info" >> $OUTPUT
echo "###" >> $OUTPUT
echo "" >> $OUTPUT
echo "set ssl_starttls=yes" >> $OUTPUT
echo "set ssl_force_tls=yes" >> $OUTPUT
echo "" >> $OUTPUT
echo "set realname=$3" >> $OUTPUT
#echo "set from=$3" >> $OUTPUT
#echo "set use_from=yes" >> $OUTPUT
echo "" >> $OUTPUT
echo "set smtp_url=$1:$2" >> $OUTPUT
echo "set smtp_pass=$4" >> $OUTPUT

else
		echo "Usage: {SMTP_URL} {SMTP_PORT} {FROM_EMAIL} {PASSWD}"

		echo "Ex)"
		echo ">gmail"
		echo "SMTP_URL : smtp://{YOUR_ID}@smtp.gmail.com"
		echo "SMTP_PORT : 587"

		exit 1
fi

echo setting for email...



