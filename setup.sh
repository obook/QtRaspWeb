#!/bin/bash
#
# setup.sh - Build script for QtRaspWeb (ADMoovPiQt)
# Target: Raspberry Pi 5 - PiOS Debian Bookworm
#

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
SRC_DIR="$SCRIPT_DIR/src"
BUILD_DIR="$SRC_DIR/build"
BINARY="ADMoovPiQt"

REQUIRED_PACKAGES=(
    build-essential
    qt6-base-dev
    qt6-webengine-dev
)

info()  { echo -e "${GREEN}[INFO]${NC} $1"; }
warn()  { echo -e "${YELLOW}[WARN]${NC} $1"; }
error() { echo -e "${RED}[ERROR]${NC} $1"; exit 1; }

# ── Checks ──────────────────────────────────────────────

check_os() {
    info "Vérification du système..."

    if [ ! -f /etc/os-release ]; then
        error "/etc/os-release introuvable. Ce script cible PiOS Debian Bookworm."
    fi

    . /etc/os-release

    if [ "$VERSION_CODENAME" != "bookworm" ]; then
        warn "Version détectée : $VERSION_CODENAME (attendu : bookworm)."
        read -r -p "Continuer quand même ? [o/N] " answer
        [[ "$answer" =~ ^[oOyY]$ ]] || exit 0
    fi

    info "Système : $PRETTY_NAME"
}

check_architecture() {
    local arch
    arch="$(uname -m)"
    info "Architecture : $arch"

    if [[ "$arch" != aarch64 && "$arch" != armv7l ]]; then
        warn "Architecture $arch détectée. Ce script est prévu pour Raspberry Pi (aarch64/armv7l)."
    fi
}

# ── Dependencies ────────────────────────────────────────

check_dependencies() {
    info "Vérification des dépendances..."

    local missing=()
    for pkg in "${REQUIRED_PACKAGES[@]}"; do
        if ! dpkg -s "$pkg" &>/dev/null; then
            missing+=("$pkg")
        fi
    done

    if [ ${#missing[@]} -eq 0 ]; then
        info "Toutes les dépendances sont installées."
        return
    fi

    warn "Paquets manquants : ${missing[*]}"
    info "Installation des dépendances..."

    sudo apt-get update
    sudo apt-get install -y "${missing[@]}"

    info "Dépendances installées."
}

# ── Build ───────────────────────────────────────────────

build() {
    info "Compilation de $BINARY..."

    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"

    qmake6 "$SRC_DIR/$BINARY.pro"
    make -j"$(nproc)"

    if [ ! -f "$BUILD_DIR/$BINARY" ]; then
        error "Échec de la compilation : binaire introuvable."
    fi

    info "Compilation réussie : $BUILD_DIR/$BINARY"
}

# ── Main ────────────────────────────────────────────────

main() {
    echo ""
    echo "========================================="
    echo "  QtRaspWeb (ADMoovPiQt) - Setup"
    echo "========================================="
    echo ""

    check_os
    check_architecture
    check_dependencies
    build

    echo ""
    info "Terminé. Pour lancer l'application :"
    echo ""
    echo "  $BUILD_DIR/$BINARY [URL]"
    echo ""
}

main
