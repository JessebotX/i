build:
	./compile

upload:
	rsync -rtvzP pub/ web@usernamesystems.xyz:/var/www/website
