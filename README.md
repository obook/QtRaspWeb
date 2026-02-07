# QtRaspWeb

Navigateur web plein écran conçu pour l'affichage de type kiosque sur Raspberry Pi. Idéal pour la signalisation numérique, les présentations et les écrans d'information.

## Fonctionnalités

- Affichage plein écran automatique au démarrage
- Rafraîchissement automatique de la page toutes les 30 minutes
- Reconnexion automatique en cas d'erreur réseau (toutes les 10 secondes)
- Curseur de souris masqué pour un affichage épuré
- Fermeture via la touche **Echap**
- URL configurable via fichier `ADMoovQt.json` ou argument de ligne de commande

## Installation rapide (Raspberry Pi 5 - PiOS Bookworm)

Le script `setup.sh` vérifie les dépendances, les installe si nécessaire et compile l'application :

```bash
./setup.sh
```

Le binaire est généré dans `src/build/ADMoovPiQt`.

## Installation manuelle

### Prérequis

- Qt 6 avec les modules : `core`, `gui`, `widgets`, `webenginewidgets`
- Compilateur C++17
- qmake6

Sur Debian Bookworm / Raspberry Pi OS :

```bash
sudo apt install build-essential qt6-base-dev qt6-webengine-dev
```

### Compilation

```bash
cd src
mkdir -p build && cd build
qmake6 ../ADMoovPiQt.pro
make -j$(nproc)
```

### Installation système

```bash
sudo make install
```

Installe le binaire dans `/opt/ADMoovPiQt/bin/`.

## Utilisation

L'application charge l'URL depuis le fichier `ADMoovQt.json` situé dans le même répertoire que le binaire. Si ce fichier n'existe pas, il est créé automatiquement avec l'URL par défaut.

```json
{
    "URL": "https://www.google.fr"
}
```

Un argument en ligne de commande surcharge l'URL du fichier JSON :

```bash
./ADMoovPiQt [URL]
```

## Comportement

| Paramètre | Valeur |
|---|---|
| Mode d'affichage | Plein écran |
| Rafraîchissement en cas de succès | 30 minutes |
| Rafraîchissement en cas d'erreur | 10 secondes |
| Délai initial avant chargement | 5 secondes |
| Touche de fermeture | Echap |

## Structure du projet

```
src/
  ADMoovPiQt.pro   # Configuration qmake
  main.cpp          # Point d'entrée
  mainwindow.h      # En-tête de la fenêtre principale
  mainwindow.cpp    # Implémentation de la fenêtre principale
  mainwindow.ui     # Interface Qt Designer
```

## Licence

Ce projet est distribué sous licence [GNU General Public License v3](LICENSE).
