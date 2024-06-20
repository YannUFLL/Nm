# Utiliser l'image Ubuntu comme base
FROM ubuntu:20.04

# Préconfigurer le fuseau horaire pour éviter l'interaction utilisateur
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC

# Mettre à jour le cache des paquets et installer openssh, sudo, wget, tar et autres outils nécessaires
RUN apt-get update && apt-get install -y \
    tzdata \
    openssh-server \
    sudo \
    wget \
    tar \
    build-essential \
	git-all

# Générer les clés SSH
RUN ssh-keygen -A

# Ajouter un utilisateur pour SSH (par exemple, 'devuser' avec le mot de passe 'password')
RUN useradd -ms /bin/bash devuser && echo "devuser:password" | chpasswd && usermod -aG sudo devuser

# Configurer sudo pour l'utilisateur
RUN echo '%sudo ALL=(ALL) NOPASSWD: ALL' > /etc/sudoers.d/99_sudo

# Copier les fichiers sources
COPY nm /home/devuser/nm

# Copier le fichier de configuration SSH
COPY sshd_config /etc/ssh/sshd_config

# Créer le répertoire /run/sshd
RUN mkdir -p /run/sshd

# Télécharger et extraire le serveur VS Code
RUN wget -O vscode-server.tar.gz https://update.code.visualstudio.com/latest/server-linux-x64/stable \
    && mkdir -p /home/devuser/.vscode-server/bin/8b3775030ed1a69b13e4f4c628c612102e30a681 \
    && tar -xzvf vscode-server.tar.gz -C /home/devuser/.vscode-server/bin/8b3775030ed1a69b13e4f4c628c612102e30a681/ \
    && rm vscode-server.tar.gz

# Changer les permissions pour l'utilisateur devuser
RUN chown -R devuser:devuser /home/devuser/.vscode-server

RUN git config --global user.name "YannUFLL"
RUN git config --global user.mail "yannlescoul79@free.fr"

# Exposer le port 22 pour SSH
EXPOSE 22


# Commande pour démarrer le service SSH
CMD ["/usr/sbin/sshd", "-D"]

