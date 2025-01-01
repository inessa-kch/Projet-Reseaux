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

## Compilation

1. Ouvrez un terminal.
2. Naviguez jusqu'au répertoire contenant les fichiers source.
3. Compilez tous les fichiers TCP et UDP :
    ```sh
    make all
    ```

## Exécution

### Version TCP
1. Ouvrez un terminal.
2. Naviguez jusqu'au répertoire contenant le serveur et le client TCP compilés.
3. Démarrez le serveur TCP :
    ./server_tcp

4. Ouvrez un autre terminal.
5. Naviguez jusqu'au répertoire contenant le client TCP compilé.
Démarrez le client TCP :
    ./client_tcp


### Version UDP
1. Ouvrez un terminal.
2. Naviguez jusqu'au répertoire contenant le serveur et le client UDP compilés.
3. Démarrez le serveur UDP :
    ./server_udp

4. Ouvrez un autre terminal.
5. Naviguez jusqu'au répertoire contenant le client UDP compilé.
Démarrez le client UDP :
    ./client_udp


## Utilisation
Une fois que le client est connecté au serveur, vous pouvez entrer des commandes dans le terminal du client pour effectuer diverses opérations.
Commandes disponibles :
AJOUT <id_client> <id_compte> <password> <montant> : Ajouter des fonds au compte.
RETRAIT <id_client> <id_compte> <password> <montant> : Retirer des fonds du compte.
SOLDE <id_client> <id_compte> <password> : Vérifier le solde du compte.
OPERATIONS <id_client> <id_compte> <password> : Consulter les 10 dernières opérations sur le compte.
Pour quitter le client, tapez exit.

### Exemples de commandes
AJOUT Inessa 123 pass1 100.0
RETRAIT Philip 456 pass2 50.0
SOLDE Marie 789 pass3
OPERATIONS Inessa 123 pass1