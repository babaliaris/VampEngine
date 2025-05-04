#!/bin/bash

# ANSI colors
BOLD="\033[1m"
YELLOW="\033[33m"
GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"
CYAN="\033[36m"

# --- Help Message ---
if [[ "$1" == "help" || "$1" == "--help" || "$1" == "-h" ]]; then
    echo -e "${BOLD}${CYAN}Tag the current Git commit with a video episode marker.${RESET}"
    echo
    echo -e "${BOLD}Usage:${RESET}"
    echo -e "  ./create-git-tag.sh ${YELLOW}<episode-number>${RESET} [${YELLOW}-f${RESET}]"
    echo
    echo -e "${BOLD}Examples:${RESET}"
    echo -e "  ./create-git-tag.sh ${YELLOW}3${RESET}       ${GREEN}# → Tags as video-ep3 (fails if tag exists)${RESET}"
    echo -e "  ./create-git-tag.sh ${YELLOW}3 -f${RESET}    ${GREEN}# → Force-overwrites video-ep3${RESET}"
    echo
    exit 0
fi

# --- Parse arguments ---
EP_NUM=$1
FORCE_FLAG=$2

if [ -z "$EP_NUM" ]; then
    echo -e "${RED}❌ Error: No episode number provided.${RESET}"
    echo -e "Run ${YELLOW}'./create-git-tag.sh help'${RESET} for usage info."
    exit 1
fi

TAG_NAME="video-ep$EP_NUM"

# --- Check if tag exists ---
if git rev-parse "$TAG_NAME" >/dev/null 2>&1; then
    if [ "$FORCE_FLAG" != "-f" ]; then
        echo -e "${RED}❌ Tag '$TAG_NAME' already exists.${RESET} Use ${YELLOW}-f${RESET} to overwrite."
        exit 1
    else
        echo -e "${YELLOW}⚠️  Forcing overwrite of tag '$TAG_NAME'${RESET}"
    fi
fi

# --- Create or replace tag ---
git tag $FORCE_FLAG "$TAG_NAME"
git push origin $FORCE_FLAG "$TAG_NAME"

echo -e "${GREEN}✅ Tagged current commit as '${TAG_NAME}'${RESET}"
