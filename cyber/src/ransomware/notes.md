1. Generate Private Key:  openssl genrsa
2. put the generated key in a file private.pem
3.  Derive Public Key from the private:  openssl rsa -in private.pem -pubout -out public.pem

4. Generating a symmetric key: openssl enc -pbkdf2 -aes-128-ecb -k my-secret-passphrase -P
5. put the key in a file sym_key.pem
6. encrypt file with the symetric key:    openssl enc -aes-128-ecb -in cleartext.txt -K $(cat sym_key.pem) -out ciphertext.txt
7. (to decrypt with that symetric key run:  openssl enc -d -aes-128-ecb -in ciphertext.txt -K $(cat sym_key.pem))

8. encrypt the symetric key with the public key from stage 3:   openssl pkeyutl -encrypt -inkey public.pem -pubin -in sym_key.pem -out sym_key.enc
9. decrypt the symetric key with the private key:   openssl pkeyutl -decrypt -inkey private.pem -in sym_key.enc -out sym_key.pem

10. now we can use the symetric key to decrypt the encrypted file like we did in stage 7.


