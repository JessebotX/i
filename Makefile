build:
	./compile

upload:
	rsync -rtvzP pub/ root@usernamesystems.xyz:/var/www/usernamesystems.xyz
