# Projet: Gestion de comptes bancaires

## Description
Ce projet implémente un système simple de gestion de comptes bancaires en utilisant les protocoles TCP et UDP. Le système permet aux clients d'effectuer des opérations telles que l'ajout de fonds, le retrait de fonds, la vérification du solde et la consultation des 10 dernières opérations sur leurs comptes.

## Fichiers
- `TCP/server_tcp.c` : Implémentation du serveur TCP
- `TCP/client_tcp.c` : Implémentation du client TCP
- `UDP/server_udp.c` : Implémentation du serveur UDP
- `UDP/client_udp.c` : Implémentation du client UDP
- `Makefile` : Fichier de compilation

## Prérequis
- Compilateur GCC

## Compilation

1. **Ouvrez un terminal.**
2. **Naviguez jusqu'au répertoire racine du projet contenant le `Makefile`.**
3. **Compilez tous les fichiers TCP et UDP :**
    ```bash
    make all
    ```
4. **Pour compiler uniquement les fichiers TCP :**
    ```bash
    make tcp
    ```
5. **Pour compiler uniquement les fichiers UDP :**
    ```bash
    make udp
    ```

## Exécution

### Version TCP
1. **Ouvrez un terminal.**
2. **Naviguez jusqu'au répertoire contenant le serveur TCP compilé.**
3. **Démarrez le serveur TCP :**
    ```bash
    ./server_tcp
    ```
4. **Ouvrez un autre terminal.**
5. **Naviguez jusqu'au répertoire contenant le client TCP compilé.**
6. **Démarrez le client TCP :**
    ```bash
    ./client_tcp
    ```

### Version UDP
1. **Ouvrez un terminal.**
2. **Naviguez jusqu'au répertoire contenant le serveur UDP compilé.**
3. **Démarrez le serveur UDP :**
    ```bash
    ./server_udp
    ```
4. **Ouvrez un autre terminal.**
5. **Naviguez jusqu'au répertoire contenant le client UDP compilé.**
6. **Démarrez le client UDP :**
    ```bash
    ./client_udp
    ```

## Utilisation
1. Une fois que le client est prêt à communiquer avec le serveur, vous pouvez entrer des commandes dans le terminal du client pour effectuer diverses opérations.
2. Commandes disponibles :
    - `AJOUT <id_client> <id_compte> <password> <montant>` : Ajouter des fonds au compte.
    - `RETRAIT <id_client> <id_compte> <password> <montant>` : Retirer des fonds du compte.
    - `SOLDE <id_client> <id_compte> <password>` : Vérifier le solde du compte.
    - `OPERATIONS <id_client> <id_compte> <password>` : Consulter les 10 dernières opérations sur le compte.
3. Pour quitter le client, tapez `exit`.

### Exemples de commandes
- `AJOUT Inessa 123 pass1 100.0`
- `RETRAIT Philip 456 pass2 50.0`
- `SOLDE Marie 789 pass3`
- `OPERATIONS Inessa 123 pass1`