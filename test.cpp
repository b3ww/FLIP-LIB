#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
// #include "String.hpp"
#include <string>

int main() {
    // Adresse IP et port du serveur
    const char *serverIP = "127.0.0.1"; // Adresse IP locale
    int serverPort = 4241;

    // Création du socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Erreur lors de la création du socket" << std::endl;
        return 1;
    }

    // Préparation de l'adresse du serveur
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(serverIP);
    serverAddr.sin_port = htons(serverPort);

    // Connexion au serveur
    if (connect(clientSocket, reinterpret_cast<struct sockaddr *>(&serverAddr), sizeof(serverAddr)) < 0) {
        std::cerr << "Erreur lors de la connexion au serveur" << std::endl;
        close(clientSocket);
        return 1;
    }

    // Chaîne de caractères à envoyer
    std::string a("coucou");
    const char *message = "Hello, server!";

    // Envoi de la chaîne de caractères au serveur
    if (send(clientSocket, a.data(), a.length(), 0) < 0) {
        std::cerr << "Erreur lors de l'envoi du message" << std::endl;
        close(clientSocket);
        return 1;
    }

    std::cout << "Message envoyé avec succès au serveur" << std::endl;

    // Fermeture du socket
    close(clientSocket);

    return 0;
}
