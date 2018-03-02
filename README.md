# Pwned Password 

Fun project to utilize awesome [';--have i been pwned?](https://haveibeenpwned.com/Passwords) Passwords API. It generates SHA1 hash for the password you provide as an argument and then grabs the range of hashes, basing on first 5 characters of the hash, from the service and checks if your hash is among them. So your password, nor its hash, never leaves your computer.

Usage is simple:

	password <password>

It'll print ***Your password is well known!*** if your password is in ';--have i been pwned? DB. Enjoy!

