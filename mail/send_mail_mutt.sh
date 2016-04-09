if [ $# -eq 3 ] ; then
mutt -s "Raspberry pi" -a $3 -- $1 < $2
elif [ $# -eq 2 ] ; then
mutt -s "Raspberry pi" $1 < $2
else
	echo "Usage 1: ./send_mail.sh {Recipient} {Message text} "
	echo "Usage 2: ./send_mail.sh {Recipient} {Message text} {Attachment file}"
fi


