# Pwned Password 

Fun project to utilize awesome [';--have i been pwned?](https://haveibeenpwned.com/Passwords) Passwords API. It generates SHA1 hash for the password you provide as an argument and then grabs the range of hashes, basing on first 5 characters of the hash, from the service and checks if your hash is among them. So your password, nor its hash, never leaves your computer.

Usage is simple:

	./pwned <password>

It'll print ***This is how many times your password was pwned:*** and a number if your password is in ';--have i been pwned? DB, else it'll print ***Password not pwned!***. Enjoy!

You can find Windows 64-bit binary and necessary libs in *win* subfolder.

