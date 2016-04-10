MUTTRC=.muttrc

if [ $# -lt 2 ] ; then
	echo "Usage 1: ./send_mail.sh {Recipient} {Message text} "
	echo "Usage 2: ./send_mail.sh {Recipient} {Message text} {Attached file 1} {Attached file 2} ..."
elif [ $# -eq 2 ] ; then
mutt -s "Raspberry pi" $1 < $2
elif [ $# -gt 2 ] ; then

RECIPIENT=""
MAILBODY=""
ATTACHED_FILES=""
for var in "$@"
do
	if [ "$RECIPIENT" == "" ] ; then
	RECIPIENT=$var
	elif [ "$MAILBODY" == "" ] ; then
	MAILBODY=$var
	else
	ATTACHED_FILES+=" "
	ATTACHED_FILES+=$var
	fi
done

	echo Recipient : $RECIPIENT
	echo mail body : $MAILBODY
	echo attached files : $ATTACHED_FILES

	if [ -f $MUTTRC ] ; then
	mutt -F .muttrc -s "Raspberry pi" -a $ATTACHED_FILES -- $RECIPIENT < $MAILBODY
	else
	mutt -s "Raspberry pi" -a $ATTACHED_FILES -- $RECIPIENT < $MAILBODY
	fi

fi


