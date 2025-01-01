# Projet: Gestion de comptes bancaires

## Description
Ce projet implémente un système simple de gestion de comptes bancaires en utilisant les protocoles TCP et UDP. Le système permet aux clients d'effectuer des opérations telles que l'ajout de fonds, le retrait de fonds, la vérification du solde et la consultation des 10 dernières opérations sur leurs comptes.

## Fichiers
- server_tcp.c : Implémentation du serveur TCP
- client_tcp.c : Implémentation du client TCP
- server_udp.c : Implémentation du serveur UDP
- client_udp.c : Implémentation du client UDP

## Prérequis
- Compilateur GCC
- Assurez-vous d'avoir les permissions nécessaires pour exécuter les commandes

## Compilation

### Version TCP
1. Ouvrez un terminal ou une invite de commande.
2. Naviguez jusqu'au répertoire contenant les fichiers source.
3. Compilez le serveur TCP :
   ```sh
   gcc -o server_tcp server_tcp.c