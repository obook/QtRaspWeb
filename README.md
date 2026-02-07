# QtRaspWeb

Navigateur web plein ecran concu pour l'affichage de type kiosque sur Raspberry Pi. Ideal pour la signalisation numerique, les presentations et les ecrans d'information.

## Fonctionnalites

- Affichage plein ecran automatique au demarrage
- Rafraichissement automatique de la page toutes les 30 minutes
- Reconnexion automatique en cas d'erreur reseau (toutes les 10 secondes)
- Curseur de souris masque pour un affichage epure
- Fermeture via la touche **Echap**
- URL configurable en argument de ligne de commande

## Installation rapide (Raspberry Pi 5 - PiOS Bookworm)

Le script `setup.sh` verifie les dependances, les installe si necessaire et compile l'application :

```bash
./setup.sh
```

Le binaire est genere dans `src/build/ADMoovPiQt`.

## Installation manuelle

### Prerequis

- Qt 5 avec les modules : `core`, `gui`, `widgets`, `webkitwidgets`
- Compilateur C++11
- qmake

Sur Debian Bookworm / Raspberry Pi OS :

```bash
sudo apt install build-essential qtbase5-dev libqt5webkit5-dev
```

### Compilation

```bash
cd src
mkdir -p build && cd build
qmake ../$ADMoovPiQt.pro
make -j$(nproc)
```

### Installation systeme

```bash
sudo make install
```

Installe le binaire dans `/opt/ADMoovPiQt/bin/`.

## Utilisation

```bash
# URL par defaut (https://admoov.albertdemun.education/)
./ADMoovPiQt

# URL personnalisee
./ADMoovPiQt https://example.com
```

## Comportement

| Parametre | Valeur |
|---|---|
| Mode d'affichage | Plein ecran |
| Rafraichissement en cas de succes | 30 minutes |
| Rafraichissement en cas d'erreur | 10 secondes |
| Delai initial avant chargement | 5 secondes |
| Touche de fermeture | Echap |

## Structure du projet

```
src/
  ADMoovPiQt.pro   # Configuration qmake
  main.cpp          # Point d'entree
  mainwindow.h      # En-tete de la fenetre principale
  mainwindow.cpp    # Implementation de la fenetre principale
  mainwindow.ui     # Interface Qt Designer
```

## Licence

Ce projet est distribue sous licence [GNU General Public License v3](LICENSE).
