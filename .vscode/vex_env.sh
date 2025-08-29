# .vscode/vex_env.sh
set -euo pipefail

TOOLBIN="$(command -v arm-none-eabi-gcc || true)"
if [ -z "${TOOLBIN:-}" ]; then
  TOOLBIN="$(find /Applications "$HOME/Applications" -type f -name arm-none-eabi-gcc 2>/dev/null | head -n1 || true)"
fi

if [ -z "${TOOLBIN:-}" ]; then
  echo "VEX ARM toolchain not found. Install with Homebrew or install/open VEXcode Pro V5."
  exit 127
fi

echo "Using toolchain: $TOOLBIN"
export PATH="$(dirname "$TOOLBIN"):$PATH"
