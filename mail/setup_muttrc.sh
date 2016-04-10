if [ $# -eq 4 ] ; then

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

cp $OUTPUT ~/

else
		echo "Usage: {SMTP_URL} {SMTP_PORT} {YOUR_EMAIL} {YOUR_PASSWORD}"

		echo "Ex)"
		echo ">gmail"
		echo "SMTP_URL : smtp://{YOUR_ID}@smtp.gmail.com"
		echo "SMTP_PORT : 587"

		exit 1
fi

echo setting for muttrc...
echo SMTP_URL    : $1
echo SMTP_PORT   : $2
echo YOUR_EMAIL  : $3
echo YOUR_PASSWD : $4
echo ""
echo "OK"
